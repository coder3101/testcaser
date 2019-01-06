/**
 * Copyright 2018-2019 Ashar <ashar786khan@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP

#ifndef _WIN32
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fstream>
#include <stdexcept>
#include <testcaser/core/integrator/result.hpp>
#define SLACK_THRESHOLD (0.005)

namespace testcaser {
/**
 * @brief This namespace is only meant for internal use. You will not have any
 * use of this scope
 *
 */
namespace internal {
/**
 * @brief Engine that is responsible for running and benchmarking the binary on
 * the given input and constraint.
 */
struct executor_engine {
  /**
   * @brief starts the execution of the new child process with all the arguments
   *
   * @param bin path of the executable to run in the child process.
   * @param in path of the input file to provide to the binary
   * @param out path of the output file to write binary's output
   * @param mem the memory limit of the binary
   * @param tim the time limit of the binary in seconds
   * @param auto_exit_wait if auto exit is false. How long should we wait before
   * a SIGKILL to kill the binary.
   * @param auto_exit should we exit the binary as soon as time or memory limit
   * is passed?
   * @return testcaser::integrator::IntegrationResult
   */
  static testcaser::integrator::Result for_execution_of(
      std::string bin, std::string in, std::string out, size_t mem, size_t tim,
      size_t auto_exit_wait, bool auto_exit) {
    if (!executor_engine::is_readable_file(in))
      throw std::runtime_error("The Input file is not readable. " + in);
    if (!executor_engine::is_readable_binary(bin) &&
        bin.substr(bin.size() - 3, std::string::npos) != ".py")
      throw std::runtime_error(
          "The specified executable file does not exist. " + bin);
    if (!executor_engine::is_readable_file(in) &&
        bin.substr(bin.size() - 3, std::string::npos) == ".py")
      throw std::runtime_error(
          "The Specified python script is not readable or does not exists. " +
          bin);
    std::remove(out.c_str());
    bool is_python_script =
        bin.substr(bin.size() - 3, std::string::npos) == ".py";
    pid_t pid;
    double wll_time;
    testcaser::integrator::ExitStatus exit_stat =
        testcaser::integrator::ExitStatus::NONE;
    int exit_code;
    int max_mem = 0;
    int max_rss = 0;
    pid = fork();
    if (pid < 0) {
      perror("Fork Failed. Unable to create the child process.");
      throw std::runtime_error(strerror(errno));
    } else if (pid == 0) {
      int fin = open(in.c_str(), O_RDONLY);
      int fout = out != "N/A" ? open(out.c_str(), O_CREAT | O_RDWR, 0666)
                              : STDOUT_FILENO;
      dup2(fin, STDIN_FILENO);
      close(fin);
      printf(">>> Child Process created with pid %d\n", getpid());
      printf(">>> Setting the time constraint to %lu seconds\n", tim);
      rlimit trlim;
      if (auto_exit)
        trlim.rlim_cur = trlim.rlim_max = tim;
      else {
        trlim.rlim_cur = trlim.rlim_max = auto_exit_wait;
        printf(">>> Auto Exit Wait Time Limit is %lu\n", auto_exit_wait);
        printf(">>> Auto Exit on Time Limit is turned off\n");
      }
      if (setrlimit(RLIMIT_CPU, &trlim) == 0)
        printf(">>> Process will be killed if not returned before %lu second\n",
               trlim.rlim_max);
      else
        throw std::runtime_error(strerror(errno));
      printf(">>> Executing %s on child process.\n", bin.c_str());
      dup2(fout, STDOUT_FILENO);
      if (fout != STDOUT_FILENO) close(fout);
      if (!is_python_script)
        execl(bin.c_str(), bin.c_str(), (char*)0);
      else
        execl("/usr/bin/python3", "python3", bin.c_str(), (char*)0);
      std::runtime_error("Failed to run the child process. exec failed");
    } else {
      double start = executor_engine::current_high_precision_time();
      pid_t cid = waitpid(pid, &exit_code, WNOHANG | WUNTRACED);
      while (cid == 0) {
        if (cid == -1) {
          printf(">>> Program was killed\n");
          kill(pid, SIGKILL);
          break;
        }

        int vm = executor_engine::get_virtual_memory_use(pid);
        if (vm > max_mem) max_mem = vm;
        int rss = executor_engine::get_physical_memory_use(pid);
        if (rss > max_rss) max_rss = rss;

        if (max_rss > mem) {
          exit_stat = testcaser::integrator::ExitStatus::MEMORY_LIMIT_EXCEEDED;
          kill(pid, SIGKILL);
          printf(
              ">>> Program was killed by SIGKILL for exceeding memory "
              "limits\n");
          break;
        }

        if (executor_engine::current_high_precision_time() - start >
            tim - SLACK_THRESHOLD) {
          printf(">>> Time limit Exceeded.\n");
          if (auto_exit) {
            printf(">>> Sending SIGKILL to program\n");
            exit_stat = testcaser::integrator::ExitStatus::TIME_LIMIT_EXCEEDED;
            kill(pid, SIGKILL);
            break;
          }
        }
        if (executor_engine::current_high_precision_time() - start >
            auto_exit_wait - SLACK_THRESHOLD) {
          printf(">>> Child Hung Up. Sending SIGKILL to kill the Program\n");
          kill(pid, SIGKILL);
          break;
        }
        cid = waitpid(pid, &exit_code, WNOHANG);
      }

      int wstatus = exit_code;
      if (WIFEXITED(wstatus)) {
        exit_code = WEXITSTATUS(wstatus);
        if (exit_stat == testcaser::integrator::ExitStatus::NONE &&
            exit_code == 0)
          exit_stat = testcaser::integrator::ExitStatus::SUCCESS;

        if (exit_stat == testcaser::integrator::ExitStatus::NONE &&
            exit_code != 0)
          exit_stat = testcaser::integrator::ExitStatus::NON_ZERO_EXIT_CODE;
      } else if (exit_stat == testcaser::integrator::ExitStatus::NONE) {
        exit_stat = testcaser::integrator::ABNORMAL_EXIT;
        exit_code = -1;
      }

      printf(">>> Completed the child process with exit code %d\n", exit_code);
      double stop = executor_engine::current_high_precision_time();
      wll_time = stop - start;
    }
    return testcaser::integrator::Result(
        max_rss, max_mem,
        static_cast<size_t>((wll_time + SLACK_THRESHOLD) * 1000000),
        tim * 1000000, mem, exit_stat, exit_code);
  }
  /**
   * @brief Returns the current wall time with microsecond precision.
   *
   * @return double the current time.
   */
  static double current_high_precision_time() {
    timeval time;
    gettimeofday(&time, 0);
    return (double)time.tv_sec + (double)time.tv_usec * 0.000001;
  }
  /**
   * @brief Get the virtual memory used by the pid specified
   *
   * @param pid the pid of process to monitor
   * @return int the memory used in KB
   */
  static int get_virtual_memory_use(pid_t pid) {
    std::string path = "/proc/" + std::to_string(pid) + "/status";
    FILE* file = fopen(path.c_str(), "r");
    int result = -1;
    char line[128];
    while (fgets(line, 128, file) != 0) {
      if (strncmp(line, "VmSize:", 7) == 0) {
        result = executor_engine::parse(line);
        break;
      }
    }
    fclose(file);
    return result;
  }
  /**
   * @brief Get the physical memory used by the pid specified
   *
   * @param pid the pid of process to monitor
   * @return int the memory used in KB
   */
  static int get_physical_memory_use(pid_t pid) {
    std::string path = "/proc/" + std::to_string(pid) + "/status";
    FILE* file = fopen(path.c_str(), "r");
    int result = -1;
    char line[128];
    while (fgets(line, 128, file) != 0) {
      if (strncmp(line, "VmRSS:", 6) == 0) {
        result = executor_engine::parse(line);
        break;
      }
    }
    fclose(file);
    return result;
  }
  /**
   * @brief Parses the line to extract virtual memory use
   *
   * @param line the line to extract info from
   * @return int the vm use in KB
   */
  static int parse(char* line) {
    int i = strlen(line);
    char const* p = line;
    while (*p < '0' || *p > '9') p++;
    line[i - 3] = '\0';
    i = atoi(p);
    return i;
  }

  /**
   * @brief shows if file is readable in text mode.
   *
   * @param file the file to check for
   * @return true if file is readable in text
   * @return false if file is not readable in text
   */

  static bool is_readable_file(std::string file) {
    std::ifstream in;
    in.open(file, std::ios::in);
    bool status = in.is_open() && in.good();
    in.close();
    return status;
  }
  /**
   * @brief shows if file is readable in binary mode.
   *
   * @param file the file to check for
   * @return true if file is readable in binary
   * @return false if file is not readable in binary
   */
  static bool is_readable_binary(std::string file) {
    std::ifstream in;
    in.open(file, std::ios::in);
    bool status = in.is_open() && in.good();
    in.close();
    return status;
  }
};
}  // namespace internal
}  // namespace testcaser
#endif
#endif

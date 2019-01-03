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

#ifndef WIN_EXECUTOR_HPP
#define WIN_EXECUTOR_HPP
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Psapi.h>
#include <io.h>
#include <stdint.h>
#include <fstream>
#include <stdexcept>
#include <string>
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
 * @brief A Posix equivalent for gettimeofday
 *
 */
struct timeval {
  long tv_sec;
  long tv_usec;

  static int gettimeofday(struct timeval* tp, struct timezone* tzp) {
    static const uint64_t EPOCH = ((uint64_t)116444736000000000ULL);
    SYSTEMTIME systime;
    FILETIME ftime;
    uint64_t ttime;
    GetSystemTime(&systime);
    SystemTimeToFileTime(&systime, &ftime);
    ttime = ((uint64_t)ftime.dwLowDateTime);
    ttime += ((uint64_t)ftime.dwHighDateTime) << 32;
    tp->tv_sec = (long)((ttime - EPOCH) / 10000000L);
    tp->tv_usec = (long)(systime.wMilliseconds * 1000);
    return 0;
  }
};
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

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    double wll_time;
    int max_mem = 0;
    int max_rss = 0;
    int exit_code;
    testcaser::integrator::ExitStatus exit_stat =
        testcaser::integrator::ExitStatus::NONE;

    printf(">>> Attempting to Start the Process..\n");
    int old1, old2;
    old1 = _dup(0);
    old2 = _dup(1);
    FILE* fin = fopen(in.c_str(), "r");
    FILE* fout = out != "N/A" ? fopen(out.c_str(), "w") : NULL;
    _dup2(_fileno(fin), 0);
    if (fout != NULL) {
      _dup2(_fileno(fout), 1);
      _close(_fileno(fout));
    }
    std::string command;
    if (is_python_script)
      command = "python3 " + bin;
    else
      command = bin;
    if (!CreateProcess(NULL, const_cast<char*>(command.c_str()), NULL, NULL,
                       FALSE, 0, NULL, NULL, &si, &pi)) {
      std::cerr << "\nFailed to create the child process. Aborting...\n";
      exit(EXIT_FAILURE);
    }
    wll_time = executor_engine::current_high_precision_time();
    std::string kill_str =
        "taskkill /pid " + std::to_string(pi.dwProcessId) + " /f ";
    /**
     * @todo No Exit on High Memory Usage in win_executor.hpp
     * @body The executor of the windows does not exits the child process as
     * soon as the memory limit is reached. This is because you have not figured
     * out how to monitor child memory usage while it is running.
     */

    DWORD status = WaitForSingleObject(pi.hProcess, tim * 1000);
    /**
     * @todo Always enforcing Auto-Exit in win_executor.
     * @body Unlike the UNIX executor, this executor is not waiting for process
     * to terminate incase auto-exit is set to false.
     *
     */
    _dup2(old1, 0);
    _dup2(old2, 1);
    printf(">>> Child Process was created with pid %d\n", pi.dwProcessId);
    printf(">>> Executed %s on child process.\n", bin.c_str());
    DWORD ret_code;
    wll_time = executor_engine::current_high_precision_time() - wll_time;
    GetExitCodeProcess(pi.hProcess, &ret_code);
    if (status == WAIT_TIMEOUT) {
      printf(">>> Time limit Exceeded.\n>>> ");
      std::system(kill_str.c_str());
      exit_stat = testcaser::integrator::ExitStatus::TIME_LIMIT_EXCEEDED;
    } else if (status == WAIT_OBJECT_0) {
      exit_stat = testcaser::integrator::ExitStatus::SUCCESS;
    } else {
      printf(">>> Program was killed. Error Code %d", GetLastError());
      std::system(kill_str.c_str());
      exit(EXIT_FAILURE);
    }
    exit_code = ret_code;
    PROCESS_MEMORY_COUNTERS pmc;
    ZeroMemory(&pmc, sizeof(pmc));
    DWORD dummy = sizeof(pmc);
    GetProcessMemoryInfo(
        pi.hProcess, reinterpret_cast<PPROCESS_MEMORY_COUNTERS>(&pmc), dummy);
    max_rss = pmc.WorkingSetSize / 1024;
    max_mem = pmc.PeakPagefileUsage / 1024;
    CloseHandle(pi.hProcess);
    if (ret_code != 0 &&
        exit_stat == testcaser::integrator::ExitStatus::SUCCESS)
      exit_stat = testcaser::integrator::ExitStatus::NON_ZERO_EXIT_CODE;
    if (max_mem >= mem && exit_stat == testcaser::integrator::ExitStatus::NONE)
      exit_stat = testcaser::integrator::ExitStatus::MEMORY_LIMIT_EXCEEDED;
    printf(">>> Completed the child process with exit code %d", exit_code);
    CloseHandle(pi.hProcess);
    return testcaser::integrator::Result(
        max_rss, max_mem,
        static_cast<size_t>((wll_time + SLACK_THRESHOLD) * 1000000),
        tim * 1000000, mem, exit_stat, exit_code);
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
  /**
   * @brief gets the current time with microseconds precision.
   *
   * @return double the time in double format
   */

  static double current_high_precision_time() {
    timeval time;
    timeval::gettimeofday(&time, 0);
    return (double)time.tv_sec + (double)time.tv_usec * 0.000001;
  }
  /**
   * @brief converts an ANSI character to UNICODE-16 format
   *
   * @param s the ANSI to convert
   * @return std::wstring the UNICODE Equivalent
   */

  static std::wstring s2ws(const std::string& s) {
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
  }
};
}  // namespace internal
}  // namespace testcaser
#endif
#endif

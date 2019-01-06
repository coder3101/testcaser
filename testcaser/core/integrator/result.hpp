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
#ifndef RESULT_HPP
#define RESULT_HPP

#include <iostream>

namespace testcaser {
namespace integrator {
/**
 * @brief Enum about the exit status of the program.
 *
 *
 */
enum ExitStatus {
  /**
   * @brief The process compleed under time and memory limit and reurned 0.
   *
   */
  SUCCESS,
  /**
   * @brief Time limit was exceeded by running program.
   *
   */
  TIME_LIMIT_EXCEEDED,
  /**
   * @brief Memory limit was exceeded by running program.
   *
   */
  MEMORY_LIMIT_EXCEEDED,
  /**
   * @brief Non Zero exit code returned by the process.
   *
   */
  NON_ZERO_EXIT_CODE,
  /**
   * @brief Program did not exited normally usually because of some runtime
   * errors.
   *
   */
  ABNORMAL_EXIT,
  /**
   * @brief No information available about exit status. Maybe because child
   * hasn't executed at all.
   *
   */
  NONE
};
/**
 * @brief The Wrapper that holds the complete result about the running of the
 * program  as child process
 *
 */

class Result {
  size_t runtime_memory, virtual_memory, time_taken;
  size_t allocated_time, allocated_memory;
  ExitStatus exit_status;
  int exit_code;

 public:
  /**
   * @brief Construct a new Result object
   *
   * @param runtimeMemory The RAM Memory used. Also called Physical memory used
   * by the process
   * @param virtualMemory The Virtual Memory Used
   * @param runtime The total execution time in micro-seconds
   * @param allocatedTime The total allocated time in micro-seconds.
   * @param allocatedMemory The total memory that was allocated to the program.
   * Virtual Memory
   * @param exit_stats The exit status. It is the final verdict of the program.
   * @param exit_c the process returned exit code.
   */
  Result(size_t runtimeMemory, size_t virtualMemory, size_t runtime,
         size_t allocatedTime, size_t allocatedMemory, ExitStatus exit_stats,
         int exit_c) {
    runtime_memory = runtimeMemory;
    virtual_memory = virtualMemory;
    time_taken = runtime;
    allocated_time = allocatedTime;
    allocated_memory = allocatedMemory;
    exit_status = exit_stats;
    exit_code = exit_c;
  }
  /**
   * @brief parses ExitStatus into a message
   *
   * @param status the object to parse.
   * @return std::string the parsed message.
   */
  std::string parse_exit_status(testcaser::integrator::ExitStatus status) {
    switch (status) {
      case testcaser::integrator::ExitStatus::SUCCESS:
        return "Success. Ran under memory and time limit";
        break;
      case testcaser::integrator::ExitStatus::TIME_LIMIT_EXCEEDED:
        return "Failure. Time limit was exceeded";
        break;
      case testcaser::integrator::ExitStatus::MEMORY_LIMIT_EXCEEDED:
        return "Failure. Memory Limit was exceeded";
        break;
      case testcaser::integrator::ExitStatus::NON_ZERO_EXIT_CODE:
        return "Unknown. Ran under time and memory but main returned non zero "
               "exit code";
        break;
      case testcaser::integrator::ExitStatus::ABNORMAL_EXIT:
        return "Failure. Runtime Error was encountered.";
        break;
      case testcaser::integrator::ExitStatus::NONE:
        return "Unknown. Unknown";
        break;
    }
  }
  /**
   * @brief Formats and prints the result on stdout (console)
   *
   */
  void print_result() {
    std::cout << "\n************** RESULTS ***************\n";
    std::cout << "Allocted Physical Memory : " << allocated_memory << " KB ("
              << allocated_memory / 1024.0 << " MB)"
              << "\n";
    std::cout << "Physical Memory Used    : " << runtime_memory << " KB ("
              << runtime_memory / 1024.0 << " MB)"
              << "\n";
    std::cout << "Virtual Memory Used     : " << virtual_memory << " KB ("
              << virtual_memory / 1024.0 << " MB)"
              << "\n";
    std::cout << "Allocated Time          : "
              << static_cast<double>(allocated_time) / 1000000.0
              << " second(s) "
              << "\n";
    std::cout << "Execution Time          : "
              << static_cast<double>(time_taken) / 1000000.0 << " second(s) "
              << "\n";
    std::cout << "Exit Code               : " << exit_code << "\n";
    std::cout << "Remark                  : " << parse_exit_status(exit_status)
              << "\n";
    std::cout << "***************************************\n";
  }
  /**
   * @brief Get the execution time of program in seconds
   *
   * @return double the execution time of the program.
   */
  double get_execution_time() const { return time_taken / 1000000.0; }
  /**
   * @brief Get the virtual memory used by the program in KB
   *
   * @return size_t the used virtual memory in KB
   */
  size_t get_virtual_memory_used() const { return virtual_memory; }
  /**
   * @brief Get the physical memory used by the program in KB
   *
   * @return size_t the used physical memory in KB
   */
  size_t get_physical_memory_used() const { return runtime_memory; }
  /**
   * @brief Get the exit code of the program
   *
   * @return int the exit code
   */
  int get_exit_code() const { return exit_code; }
  /**
   * @brief Get the exit status of the program.
   *
   * @return testcaser::integrator::ExitStatus the exit status
   */
  testcaser::integrator::ExitStatus get_exit_status() const {
    return exit_status;
  }
};
}  // namespace integrator
}  // namespace testcaser
#endif

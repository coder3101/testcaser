/**
 * Copyright 2018 Ashar <ashar786khan@gmail.com>
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
#ifdef _WIN32

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
      size_t auto_exit_wait, bool auto_exit) {}

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

#endif
#endif
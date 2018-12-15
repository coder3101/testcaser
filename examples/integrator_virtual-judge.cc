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

#include <testcaser/integrator>

using testcaser::integrator::VirtualJudge;

int main() {
  // we have a program and a input.txt build using maker in this root.
  const std::string root = "./testcaser/core/integrator/tests/";
  /**
   * set_binary(root + "program.out")
   *   required (the path of the binary to execute)
   *
   * set_input_file(root + "input.txt")
   *   required (the input to provide to binary)
   *
   * set_output_file(root + "output2.txt")
   *   optional (the path to write the output of program) defaults to stdout
   *
   * set_time_limit(5)
   *   optional (the time limit in seconds to set for program. No float value)
   *   defaults to 1 sec
   *
   * set_memory_limit(1024 * 25)
   *   optional (the memory limit to set for program in KB)
   *
   * execute()
   *   runs the program, this returns the result of execution. Note this call is
   *   blocking until either time limit exceeds or program returns.
   *
   * print_result()
   *   shows the result of execution from the result object returned by the
   *   execute()
   *
   */
  VirtualJudge()
      .set_binary(root + "program.out")
      .set_input_file(root + "input.txt")
      .set_output_file(root + "output2.txt")
      .set_time_limit(5)
      .set_memory_limit(1024 * 25)
      .execute()
      .print_result();
  return 0;
}
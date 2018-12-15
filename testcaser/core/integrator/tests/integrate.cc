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
  const std::string root = "./testcaser/core/integrator/tests/";
  VirtualJudge()
      .set_binary(root + "program.out")
      .set_input_file(root + "input.txt")
      .set_output_file(root + "output2.txt")
      .set_time_limit(5)
      .set_memory_limit(1024*25)
      .execute()
      .print_result();
  return 0;
}

/**
 * *****************************************************
 * If everything is Okay You will See following on stdout
 * *****************************************************
 * 
 * >>> Child Process created with pid 19398
 * >>> Setting the time constraint to 5 seconds
 * >>> Process will be killed if not returned before 5 second
 * >>> Executing ./testcaser/core/integrator/tests/program.out on child process.
 * >>> Completed the child process with exit code 0

 * ******************** RESULTS ************************
 * Allocted Virtual Memory : 25600 KB (25 MB)
 * Physical Memory Used    : 3412 KB (3.33203 MB)
 * Virtual Memory Used     : 20364 KB (19.8867 MB)
 * Allocated Time          : 5 second(s)
 * Execution Time          : 0.112149 second(s)
 * Exit Code               : 0
 * Remark                  : Success. Ran under memory and time limit
 * *****************************************************
 * ###############################################################################
 * *****************************************************
 * If program.out throws runtime error You will on stdout
 * *****************************************************
 * 
 * >>> Child Process created with pid 19398
 * >>> Setting the time constraint to 5 seconds
 * >>> Process will be killed if not returned before 5 second
 * >>> Executing ./testcaser/core/integrator/tests/program.out on child process.
 * >>> Completed the child process with exit code -1

 * ******************** RESULTS ************************
 * Allocted Virtual Memory : 25600 KB (25 MB)
 * Physical Memory Used    : 3412 KB (3.48203 MB)
 * Virtual Memory Used     : 20364 KB (19.8867 MB)
 * Allocated Time          : 5 second(s)
 * Execution Time          : 0.112149 second(s)
 * Exit Code               : -1
 * Remark                  : Failure. Runtime Error was encountered.
 * *****************************************************
 * ###############################################################################
 * *****************************************************
 * If program.out uses more than specified memory you see
 * *****************************************************
 * 
 * >>> Child Process created with pid 19398
 * >>> Setting the time constraint to 5 seconds
 * >>> Process will be killed if not returned before 5 second
 * >>> Executing ./testcaser/core/integrator/tests/program.out on child process.
 * >>> Completed the child process with exit code -1

 * ******************** RESULTS ************************
 * Allocted Virtual Memory : 20480 KB (20 MB)
 * Physical Memory Used    : 3412 KB (3.48203 MB)
 * Virtual Memory Used     : 22308 KB (21.7852 MB)
 * Allocated Time          : 5 second(s)
 * Execution Time          : 0.001304 second(s)
 * Exit Code               : 0
 * Remark                  : Failure. Memory Limit was exceeded
 * *****************************************************
 * ###############################################################################
 * *****************************************************
 * If program.out uses more than specified time you see
 * *****************************************************
 * 
 * >>> Child Process created with pid 19398
 * >>> Setting the time constraint to 5 seconds
 * >>> Process will be killed if not returned before 5 second
 * >>> Executing ./testcaser/core/integrator/tests/program.out on child process.
 * >>> Completed the child process with exit code -1

 * ******************** RESULTS ************************
 * Allocted Virtual Memory : 25600 KB (25 MB)
 * Physical Memory Used    : 3412 KB (3.48203 MB)
 * Virtual Memory Used     : 22308 KB (21.7852 MB)
 * Allocated Time          : 5 second(s)
 * Execution Time          : 5.00006 second(s)
 * Exit Code               : 0
 * Remark                  : Failure. Time limit was exceeded
 * *****************************************************
 * 
 */
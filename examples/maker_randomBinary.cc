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

/**
 * Problem Statement
 * The First Line contains an Integer T, denoting the number of testcases.
 * For Each T, The First line contains 2 space separated Integer A & B denoting
 * the height and the width of the chess board. The next B lines contains a
 * chessboard where 0 represents black and 1 represents white box of length A in
 * every line.
 *
 * Constraints
 * 1 <= A <= 1000
 * 1 <= B <= 1000
 * 1 <= T < 20
 *
 */

#include <testcaser/maker>

using testcaser::maker::TestCaseBuilder;
using testcaser::maker::types::RandomBinary;
using testcaser::maker::types::RandomUnsignedInteger;

int main() {
  TestCaseBuilder builder("./test.txt");

  RandomUnsignedInteger<> t{1, 20}, a{1, 1001}, b{1, 1001};
  // Create all the Unsigned Numbers in the Range as mentioned in the Problem.

  RandomBinary<> bin;
  int test_case_count = builder.add(t);
  builder.add_line();

  // Repeat for each testcase
  for (int t = 0; t < test_case_count; t++) {
    // Get the value of a and b and write it as well space separated.
    int a_val = builder.add(a);
    builder.add_space();
    int b_val = builder.add(b);
    builder.add_line();
    // Create a chessboard of bxa size
    for (int i = 0; i < b_val; i++) {
      for (int j = 0; j < a_val; j++) builder.add(bin);
      builder.add_line();
    }
  }
  builder.finalize();
  return 0;
}

/**
 * SAMPLE OUTPUT COULD BE
 * 
 * 2
 * 5 4
 * 10101
 * 01011
 * 11001
 * 10111
 * 3 3
 * 101
 * 111
 * 011
 * 
 */
/**
 *   Copyright 2018-2019 Ashar <ashar786khan@gmail.com>
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

#include <iostream>
#include <random>
#include <testcaser/core/maker/randoms/RandomTypes.hpp>

using std::cin;
using std::cout;
using std::endl;

using testcaser::maker::types::RandomAlphabet;
using testcaser::maker::types::RandomBinary;
using testcaser::maker::types::RandomFrom;
using testcaser::maker::types::RandomInteger;
using testcaser::maker::types::RandomQuaternary;
using testcaser::maker::types::RandomQuinary;
using testcaser::maker::types::RandomSenary;
using testcaser::maker::types::RandomTernary;
using testcaser::maker::types::RandomUnsignedInteger;

using testcaser::maker::types::RandomType;

int main() {
  std::mt19937 gen;
  std::random_device rd;
  auto r =
      RandomType<std::mt19937, std::uniform_int_distribution<uint>>(gen, rd());
  cout << "\nStarting Random Number Generation ::";
  auto p = std::uniform_int_distribution<uint>(0, 100);
  for (int t = 0; t < 10; t++) {
    cout << " " << r.get(p);
  }
  auto v = std::vector<char>({'&', '$', '#', ')'});
  RandomFrom<char> i(v);
  for (int t = 0; t < 5; t++) cout << " " << i.get();
  return 0;
}

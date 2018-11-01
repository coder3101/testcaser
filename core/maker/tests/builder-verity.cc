/**
 *   Copyright 2018 Ashar <ashar786khan@gmail.com>
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

#include <core/maker/builder.hpp>
#include <core/maker/randoms/RandomTypes.hpp>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;

using testcaser::maker::RandomIntegerLimit;
using testcaser::maker::TestCaseBuilder;
using testcaser::maker::types::RandomAlphabet;
using testcaser::maker::types::RandomBinary;
using testcaser::maker::types::RandomInteger;
using testcaser::maker::types::RandomFrom;

int main() {
  RandomInteger<> ri{{10, 20}};
  RandomAlphabet<> rai;
  auto dd= {'V', 'r', '#', '*'};
  RandomFrom<char> h(dd);
  RandomBinary<> rb;
  TestCaseBuilder builder("./test.txt");
  auto rs = builder.add_new(ri, true, ' ');
  auto rq = builder.add_new(ri, true, ' ');
  auto rp = builder.add_new(ri, true);
  for (uint t = 0; t < rs; t++) {
    for (uint tp = 0; tp < rp; tp++) {
      builder.add_new(h, false);
    }
    builder.add_new_line();
  }
  for(uint t=0;t<rq;t++)
    builder.add_new(ri, true);
  builder.finalize();
  return 0;
}
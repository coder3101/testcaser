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

#include <testcaser/maker>

using testcaser::maker::TestCaseBuilder;
using testcaser::maker::types::RandomUnsignedInteger;

int main() {
  RandomUnsignedInteger<> a{{1, 100}}, b{{1, 100}}, t{{1, 20000}};
  TestCaseBuilder builder("./testcaser/core/integrator/tests/input.txt");
  auto val = builder.add(t);
  builder.add_line();
  for (int tt = 0; tt < val; tt++) {
    builder.add(a);
    builder.add_space();
    builder.add(b);
    builder.add_line();
  }
  builder.finalize();
  return 0;
}
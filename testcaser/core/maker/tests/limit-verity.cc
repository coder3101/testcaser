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

#include <testcaser/core/maker/randoms/limits.hpp>
#include <iostream>
#include <type_traits>

using std::cin;
using std::cout;
using std::endl;



using testcaser::maker::RandomCharacterLimit;
using testcaser::maker::RandomIntegerLimit;
using testcaser::maker::RandomUnsignedIntegerLimit;

int main() {
  RandomIntegerLimit lt(50, -10);
  RandomIntegerLimit kp(lt);
  RandomUnsignedIntegerLimit lt2({10, 50});
  RandomUnsignedIntegerLimit kp1(lt2);
  RandomCharacterLimit lt3(static_cast<int>('F'), static_cast<int>('A'));
  RandomCharacterLimit kp2(lt3);

  cout << "Actual size  : (50, -10] : " << lt.actual_limit_size() << endl;
  cout << "Actual size  : (F, A] : " << lt3.actual_limit_size() << endl;
  cout << "Actual size  : (50, 10] : " << lt2.actual_limit_size() << endl;

  lt2.add_interval_exception({10, 15});

  cout << "After Interval set : \n";
  cout << "Actual size  : (50, -10] : " << lt.actual_limit_size() << endl;
  cout << "Actual size  : (F, A] : " << lt3.actual_limit_size() << endl;
  cout << "Actual size  : (50, 10] : " << lt2.actual_limit_size() << endl;

  cout << "Is valid : " << lt3.valid_output('C') << endl;
  cout << "Is valid : " << lt3.valid_output('D') << endl;
  cout << "Is valid : " << lt3.valid_output('R') << endl;
  cout << "Is valid : " << lt3.valid_output('B') << endl;
  cout << "Is valid : " << lt3.valid_output('A') << endl;

  cout << "Is Copy constructible RandomCharacterLimit: "
       << std::is_copy_constructible<RandomCharacterLimit>::value << endl;
  cout << "Is Move constructible RandomCharacterLimit: "
       << std::is_move_constructible<RandomCharacterLimit>::value;
  return 0;
}

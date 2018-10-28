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

#ifndef __LIMITS_HPP__
#define __LIMITS_HPP__

#include <vector>

namespace testcaser {
namespace maker {
namespace limits {
template <class T>
struct Intervals {
  T upper;
  T lower;
  Intervals(T a, T b) {
    lower = a;
    upper = b;
  }
  Intervals(std::pair<T, T> pp) {
    lower = pp.first;
    upper = pp.second;
  }
  bool operator<(const Intervals& that) { return this->lower < that.lower; }
  bool operator>(const Intervals& that) { return this->lower > that.lower; }
};
}  // namespace limits

class RandomIntegerLimits {
  std::vector<limits::Intervals<long long>> except_intervals;

 public:
  const long long UpperLimit, LowerLimit;
  explicit RandomIntegerLimits(long long upper, long long lower);
  void add_interval_exception(std::pair<long long, long long> interval);
  unsigned long long actual_limit_size() const;
  bool valid_output(long long out) const;
};

class RandomUnsignedIntegerLimits {
  std::vector<limits::Intervals<unsigned long long>> except_intervals;

 public:
  const long long UpperLimit, LowerLimit;
  explicit RandomUnsignedIntegerLimits(unsigned long long upper,
                                        unsigned long long lower);
  void add_interval_exception(
      std::pair<unsigned long long, unsigned long long> interval);
  unsigned long long actual_limit_size() const;
  bool valid_output(unsigned long long out) const;

};
}  // namespace maker
   // TODO(@coder3101) : Maybe add FloatRanges too.
   // ? Do we need even higher ranges? In most cases it will never exceed 10^18
   // so RandomUnsignedInteger is the best choice to go with.
}  // namespace testcaser
#endif
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

#ifndef LIMITS_HPP
#define LIMITS_HPP

#include <algorithm>
#include <core/exceptions/InvalidLimit.hpp>
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
  bool operator<(const Intervals& that) const {
    return this->lower < that.lower;
  }
  bool operator>(const Intervals& that) const {
    return this->lower > that.lower;
  }
};
}  // namespace limits

class RandomIntegerLimit {
  std::vector<limits::Intervals<long long>> except_intervals;

 public:
  const long long UpperLimit, LowerLimit;
  RandomIntegerLimit(std::initializer_list<long long> llmt)
      : LowerLimit(*(llmt.begin() + 1) > *(llmt.begin()) ? *(llmt.begin())
                                                         : *(llmt.begin() + 1)),
        UpperLimit(*(llmt.begin()) > *(llmt.begin() + 1)
                       ? *(llmt.begin())
                       : *(llmt.begin() + 1)) {
    if (*(llmt.begin()) == *(llmt.begin() + 1)) {
      throw testcaser::exceptions::maker::LimitError(
          "Lower Limit must be strictly smaller than upper limit");
    }
  }
  explicit RandomIntegerLimit(long long upper, long long lower)
      : UpperLimit(upper), LowerLimit(lower) {
    if (lower >= upper) {
      auto ex = testcaser::exceptions::maker::LimitError(
          "Upper limit was : " + std::to_string(upper) +
          "while lower limit was " + std::to_string(lower));
      ex.set_resolution(
          "Lower limit must be strictly smaller than upper limit. Try to "
          "switch them to fix it");
      throw ex;
    }
  }
  void add_interval_exception(std::pair<long long, long long> interval) {
    long long upper =
        interval.first > interval.second ? interval.first : interval.second;
    long long lower = interval.first + interval.second - upper;
    if (upper > UpperLimit || lower < LowerLimit) {
      throw testcaser::exceptions::maker::LimitIntervalError(
          "Intervals upper limit is : " + std::to_string(upper) +
          " while Limit's upper limit is " + std::to_string(UpperLimit) +
          " and for lower " + std::to_string(lower) + " and " +
          std::to_string(LowerLimit) + " respectively.");
    }
    except_intervals.emplace_back(std::make_pair(lower, upper));
  };
  unsigned long long actual_limit_size() {
    long long min, max;
    unsigned long long total_size = UpperLimit - LowerLimit;
    if (except_intervals.size() == 0) return total_size;
    std::sort(except_intervals.begin(), except_intervals.end());
    min = except_intervals[0].lower;
    max = except_intervals[except_intervals.size() - 1].upper;
    total_size -= max - min;
    auto active = except_intervals[0];
    for (int t = 1; t < except_intervals.size(); t++) {
      if (except_intervals[t].lower >= active.upper)
        total_size += except_intervals[t].lower - active.upper;
      if (active.upper < except_intervals[t].upper)
        active = except_intervals[t];
    }
    return total_size;
  };
  bool valid_output(long long out) const {
    if (out >= UpperLimit || out < LowerLimit) return false;
    for (auto& e : except_intervals)
      if (out >= e.lower && out < e.upper) return false;
    return true;
  };
};

class RandomUnsignedIntegerLimit {
  std::vector<limits::Intervals<unsigned long long>> except_intervals;

 public:
  const unsigned long long UpperLimit, LowerLimit;
  RandomUnsignedIntegerLimit(
      std::initializer_list<unsigned long long> llmt)
      : LowerLimit(*llmt.begin() < *(llmt.begin() + 1) ? *llmt.begin()
                                                       : *(llmt.begin() + 1)),
        UpperLimit(*llmt.begin() > *(llmt.begin() + 1) ? *llmt.begin()
                                                       : *(llmt.begin() + 1)) {
    if (*(llmt.begin()) == *(llmt.begin() + 1)) {
      throw testcaser::exceptions::maker::LimitError(
          "Lower Limit must be strictly smaller than upper limit");
    }
  }
  explicit RandomUnsignedIntegerLimit(unsigned long long upper,
                                      unsigned long long lower)
      : UpperLimit(upper), LowerLimit(lower) {
    if (lower >= upper) {
      auto ex = testcaser::exceptions::maker::LimitError(
          "Upper limit was : " + std::to_string(upper) +
          "while lower limit was " + std::to_string(lower));
      ex.set_resolution(
          "Lower limit must be strictly smaller than upper limit. Try to "
          "switch them to fix it");
      throw ex;
    }
  };
  void add_interval_exception(
      std::pair<unsigned long long, unsigned long long> interval) {
    long long upper =
        interval.first > interval.second ? interval.first : interval.second;
    long long lower = interval.first + interval.second - upper;
    if (upper > UpperLimit || lower < LowerLimit) {
      throw testcaser::exceptions::maker::LimitIntervalError(
          "Intervals upper limit is : " + std::to_string(upper) +
          " while Limit's upper limit is " + std::to_string(UpperLimit) +
          " and for lower " + std::to_string(lower) + " and " +
          std::to_string(LowerLimit) + " respectively.");
    }
    except_intervals.emplace_back(std::make_pair(lower, upper));
  };
  unsigned long long actual_limit_size() {
    unsigned long long min, max;
    unsigned long long total_size = UpperLimit - LowerLimit;
    if (except_intervals.size() == 0) return total_size;
    std::sort(except_intervals.begin(), except_intervals.end());
    min = except_intervals[0].lower;
    max = except_intervals[except_intervals.size() - 1].upper;
    total_size -= max - min;
    auto active = except_intervals[0];
    for (int t = 1; t < except_intervals.size(); t++) {
      if (except_intervals[t].lower >= active.upper)
        total_size += except_intervals[t].lower - active.upper;
      if (active.upper < except_intervals[t].upper)
        active = except_intervals[t];
    }
    return total_size;
  };
  bool valid_output(unsigned long long out) const {
    if (out >= UpperLimit || out < LowerLimit) return false;
    for (auto& e : except_intervals)
      if (out >= e.lower && out < e.upper) return false;
    return true;
  };
};
class RandomCharacterLimit {
  std::vector<limits::Intervals<int>> except_intervals;

 public:
  const int UpperLimit, LowerLimit;
  RandomCharacterLimit(std::initializer_list<int> llmt)
      : LowerLimit(*(llmt.begin() + 1) > *(llmt.begin()) ? *(llmt.begin())
                                                         : *(llmt.begin() + 1)),
        UpperLimit(*(llmt.begin()) > *(llmt.begin() + 1)
                       ? *(llmt.begin())
                       : *(llmt.begin() + 1)) {
    if (*(llmt.begin()) == *(llmt.begin() + 1)) {
      throw testcaser::exceptions::maker::LimitError(
          "Lower Limit must be strictly smaller than upper limit");
    }
  }
  RandomCharacterLimit(int upper, int lower)
      : UpperLimit(upper), LowerLimit(lower) {
    if (lower < 0 || upper > 256)
      throw testcaser::exceptions::maker::LimitIntervalError(
          "RandomCharacterLimit exceeds the range of ASCII characters.");
  }
  void add_interval_exception(std::pair<int, int> interval) {
    int upper =
        interval.first > interval.second ? interval.first : interval.second;
    int lower = interval.first + interval.second - upper;
    if (upper > UpperLimit || lower < LowerLimit) {
      throw testcaser::exceptions::maker::LimitIntervalError(
          "Intervals upper limit is : " + std::to_string(upper) +
          " while Limit's upper limit is " + std::to_string(UpperLimit) +
          " and for lower " + std::to_string(lower) + " and " +
          std::to_string(LowerLimit) + " respectively.");
    }
    except_intervals.emplace_back(std::make_pair(lower, upper));
  };
  int actual_limit_size() {
    int min, max;
    int total_size = UpperLimit - LowerLimit;
    if (except_intervals.size() == 0) return total_size;
    std::sort(except_intervals.begin(), except_intervals.end());
    min = except_intervals[0].lower;
    max = except_intervals[except_intervals.size() - 1].upper;
    total_size -= max - min;
    auto active = except_intervals[0];
    for (int t = 1; t < except_intervals.size(); t++) {
      if (except_intervals[t].lower >= active.upper)
        total_size += except_intervals[t].lower - active.upper;
      if (active.upper < except_intervals[t].upper)
        active = except_intervals[t];
    }
    return total_size;
  }
  bool valid_output(int out) const {
    if (out >= UpperLimit || out < LowerLimit) return false;
    for (auto& e : except_intervals)
      if (out >= e.lower && out < e.upper) return false;
    return true;
  };

  static RandomCharacterLimit lower_case_alphabet_limit() {
    return RandomCharacterLimit(static_cast<int>('z') + 1,
                                static_cast<int>('a'));
  }

  static RandomCharacterLimit upper_case_alphabet_limit() {
    return RandomCharacterLimit(static_cast<int>('Z') + 1,
                                static_cast<int>('A'));
  }

  static RandomCharacterLimit alphabet_limit() {
    auto lt =
        RandomCharacterLimit(static_cast<int>('z') + 1, static_cast<int>('A'));
    lt.add_interval_exception(
        std::make_pair(static_cast<int>('Z') + 1, static_cast<int>('a')));
    return lt;
  }

  operator RandomUnsignedIntegerLimit() {
    auto lt = RandomUnsignedIntegerLimit(this->UpperLimit, this->LowerLimit);
    for (auto& interval : this->except_intervals)
      lt.add_interval_exception(std::make_pair(interval.lower, interval.upper));
    return lt;
  }
};
}  // namespace maker

// TODO(@coder3101) : Maybe add FloatRanges too.
// ? Do we need even higher ranges? In most cases it will never exceed 10^18
// so RandomUnsignedInteger is the best choice to go with.

}  // namespace testcaser
#endif
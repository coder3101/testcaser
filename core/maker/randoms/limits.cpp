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

#include <algorithm>
#include <core/exceptions/InvalidLimit.hpp>
#include <core/maker/randoms/limits.hpp>

namespace testcaser {
namespace maker {

RandomIntegerLimit::RandomIntegerLimit(long long upper, long long lower)
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

void RandomIntegerLimit::add_interval_exception(
    std::pair<long long, long long> interval) {
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
}

unsigned long long RandomIntegerLimit::actual_limit_size() const {
  // ! Requires Testing...
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
    if (active.upper < except_intervals[t].upper) active = except_intervals[t];
  }
  return total_size;
}

bool RandomIntegerLimit::valid_output(long long out) const {
  if (out >= UpperLimit || out < LowerLimit) return false;
  for (auto& e : except_intervals)
    if (out >= e.lower && out < e.upper) return false;
  return true;
}

RandomUnsignedIntegerLimit::RandomUnsignedIntegerLimit(unsigned long long upper,
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
}

void RandomUnsignedIntegerLimit::add_interval_exception(
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
}

unsigned long long RandomUnsignedIntegerLimit::actual_limit_size() const {
  // ! Requires Testing...
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
    if (active.upper < except_intervals[t].upper) active = except_intervals[t];
  }
  return total_size;
}

bool RandomUnsignedIntegerLimit::valid_output(unsigned long long out) const {
  if (out >= UpperLimit || out < LowerLimit) return false;
  for (auto& e : except_intervals)
    if (out >= e.lower && out < e.upper) return false;
  return true;
}

RandomCharacterLimit::RandomCharacterLimit(int upper, int lower)
    : UpperLimit(upper), LowerLimit(lower) {
  if (lower < 0 || upper > 256)
    throw testcaser::exceptions::maker::LimitIntervalError(
        "RandomCharacterLimit exceeds the range of ASCII characters.");
}

int RandomCharacterLimit::actual_limit_size() const {
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
    if (active.upper < except_intervals[t].upper) active = except_intervals[t];
  }
  return total_size;
}
bool RandomCharacterLimit::valid_output(int out) const {
  if (out >= UpperLimit || out < LowerLimit) return false;
  for (auto& e : except_intervals)
    if (out >= e.lower && out < e.upper) return false;
  return true;
}

void RandomCharacterLimit::add_interval_exception(
    std::pair<int, int> interval) {
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
}
}  // namespace maker
}  // namespace testcaser

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
/**
 * @brief Internal namespace that encapsulates the Intervals Class used by Limit
 *
 */
namespace limits {
/**
 * @brief Interval holding class. Interval is [lower, upper) type.
 *
 * @tparam T The lower and upper limit type
 */
template <class T>
struct Intervals {
  /**
   * @brief upper the upper limit
   * 
   */
  T upper;
  /**
   * @brief lower the lower limit of the interval
   * 
   */
  T lower;
  /**
   * @brief Construct a new Intervals object
   *
   * @param a Lower limit of interval
   * @param b Upper limit of the interval
   */
  Intervals(T a, T b) {
    lower = a;
    upper = b;
  }
  /**
   * @brief Construct a new Intervals object
   *
   * @param pp A Interval as a pair of with first being the lower and second
   * being the higher interval limit
   */
  Intervals(std::pair<T, T> pp) {
    lower = pp.first;
    upper = pp.second;
  }
  /**
   * @brief compares two interval from their starting/lower points
   *
   * @param that other object to compare with
   * @return true if the other's lower limit is bigger that this lower limit
   * @return false otherwise
   */
  bool operator<(const Intervals& that) const {
    return this->lower < that.lower;
  }
  /**
   * @brief compares two interval from their starting/lower points
   *
   * @param that other object to compare with
   * @return true if the this lower limit is bigger that that's lower limit
   * @return false otherwise
   */
  bool operator>(const Intervals& that) const {
    return this->lower > that.lower;
  }
};
}  // namespace limits

/**
 * @brief A object that holds the properties of a limit that will be imposed on
 * the Random Integer generator
 *
 */
class RandomIntegerLimit {
  std::vector<limits::Intervals<long long>> except_intervals;

  // Todo (@coder3101) : Some Distributions takes Floats instead of limits like
  // Todo : bernauli's trial and gaussian distribution. Changing the upperLimit
  // Todo : LowerLimit to double will be a Good Idea in Future or create a
  // Todo : different limit class to handle those cases.

 public:
  /**
   * @brief UpperLimit the upper limit of the character as ASCII int.
   *
   */
  const long long UpperLimit;

  /**
   * @brief LowerLimit the lower limit of the character as ASCII int.
   *
   */

  const long long LowerLimit;
  /**
   * @brief Construct a new Random Integer Limit object
   *
   * @param llmt the limit as initializer list
   */
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
  /**
   * @brief Construct a new Random Integer Limit object
   *
   * @param upper the upper bound of the limit (not included)
   * @param lower the lower bound of the limit (included)
   */
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
  /**
   * @brief Adds a interval exception in between the limit say. Original Limit
   * are [a, b) and you want to skip some intervals in between say [c,d) such
   * that c >= a and d < b then you would call this method with std::pair<c,d>
   *
   * @param interval the std::pair object holding an interval in between the
   * original limit.
   */
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
  /**
   * @brief The limit size after excluding all the exceptions in between them
   *
   * @return unsigned long long the value of the limit size
   */
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
  /**
   * @brief checks if the a long long is a valid as per the limit constraints
   * with exception internals in mind.
   *
   * @param out the value to check for
   * @return true if doesn't violates the limit rules
   * @return false if violates any rule or is out of limit
   */
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
  /**
   * @brief UpperLimit the upper limit of the character as ASCII int.
   *
   */
  const unsigned long long UpperLimit;

  /**
   * @brief LowerLimit the lower limit of the character as ASCII int.
   *
   */

  const unsigned long long LowerLimit;
  /**
   * @brief Construct a new Random Unsigned Integer Limit object
   *
   * @param llmt the limit as initializer list
   */
  RandomUnsignedIntegerLimit(std::initializer_list<unsigned long long> llmt)
      : LowerLimit(*llmt.begin() < *(llmt.begin() + 1) ? *llmt.begin()
                                                       : *(llmt.begin() + 1)),
        UpperLimit(*llmt.begin() > *(llmt.begin() + 1) ? *llmt.begin()
                                                       : *(llmt.begin() + 1)) {
    if (*(llmt.begin()) == *(llmt.begin() + 1)) {
      throw testcaser::exceptions::maker::LimitError(
          "Lower Limit must be strictly smaller than upper limit");
    }
  }
  /**
   * @brief Construct a new Random Unsigned Integer Limit object
   *
   * @param upper the upper bound of the limit (not included)
   * @param lower the lower bound of the limit (included)
   */
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
  /**
   * @brief Adds a interval exception in between the limit say. Original Limit
   * are [a, b) and you want to skip some intervals in between say [c,d) such
   * that c >= a and d < b then you would call this method with std::pair<c,d>
   *
   * @param interval the std::pair object holding an interval in between the
   * original limit.
   */
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
  /**
   * @brief The limit size after excluding all the exceptions in between them
   *
   * @return unsigned long long the value of the limit size
   */
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
  /**
   * @brief checks if the a unsigned long long is a valid as per the limit
   * constraints with exception internals in mind.
   *
   * @param out the value to check for
   * @return true if doesn't violates the limit rules
   * @return false if violates any rule or is out of limit
   */
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
  /**
   * @brief UpperLimit the upper limit of the character as ASCII int.
   *
   */
  const int UpperLimit;

  /**
   * @brief LowerLimit the lower limit of the character as ASCII int.
   *
   */

  const int LowerLimit;
  /**
   * @brief Construct a new Random Character Limit object
   *
   * @param llmt the limit as initializer list
   */
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
  /**
   * @brief Construct a new Random Character Limit object
   *
   * @param upper the upper bound of the limit (not included)
   * @param lower the lower bound of the limit (included)
   */
  RandomCharacterLimit(int upper, int lower)
      : UpperLimit(upper), LowerLimit(lower) {
    if (lower < 0 || upper > 256)
      throw testcaser::exceptions::maker::LimitIntervalError(
          "RandomCharacterLimit exceeds the range of ASCII characters.");
  }
  /**
   * @brief Adds a interval exception in between the limit say. Original Limit
   * are [a, b) and you want to skip some intervals in between say [c,d) such
   * that c >= a and d < b then you would call this method with std::pair<c,d>
   *
   * @param interval the std::pair object holding an interval in between the
   * original limit.
   */
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
  /**
   * @brief The limit size after excluding all the exceptions in between them
   *
   * @return int the value of the limit size
   */
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
  /**
   * @brief checks if the a char is a valid as per the limit
   * constraints with exception internals in mind.
   *
   * @param out the value to check for
   * @return true if doesn't violates the limit rules
   * @return false if violates any rule or is out of limit
   */
  bool valid_output(int out) const {
    if (out >= UpperLimit || out < LowerLimit) return false;
    for (auto& e : except_intervals)
      if (out >= e.lower && out < e.upper) return false;
    return true;
  };
  /**
   * @brief returns the limit of the lower case alphabets.
   *
   * @return RandomCharacterLimit
   */

  static RandomCharacterLimit lower_case_alphabet_limit() {
    return RandomCharacterLimit(static_cast<int>('z') + 1,
                                static_cast<int>('a'));
  }
  /**
   * @brief returns the upper case alphabet limit
   *
   * @return RandomCharacterLimit
   */

  static RandomCharacterLimit upper_case_alphabet_limit() {
    return RandomCharacterLimit(static_cast<int>('Z') + 1,
                                static_cast<int>('A'));
  }
  /**
   * @brief returns the mixed case alphabet limit
   *
   * @return RandomCharacterLimit
   */

  static RandomCharacterLimit alphabet_limit() {
    auto lt =
        RandomCharacterLimit(static_cast<int>('z') + 1, static_cast<int>('A'));
    lt.add_interval_exception(
        std::make_pair(static_cast<int>('Z') + 1, static_cast<int>('a')));
    return lt;
  }
  /**
   * @brief Converts this object to an object of RandomUnsignedIntegerLimit
   *
   * @return RandomUnsignedIntegerLimit
   */

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
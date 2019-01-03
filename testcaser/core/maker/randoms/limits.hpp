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

#ifndef LIMITS_HPP
#define LIMITS_HPP

#include <algorithm>
#include <testcaser/core/exceptions/InvalidLimit.hpp>
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
   * @param pp An Interval as a pair of with first being the lower and second
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
  bool operator<(Intervals const& that) const {
    return this->lower < that.lower;
  }
  /**
   * @brief compares two interval from their starting/lower points
   *
   * @param that other object to compare with
   * @return true if the this lower limit is bigger that that's lower limit
   * @return false otherwise
   */
  bool operator>(Intervals const& that) const {
    return this->lower > that.lower;
  }
};
}  // namespace limits

/**
 * @brief This is the base class that lays out the structure of all the limits.
 * All the limits must ineherit from this class
 *
 * @tparam T the type of the limit
 */
template <class T>
class BaseLimitProperties {
 protected:
  /**
   * @brief intervals in a vector to exclude the sampling from.
   *
   */
  std::vector<limits::Intervals<T>> except_intervals;

 public:
  /**
   * @brief UpperLimit the upper limit.
   *
   */
  T const UpperLimit;
  /**
   * @brief LowerLimit the lower limit.
   *
   */
  T const LowerLimit;

  /**
   * @brief Construct a new Base Limit Properties object
   *
   * @param lower the lower limit to set
   * @param upper the upper limit to set
   */
  explicit BaseLimitProperties(T lower, T upper)
      : LowerLimit(lower), UpperLimit(upper) {}

  /**
   * @brief Adds a interval exception in between the limit say. Original Limit
   * are [a, b) and you want to skip some intervals in between say [c,d) such
   * that c >= a and d < b then you would call this method with std::pair<c,d>
   *
   * @param interval the std::pair object holding an interval in between the
   * original limit.
   */
  void add_interval_exception(std::pair<T, T> interval) {
    T upper =
        interval.first > interval.second ? interval.first : interval.second;
    T lower = interval.first + interval.second - upper;
    if (upper > UpperLimit || lower < LowerLimit) {
      throw testcaser::exceptions::maker::LimitIntervalError(
          "Intervals upper limit is : " + std::to_string(upper) +
          " while Limit's upper limit is " + std::to_string(UpperLimit) +
          " and for lower " + std::to_string(lower) + " and " +
          std::to_string(LowerLimit) + " respectively.");
    }
    except_intervals.emplace_back(std::make_pair(lower, upper));
  }

  /**
   * @brief checks if a value produced T is a valid as per the limit constraints
   * with exception internals in mind.
   *
   * @param out the value to check for
   * @return true if doesn't violates the limit rules
   * @return false if violates any rule or is out of limit
   */
  bool valid_output(T out) const {
    if (out >= UpperLimit || out < LowerLimit) return false;
    for (auto& e : except_intervals)
      if (out >= e.lower && out < e.upper) return false;
    return true;
  }
  /**
   * @brief The limit size after excluding all the exceptions in between them
   *
   * @return unsigned long long the value of the limit size
   */
  unsigned long long actual_limit_size() {
    T min, max;
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
};

/**
 * @brief An object that holds the properties of a limit that will be imposed on
 * the Random Integer generator
 *
 */
struct RandomIntegerLimit final : public BaseLimitProperties<long long> {
  /**
   * @brief Construct a new Random Integer Limit object
   *
   * @param llmt the limit as initializer list
   */
  RandomIntegerLimit(std::initializer_list<long long> llmt)
      : BaseLimitProperties(
            (*(llmt.begin() + 1) > *(llmt.begin()) ? *(llmt.begin())
                                                   : *(llmt.begin() + 1)),
            (*(llmt.begin()) > *(llmt.begin() + 1) ? *(llmt.begin())
                                                   : *(llmt.begin() + 1))) {
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
      : BaseLimitProperties(lower, upper) {
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
};
/**
 * @brief Generates an RandomUnsigned Integer Limit to be used by the
 * RandomUnsignedInteger to generate Random Values in the limit specified by
 * this object.
 *
 */
struct RandomUnsignedIntegerLimit final
    : public BaseLimitProperties<unsigned long long> {
  /**
   * @brief Construct a new Random Unsigned Integer Limit object
   *
   * @param llmt the limit to set
   */
  RandomUnsignedIntegerLimit(std::initializer_list<unsigned long long> llmt)
      : BaseLimitProperties(
            (*(llmt.begin() + 1) > *(llmt.begin()) ? *(llmt.begin())
                                                   : *(llmt.begin() + 1)),
            (*(llmt.begin()) > *(llmt.begin() + 1) ? *(llmt.begin())
                                                   : *(llmt.begin() + 1))) {
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
      : BaseLimitProperties(lower, upper) {
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
};
/**
 * @brief Generates an ASCII Character Limit to be used by the RandomAlphabet to
 * generate Random Values in the limit specified by this object.
 *
 */
struct RandomCharacterLimit final : public BaseLimitProperties<int> {
  /**
   * @brief Construct a new Random Character Limit object
   *
   * @param llmt the limit to set
   */
  RandomCharacterLimit(std::initializer_list<int> llmt)
      : BaseLimitProperties(
            (*(llmt.begin() + 1) > *(llmt.begin()) ? *(llmt.begin())
                                                   : *(llmt.begin() + 1)),
            (*(llmt.begin()) > *(llmt.begin() + 1) ? *(llmt.begin())
                                                   : *(llmt.begin() + 1))) {
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
      : BaseLimitProperties(lower, upper) {
    if (lower < 0 || upper > 256)
      throw testcaser::exceptions::maker::LimitIntervalError(
          "RandomCharacterLimit exceeds the range of ASCII characters.");
  }
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
};  // namespace maker
}  // namespace maker

/**
 * @todo Maybe add FloatRanges too.
 * @body Maybe in some cases the Ranges or numbers to generate is not always
 * Unsigned. In some cases when it is Float. We may add Float Ranges as well.
 */
}  // namespace testcaser
#endif
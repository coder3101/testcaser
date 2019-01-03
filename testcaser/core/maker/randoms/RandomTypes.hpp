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
#ifndef RANDOM_TYPES_HPP
#define RANDOM_TYPES_HPP

#include <iostream>
#include <random>
#include <testcaser/core/maker/randoms/limits.hpp>

namespace testcaser {
namespace maker {

/**
 * @brief The internal template that holds all the types that generate a random
 * result
 *
 */
namespace types {

/**
 * @brief RandomType The core random type that holds the random generation logic
 * inside of itself. Do not instantiate this object it is for internal purpose
 * only.
 *
 * @tparam RNG the Random Number Generator
 * @tparam DistributionType The distribution type to use for this generator
 */

template <class RNG, class DistributionType>

class RandomType {
  RNG& engine;
  /**
   * @brief Seeds the value to the Random number engine
   *
   * @param seed the value to seed
   */
  void seed_value(typename RNG::result_type seed) { engine.seed(seed); }

  // ? std::random_device is very sucepticle to copy and move construction. How
  // ? about we pass its value directly after seeding.

 public:
  /**
   * @brief Construct a new Random Type object
   *
   * @param gen the generator object.
   * @param seed the value to seed
   */
  RandomType(RNG& gen, typename RNG::result_type seed) : engine(gen) {
    seed_value(seed);
  }
  /**
   * @brief returns the value from the generator over the distribution
   *
   * @param dist the distribution object
   * @return DistributionType::result_type the value expected to return by the
   * distribution
   */
  typename DistributionType::result_type get(DistributionType& dist) const {
    return dist(engine);
  }
};

/**
 * @brief RandomInteger object generates a random integer every time .get() is
 * called it follows the generator and the distribution type that you provide.
 *
 * @tparam std::mt19937 The default Random Number generator to use
 * @tparam std::uniform_int_distribution<long long> The default distribution to
 * use
 */

template <class Generator = std::mt19937,
          class Distribution = std::uniform_int_distribution<long long>>
class RandomInteger {
  testcaser::maker::RandomIntegerLimit const limit;
  RandomType<Generator, Distribution> rt;
  Generator gen;

 public:
  /**
   * @brief Construct a new Random Integer object. Defaults the range to range
   * of Long Long of C++.
   *
   */
  RandomInteger()
      : limit({__LONG_LONG_MAX__, -__LONG_LONG_MAX__}),
        gen(std::random_device()()),
        rt(RandomType<Generator, Distribution>{gen, std::random_device()()}) {}
  /**
   * @brief Construct a new Random Integer object
   *
   * @param lmt the limit to set on the range of random number generated
   */
  RandomInteger(testcaser::maker::RandomIntegerLimit lmt)
      : limit(lmt),
        gen(std::random_device()()),
        rt(RandomType<Generator, Distribution>{gen, std::random_device()()}) {}
  /**
   * @brief Construct a new Random Integer object
   *
   * @param lst the range as a initializer list
   */
  RandomInteger(std::initializer_list<long long> lst)
      : limit(testcaser::maker::RandomIntegerLimit{lst}),
        gen(std::random_device()()),
        rt(RandomType<Generator, Distribution>{gen, std::random_device()()}) {}
  /**
   * @brief returns the random number from this class
   *
   * @return long long the value of the random number
   */
  long long get() const {
    /**
     * @todo Make get() startegy even better.
     * @body The sampling of the distribution can be inefficent when too many
     * except_intervals are specified. Improve this startegy
     *
     */
    Distribution dis{limit.LowerLimit, limit.UpperLimit - 1};
    long long out = rt.get(dis);
    while (!limit.valid_output(out)) out = rt.get(dis);
    return out;
  }

  /**
   * @brief Get the random Integer non-strictly more than the value specified.
   *
   * @param val The new lower limit for the distribution to sample from.
   * @return long long The Value more than val bu under the limit of this
   * object.
   */

  long long get_more_than(long long val) {
    if (val >= limit.UpperLimit) {
      throw testcaser::exceptions::maker::LimitIntervalError(
          "Restriction of value more than " + std::to_string(val) +
          " while Upper Limit on this random number was set to " +
          std::to_string(limit.UpperLimit));
    } else {
      Distribution dis{val, limit.UpperLimit - 1};
      long long out = rt.get(dis);
      while (!limit.valid_output(out)) out = rt.get(dis);
      return out;
    }
  }
  /**
   * @brief Get the random Integer non-strictly less than the value specified.
   *
   * @param val The new upper limit for the distribution to sample from.
   * @return long long The Value less than val but under the limit of this
   * object.
   */

  long long get_less_than(long long val) {
    if (val < limit.LowerLimit) {
      throw testcaser::exceptions::maker::LimitIntervalError(
          "Restriction of value less than " + std::to_string(val) +
          " while Lower Limit on this random number was set to " +
          std::to_string(limit.LowerLimit));
    } else {
      Distribution dis{limit.LowerLimit, val};
      long long out = rt.get(dis);
      while (!limit.valid_output(out)) out = rt.get(dis);
      return out;
    }
  }

  /**
   * @brief reseeds the generator with a new seed value
   *
   * @param seed the value to seed the generator
   */
  void reseed_engine(typename Generator::result_type seed) {
    rt.seed_value(seed);
  }
  /**
   * @brief reseed the random number engine with the random value. It uses
   * std::random_device()() for this task.
   *
   */
  void reseed_engine_with_random_device() {
    rt.seed_value(std::random_device()());
  }
};

/**
 * @brief RandomUnsignedInteger object generates a random integer every time
 * .get() is called it follows the generator and the distribution type that you
 * provide.
 *
 * @tparam std::mt19937 the default generator to use
 * @tparam std::uniform_int_distribution<unsigned long long> the default
 * distribution to use
 */

template <class Generator = std::mt19937,
          class Distribution =
              std::uniform_int_distribution<unsigned long long>>
class RandomUnsignedInteger {
  testcaser::maker::RandomUnsignedIntegerLimit const limit;
  RandomType<Generator, Distribution> rt;
  Generator gen;

 public:
  /**
   * @brief Construct a new Random Unsigned Integer object
   *
   */
  RandomUnsignedInteger()
      : limit({static_cast<unsigned long long>(__LONG_LONG_MAX__) * 2, 0}),
        gen(std::random_device()()),
        rt(RandomType<Generator, Distribution>{gen, std::random_device()()}) {}

  /**
   * @brief Construct a new Random Unsigned Integer object
   *
   * @param lmt the random number limit to put on the generator
   */
  RandomUnsignedInteger(testcaser::maker::RandomUnsignedIntegerLimit lmt)
      : limit(lmt),
        gen(std::random_device()()),
        rt(RandomType<Generator, Distribution>{gen, std::random_device()()}) {}

  /**
   * @brief Construct a new Random Unsigned Integer object
   *
   * @param lst the limit in the form of initializer list
   */
  RandomUnsignedInteger(std::initializer_list<unsigned long long> lst)
      : limit(testcaser::maker::RandomUnsignedIntegerLimit{lst}),
        gen(std::random_device()()),
        rt(RandomType<Generator, Distribution>{gen, std::random_device()()}) {}

  /**
   * @brief returns the random number generated
   *
   * @return unsigned long long the value returned
   */
  unsigned long long get() const {
    Distribution dis{limit.LowerLimit, limit.UpperLimit - 1};
    unsigned long long out = rt.get(dis);
    while (!limit.valid_output(out)) out = rt.get(dis);
    return out;
  }
  /**
   * @brief Get the random Integer non-strictly more than the value specified.
   *
   * @param val The new lower limit for the distribution to sample from.
   * @return unsigned long long The Value more than val bu under the limit of
   * this object.
   */

  unsigned long long get_more_than(unsigned long long val) {
    if (val >= limit.UpperLimit) {
      throw testcaser::exceptions::maker::LimitIntervalError(
          "Restriction of value more than " + std::to_string(val) +
          " while Upper Limit on this random number was set to " +
          std::to_string(limit.UpperLimit));
    } else {
      Distribution dis{val, limit.UpperLimit - 1};
      unsigned long long out = rt.get(dis);
      while (!limit.valid_output(out)) out = rt.get(dis);
      return out;
    }
  }
  /**
   * @brief Get the random Unsigned Integer non-strictly less than the value
   * specified.
   *
   * @param val The new upper limit for the distribution to sample from.
   * @return unsigned long long The Value less than val but under the limit of
   * this object.
   */

  unsigned long long get_less_than(unsigned long long val) {
    if (val < limit.LowerLimit) {
      throw testcaser::exceptions::maker::LimitIntervalError(
          "Restriction of value less than " + std::to_string(val) +
          " while Lower Limit on this random number was set to " +
          std::to_string(limit.LowerLimit));
    } else {
      Distribution dis{limit.LowerLimit, val};
      unsigned long long out = rt.get(dis);
      while (!limit.valid_output(out)) out = rt.get(dis);
      return out;
    }
  }
  /**
   * @brief reseed the engine with the given value
   *
   * @param seed the value to seed the engine with
   */
  void reseed_engine(typename Generator::result_type seed) {
    rt.seed_value(seed);
  }

  /**
   * @brief reseeds the generator engine with a new random device value.
   *
   */
  void reseed_engine_with_random_device() {
    rt.seed_value(std::random_device()());
  }
};

/**
 * @brief RandomBinary object generates a random binary every time .get() is
 * called it follows the generator and the distribution type that you provide.
 *
 * @tparam std::mt19937 the random number generator to use
 * @tparam std::uniform_int_distribution<unsigned long long> the distribution to
 * use to sample the random number
 */
template <class Generator = std::mt19937,
          class Distribution =
              std::uniform_int_distribution<unsigned long long>>
struct RandomBinary {
  /**
   * @brief rui the RandomUnsignedInteger object to generate binary numbers with
   * binary limit
   *
   */
  RandomUnsignedInteger<Generator, Distribution> rui;

  /**
   * @brief Construct a new Random Binary object
   *
   */
  RandomBinary()
      : rui(RandomUnsignedInteger<Generator, Distribution>{{2, 0}}) {}
  /**
   * @brief Get the random value as boolean object
   *
   * @return true
   * @return false
   */
  bool get_as_boolean() { return rui.get() == 1 ? true : false; }
  /**
   * @brief Get the random value as int object
   *
   * @return unsigned long long
   */
  unsigned long long get_as_int() const { return rui.get(); }
};

/**
 * @brief RandomTernary object generates a random ternary every time .get() is
 * called it follows the generator and the distribution type that you provide.
 *
 * @tparam std::mt19937 the random number generator to use
 * @tparam std::uniform_int_distribution<unsigned long long> the distribution to
 * use to sample the random number
 */
template <class Generator = std::mt19937,
          class Distribution =
              std::uniform_int_distribution<unsigned long long>>
struct RandomTernary {
  /**
   * @brief rui the RandomUnsignedInteger object to ternary numbers with ternary
   * limit
   *
   */
  RandomUnsignedInteger<Generator, Distribution> rui;
  /**
   * @brief Construct a new Random Ternary object
   *
   * @param one_based should the ternary start with 1 index or 0 index
   */
  RandomTernary(bool one_based = false)
      : rui(RandomUnsignedInteger<Generator, Distribution>(
            {one_based ? 4ull : 3ull, one_based ? 1ull : 0ull})) {}
  /**
   * @brief Get the value as int object
   *
   * @return unsigned long long
   */
  unsigned long long get_as_int() const { return rui.get(); }
};

/**
 * @brief RandomQuaternary object generates a random quaternary every time
 * .get() is called it follows the generator and the distribution type that you
 * provide.
 *
 * @tparam std::mt19937 the random number generator to use
 * @tparam std::uniform_int_distribution<unsigned long long> the distribution to
 * use to sample the random number
 */

template <class Generator = std::mt19937,
          class Distribution =
              std::uniform_int_distribution<unsigned long long>>
struct RandomQuaternary {
  /**
   * @brief rui the RandomUnsignedInteger object to quaternary numbers with
   * quaternary limit
   *
   */
  RandomUnsignedInteger<Generator, Distribution> rui;
  /**
   * @brief Construct a new Random Quaternary object
   *
   * @param one_based should use start with 0 or 1
   */
  RandomQuaternary(bool one_based = false)
      : rui(RandomUnsignedInteger<Generator, Distribution>(
            {one_based ? 5ull : 4ull, one_based ? 1ull : 0ull})) {}
  /**
   * @brief Get the value as int object
   *
   * @return unsigned long long
   */
  unsigned long long get_as_int() const { return rui.get(); }
};

/**
 * @brief RandomQuinary object generates a random quinary every time .get() is
 * called it follows the generator and the distribution type that you provide.
 *
 * @tparam std::mt19937 the random number generator to use
 * @tparam std::uniform_int_distribution<unsigned long long> the distribution to
 * use to sample the random number
 */
template <class Generator = std::mt19937,
          class Distribution =
              std::uniform_int_distribution<unsigned long long>>
struct RandomQuinary {
  /**
   * @brief rui the RandomUnsignedInteger object to generate quinary numbers
   * with quinary limit
   *
   */
  RandomUnsignedInteger<Generator, Distribution> rui;
  /**
   * @brief Construct a new Random Quinary object
   *
   * @param one_based use 0 or 1 as random number starting position
   */
  RandomQuinary(bool one_based = false)
      : rui(RandomUnsignedInteger<Generator, Distribution>(
            {one_based ? 6ull : 5ull, one_based ? 1ull : 0ull})) {}
  /**
   * @brief Get the value as int object
   *
   * @return unsigned long long
   */
  unsigned long long get_as_int() const { return rui.get(); }
};

/**
 * @brief RandomSenary object generates a random senary every time .get() is
 * called it follows the generator and the distribution type that you provide.
 *
 * @tparam std::mt19937 the random number generator to use
 * @tparam std::uniform_int_distribution<unsigned long long> the distribution to
 * use to sample the random number
 */
template <class Generator = std::mt19937,
          class Distribution =
              std::uniform_int_distribution<unsigned long long>>
struct RandomSenary {
  /**
   * @brief rui the RandomUnsignedInteger object to generate senary numbers with
   * senary limit
   *
   */
  RandomUnsignedInteger<Generator, Distribution> rui;
  /**
   * @brief Construct a new Random Senary object
   *
   * @param one_based use the 0 or 1 as start of random number
   */
  RandomSenary(bool one_based = false)
      : rui(RandomUnsignedInteger<Generator, Distribution>(
            {one_based ? 7ull : 6ull, one_based ? 1ull : 0ull})) {}
  /**
   * @brief Get the value as int object
   *
   * @return unsigned long long
   */
  unsigned long long get_as_int() const { return rui.get(); }
};

/**
 * @brief RandomAlphabet object generates a random alphabet every time .get() is
 * called it follows the generator and the distribution type that you provide.
 *
 * @tparam std::mt19937 the random number generator to use
 * @tparam std::uniform_int_distribution<unsigned long long> the distribution to
 * use to sample the random number
 */
template <class Generator = std::mt19937,
          class Distribution =
              std::uniform_int_distribution<unsigned long long>>
class RandomAlphabet {
 private:
  RandomUnsignedInteger<Generator, Distribution> rui1;
  RandomUnsignedInteger<Generator, Distribution> rui2;
  RandomUnsignedInteger<Generator, Distribution> rui3;

 public:
  /**
   * @brief Construct a new Random Alphabet object
   *
   */
  RandomAlphabet()
      : rui1(RandomUnsignedInteger<Generator, Distribution>(
            testcaser::maker::RandomCharacterLimit::
                upper_case_alphabet_limit())),
        rui2(RandomUnsignedInteger<Generator, Distribution>(
            testcaser::maker::RandomCharacterLimit::
                lower_case_alphabet_limit())),
        rui3(RandomUnsignedInteger<Generator, Distribution>(
            testcaser::maker::RandomCharacterLimit::alphabet_limit())) {}
  /**
   * @brief Get the lower case character
   *
   * @return char the lower case char
   */
  char get_lower() const { return static_cast<char>(rui2.get()); }
  /**
   * @brief Get the upper case char
   *
   * @return char the upper case character
   */
  char get_upper() const { return static_cast<char>(rui1.get()); }
  /**
   * @brief returns a distribution based character from mix of upper and lower
   *
   * @return char a valid upper or lower character
   */
  char get() const { return static_cast<char>(rui3.get()); }
};

/**
 * @brief A Simple UpperCase RandomAlphabet Wrapper
 *
 * @tparam std::mt19937 The Genenerator to use in the sampling
 * @tparam std::uniform_int_distribution<unsigned long long> The Distribution to
 * use in the sampling.
 */

template <class Generator = std::mt19937,
          class Distribution =
              std::uniform_int_distribution<unsigned long long>>
class RandomUpperAlphabet {
  RandomAlphabet<Generator, Distribution> rui1;

 public:
  RandomUpperAlphabet() : rui1(RandomAlphabet<Generator, Distribution>()){};
  /**
   * @brief Gets a new Random Upper Case Alphabet
   *
   * @return char The Upper Case Alphabet Value
   */
  char get() const { return static_cast<char>(rui1.get_upper()); }
};

/**
 * @brief A Simple LowerCase RandomAlphabet Wrapper
 *
 * @tparam std::mt19937 The Genenerator to use in the generation.
 * @tparam std::uniform_int_distribution<unsigned long long> The Distribution to
 * use in the sampling.
 */

template <class Generator = std::mt19937,
          class Distribution =
              std::uniform_int_distribution<unsigned long long>>
class RandomLowerAlphabet {
  RandomAlphabet<Generator, Distribution> rui1;

 public:
  RandomLowerAlphabet() : rui1(RandomAlphabet<Generator, Distribution>()){};
  /**
   * @brief Gets a new Random Lower Case Alphabet
   *
   * @return char The Lower Case Alphabet Value
   */
  char get() const { return static_cast<char>(rui1.get_lower()); }
};
/**
 * @brief RandomFrom object picks a random object from given collection every
 * time .get() is called it follows the generator and the distribution type that
 * you provide.
 *
 * @tparam std::mt19937 the random number generator to use
 * @tparam std::uniform_int_distribution<unsigned long long> the distribution to
 * use to sample the random number
 */
template <class T, class Generator = std::mt19937,
          class Distribution =
              std::uniform_int_distribution<unsigned long long>>
struct RandomFrom {
  /**
   * @brief data the collection from where the samples will be drawn
   *
   */
  std::vector<T> data;
  /**
   * @brief limit the limit to set on the sample collection
   *
   */
  testcaser::maker::RandomUnsignedIntegerLimit limit;
  /**
   * @brief _rui The RandomUnsignedInteger object to generate collection size
   * numbers with collection size limit. This is for Internal Use only
   *
   */
  RandomUnsignedInteger<Generator, Distribution> _rui;
  /**
   * @brief Construct a new Random From object
   *
   * @param collection the collection as a vector
   */
  RandomFrom(std::vector<T> collection)
      : data(collection),
        limit({collection.size(), 0}),
        _rui(RandomUnsignedInteger<Generator, Distribution>{limit}) {}
  /**
   * @brief returns a randomly picked random object from the collection
   *
   * @return T an object of the collection
   */
  T get() const { return data[_rui.get()]; }
};
// ? As far as float/double is concerned it should be generated via
// ? RandomIntegers. We do not wish to add separate object for it as of now.
// ? Maybe Later we can do that too.
}  // namespace types
}  // namespace maker
}  // namespace testcaser
#endif
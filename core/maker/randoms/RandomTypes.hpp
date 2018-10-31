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
#ifndef RANDOM_TYPES_HPP
#define RANDOM_TYPES_HPP

#include <core/maker/randoms/limits.hpp>
#include <iostream>
#include <random>

namespace testcaser {
namespace maker {
namespace types {

template <class RNG, class DistributionType>
class RandomType {
  RNG& engine;
  void seed_value(typename RNG::result_type seed) { engine.seed(seed); }

  // ? std::random_device is very sucepticle to copy and move construction. How
  // ? about we pass its value directly after seeding.

 public:
  RandomType(RNG& gen, typename RNG::result_type seed) : engine(gen) {
    seed_value(seed);
  }
  typename DistributionType::result_type get(DistributionType& dist) const {
    return dist(engine);
  }
};

template <class Generator = std::mt19937,
          class Distribution = std::uniform_int_distribution<long long>>
class RandomInteger {
  const testcaser::maker::RandomIntegerLimit limit;
  RandomType<Generator, Distribution> rt;
  Generator gen;

 public:
  RandomInteger()
      : limit({__LONG_LONG_MAX__, -__LONG_LONG_MAX__}),
        gen(std::random_device()()),
        rt(RandomType<Generator, Distribution>{gen, std::random_device()()}) {}
  RandomInteger(testcaser::maker::RandomIntegerLimit lmt)
      : limit(lmt),
        gen(std::random_device()()),
        rt(RandomType<Generator, Distribution>{gen, std::random_device()()}) {}
  long long get() const {
    // todo(@coder3101) Change this stategy to something more efficent
    Distribution dis{limit.LowerLimit, limit.UpperLimit - 1};
    long long out = rt.get(dis);
    while (!limit.valid_output(out)) out = rt.get(dis);
    return out;
  }
  void reseed_engine(typename Generator::result_type seed) {
    rt.seed_value(seed);
  }
  void reseed_engine_with_random_device() {
    rt.seed_value(std::random_device()());
  }
};

template <class Generator = std::mt19937,
          class Distribution =
              std::uniform_int_distribution<unsigned long long>>
class RandomUnsignedInteger {
  const testcaser::maker::RandomUnsignedIntegerLimit limit;
  RandomType<Generator, Distribution> rt;
  Generator gen;

 public:
  RandomUnsignedInteger()
      : limit({static_cast<unsigned long long>(__LONG_LONG_MAX__) * 2, 0}),
        gen(std::random_device()()),
        rt(RandomType<Generator, Distribution>{gen, std::random_device()()}) {}
  RandomUnsignedInteger(testcaser::maker::RandomUnsignedIntegerLimit lmt)
      : limit(lmt),
        gen(std::random_device()()),
        rt(RandomType<Generator, Distribution>{gen, std::random_device()()}) {}
  unsigned long long get() const {
    // todo(@coder3101) Change this stategy to something more efficent
    Distribution dis{limit.LowerLimit, limit.UpperLimit - 1};
    unsigned long long out = rt.get(dis);
    while (!limit.valid_output(out)) out = rt.get(dis);
    return out;
  }
  void reseed_engine(typename Generator::result_type seed) {
    rt.seed_value(seed);
  }

  void reseed_engine_with_random_device() {
    rt.seed_value(std::random_device()());
  }
};

template <class Generator = std::mt19937,
          class Distribution =
              std::uniform_int_distribution<unsigned long long>>
struct RandomBinary {
  RandomUnsignedInteger<Generator, Distribution> rui;
  RandomBinary()
      : rui(RandomUnsignedInteger<Generator, Distribution>{{2, 0}}) {}
  bool get_as_boolean() { return rui.get() == 1 ? true : false; }
  unsigned long long get_as_int() const { return rui.get(); }
};

template <class Generator = std::mt19937,
          class Distribution =
              std::uniform_int_distribution<unsigned long long>>
struct RandomTernary {
  RandomUnsignedInteger<Generator, Distribution> rui;
  RandomTernary(bool one_based = false)
      : rui(RandomUnsignedInteger<Generator, Distribution>(
            {one_based ? 4ull : 3ull, one_based ? 1ull : 0ull})) {}
  unsigned long long get_as_int() const { return rui.get(); }
};
template <class Generator = std::mt19937,
          class Distribution =
              std::uniform_int_distribution<unsigned long long>>
struct RandomQuaternary {
  RandomUnsignedInteger<Generator, Distribution> rui;
  RandomQuaternary(bool one_based = false)
      : rui(RandomUnsignedInteger<Generator, Distribution>(
            {one_based ? 5ull : 4ull, one_based ? 1ull : 0ull})) {}
  unsigned long long get_as_int() const { return rui.get(); }
};
template <class Generator = std::mt19937,
          class Distribution =
              std::uniform_int_distribution<unsigned long long>>
struct RandomQuinary {
  RandomUnsignedInteger<Generator, Distribution> rui;
  RandomQuinary(bool one_based = false)
      : rui(RandomUnsignedInteger<Generator, Distribution>(
            {one_based ? 6ull : 5ull, one_based ? 1ull : 0ull})) {}
  unsigned long long get_as_int() const { return rui.get(); }
};
template <class Generator = std::mt19937,
          class Distribution =
              std::uniform_int_distribution<unsigned long long>>
struct RandomSenary {
  RandomUnsignedInteger<Generator, Distribution> rui;
  RandomSenary(bool one_based = false)
      : rui(RandomUnsignedInteger<Generator, Distribution>(
            {one_based ? 7ull : 6ull, one_based ? 1ull : 0ull})) {}
  unsigned long long get_as_int() const { return rui.get(); }
};

template <class Generator = std::mt19937,
          class Distribution =
              std::uniform_int_distribution<unsigned long long>>
struct RandomAlphabet {
  RandomUnsignedInteger<Generator, Distribution> rui1, rui2, rui3;
  RandomAlphabet()
      : rui1(RandomUnsignedInteger<Generator, Distribution>(
            testcaser::maker::RandomCharacterLimit::
                upper_case_alphabet_limit())),
        rui2(RandomUnsignedInteger<Generator, Distribution>(
            testcaser::maker::RandomCharacterLimit::
                lower_case_alphabet_limit())),
        rui3(RandomUnsignedInteger<Generator, Distribution>(
            testcaser::maker::RandomCharacterLimit::alphabet_limit())) {}
  char get_lower() const { return static_cast<char>(rui2.get()); }
  char get_upper() const { return static_cast<char>(rui1.get()); }
  char get() const { return static_cast<char>(rui3.get()); }
};

template <class T, class Generator = std::mt19937,
          class Distribution =
              std::uniform_int_distribution<unsigned long long>>
struct RandomFrom {
  std::vector<T> data;
  testcaser::maker::RandomUnsignedIntegerLimit limit;
  RandomUnsignedInteger<Generator, Distribution> rui;
  RandomFrom(std::vector<T> r)
      : data(r),
        limit({r.size(), 0}),
        rui(RandomUnsignedInteger<Generator, Distribution>{limit}) {}
  T get() const { return data[rui.get()]; }
};
// ? As far as float/double is concerned it should be generated via
// ? RandomIntegers. We do not wish to add separate object for it as of now.
// ? Maybe Later we can do that too.
}  // namespace types
}  // namespace maker
}  // namespace testcaser
#endif
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
#ifndef __RANDOM_TYPES_HPP__
#define __RANDOM_TYPES_HPP__

#include <core/maker/randoms/limits.hpp>
#include <random>

namespace testcaser {
namespace maker {
namespace types {

template <class RNG, class DistributionType>
class RandomType {
  bool use_rd;
  std::random_device rd;
  const RNG& engine;
  void seed_value(uint32_t seed) { engine.seed(seed); }

 public:
  RandomType(RNG& gen, bool random_device = true)
      : use_rd(random_device), engine(gen) {
    if (use_rd)
      engine.seed(rd);
    else
      seed_value(0u);
  }
  typename DistributionType::result_type get(DistributionType& dist) {
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
  RandomInteger(bool use_random_device = true)
      : limit(__LONG_LONG_MAX__, -__LONG_LONG_MAX__),
        rd_flag(use_random_device),
        rt(RandomType(gen, use_random_device)) {}
  RandomInteger(testcaser::maker::RandomIntegerLimits lmt,
                bool use_random_device = true)
      : limit(lmt),
        rd_flag(use_random_device),
        rt(RandomType(gen, use_random_device)) {}
  long long get() {
    // todo(@coder3101) Change this stategy to something more efficent
    Distribution dis(limit.LowerLimit, limit.UpperLimit - 1);
    long long out = rt.get(dis);
    while (!limit.valid_output(out)) out = rt.get(dis);
    return out;
  }
  void reseed_engine(uint32_t seed) { rt.seed_value(seed); }
};

template <class Generator = std::mt19937,
          class Distribution =
              std::uniform_int_distribution<unsigned long long>>
class RandomUnsignedInteger {
  const testcaser::maker::RandomUnsignedIntegerLimit limit;
  RandomType<Generator, Distribution> rt;
  Generator gen;

 public:
  RandomUnsignedInteger(bool use_random_device = true)
      : limit((__LONG_LONG_MAX__ - 1) * 2, 0),
        rt(RandomType(gen, use_random_device)) {}
  RandomUnsignedInteger(testcaser::maker::RandomUnsignedIntegerLimit lmt,
                        bool use_random_device = true)
      : limit(lmt), rt(RandomType(gen, use_random_device)) {}
  unsigned long long get() {
    // todo(@coder3101) Change this stategy to something more efficent
    Distribution dis(limit.LowerLimit, limit.UpperLimit - 1);
    long long out = rt.get(dis);
    while (!limit.valid_output(out)) out = rt.get(dis);
    return out;
  }
  void reseed_engine(uint32_t seed) { rt.seed_value(seed); }
};

template <class Generator = std::mt19937,
          class Distribution = std::uniform_int_distribution<long long>>
struct RandomBinary {
  RandomUnsignedInteger<Generator, Distribution> rui;
  RandomBinary()
      : rui(RandomUnsignedInteger<Generator, Distribution>(
            testcaser::maker::RandomUnsignedIntegerLimit(2, 0), true)) {}
  bool get_as_boolean() { return rui.get() == 1 ? true : false; }
  unsigned long long get_as_int() { return rui.get(); }
};

template <class Generator = std::mt19937,
          class Distribution = std::uniform_int_distribution<long long>>
struct RandomTernary {
  RandomUnsignedInteger<Generator, Distribution> rui;
  RandomTernary(bool one_based = false)
      : rui(RandomUnsignedInteger<Generator, Distribution>(
            testcaser::maker::RandomUnsignedIntegerLimit(one_based ? 4 : 3,
                                                         one_based ? 1 : 0),
            true)) {}
  unsigned long long get_as_int() { return rui.get(); }
};
template <class Generator = std::mt19937,
          class Distribution = std::uniform_int_distribution<long long>>
struct RandomQuaternary {
  RandomUnsignedInteger<Generator, Distribution> rui;
  RandomQuaternary(bool one_based = false)
      : rui(RandomUnsignedInteger<Generator, Distribution>(
            testcaser::maker::RandomUnsignedIntegerLimit(one_based ? 5 : 4,
                                                         one_based ? 1 : 0),
            true)) {}
  unsigned long long get_as_int() { return rui.get(); }
};
template <class Generator = std::mt19937,
          class Distribution = std::uniform_int_distribution<long long>>
struct RandomQuinary {
  RandomUnsignedInteger<Generator, Distribution> rui;
  RandomQuinary(bool one_based = false)
      : rui(RandomUnsignedInteger<Generator, Distribution>(
            testcaser::maker::RandomUnsignedIntegerLimit(one_based ? 6 : 5,
                                                         one_based ? 1 : 0),
            true)) {}
  unsigned long long get_as_int() { return rui.get(); }
};
template <class Generator = std::mt19937,
          class Distribution = std::uniform_int_distribution<long long>>
struct RandomSenary {
  RandomUnsignedInteger<Generator, Distribution> rui;
  RandomSenary(bool one_based = false)
      : rui(RandomUnsignedInteger<Generator, Distribution>(
            testcaser::maker::RandomUnsignedIntegerLimit(one_based ? 7 : 6,
                                                         one_based ? 1 : 0),
            true)) {}
  unsigned long long get_as_int() { return rui.get(); }
};

template <class Generator = std::mt19937,
          class Distribution = std::uniform_int_distribution<long long>>
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
  char get_lower() { return static_cast<char>(rui2.get()); }
  char get_upper() { return static_cast<char>(rui1.get()); }
  char get() { return static_cast<char>(rui3.get()); }
};

template <class T, class Generator = std::mt19937,
          class Distribution =
              std::uniform_int_distribution<unsigned long long>>
struct RandomFrom {
  std::vector<T> data;
  RandomUnsignedInteger<Generator, Distribution> rui;
  testcaser::maker::RandomUnsignedIntegerLimit limit;
  RandomFrom(std::vector<T> r) : data(r) {
    limit = testcaser::maker::RandomUnsignedIntegerLimit(r.size(), 0);
    rui = RandomUnsignedInteger<Generator, Distribution>(limit);
  }
  T get() { return data[rui.get()]; }
};
// ? As far as float/double is concerned it should be generated via
// ? RandomIntegers. We do not wish to add separate object for it as of now.
// ? Maybe Later we can do that too.
}  // namespace types
}  // namespace maker
}  // namespace testcaser
#endif
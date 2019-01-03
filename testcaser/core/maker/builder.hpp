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

#ifndef __BUILDER_HPP__
#define __BUILDER_HPP__

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <testcaser/core/exceptions/BuildException.hpp>
#include <testcaser/core/maker/randoms/RandomTypes.hpp>
#include <typeindex>
#ifndef _IO_BUFSIZ
#define _IO_BUFSIZ (4096)
#endif


/**
 *
 * @brief The main namespace of the project. It is the main namespace of the
 * project
 *
 */
namespace testcaser {
/**
 * @brief The maker namespace of the testcaser namespace. This namespace has all
 * the testcase file generaing classes and functions
 *
 */
namespace maker {

/**
 * @brief A Test Case builder Class that can be used to create a single test
 * case file
 *
 */
class TestCaseBuilder {
  std::ofstream file;
  bool finalized = false;
  std::string fname;
  std::string to_write;

  bool buffer_full() { return _IO_BUFSIZ <= to_write.size(); }
  void perform_write() {
    file << to_write;
    to_write.clear();
  }

 public:
  TestCaseBuilder() = delete;
  TestCaseBuilder(TestCaseBuilder&) = delete;
  TestCaseBuilder(TestCaseBuilder&&) = delete;
  bool operator=(TestCaseBuilder const& other) = delete;
  /**
   * @brief Construct a new Test Case Builder object
   *
   * @param abs_name The Absolute name of the testfile to generate. it should be
   * a txt file
   */
  explicit TestCaseBuilder(std::string abs_name) : fname(abs_name) {
    file.open(abs_name, std::ios::out);
    if (!file.is_open() || !file.good()) {
      throw testcaser::exceptions::maker::TestFileIOError(
          "File is Open : " + std::to_string(file.is_open()) +
          " :: File is Good : " + std::to_string(file.good()));
      to_write.reserve(_IO_BUFSIZ + 1);
    }
    file.seekp(0, std::ios::beg);
  }
  /**
   * @brief Adds a new RandomAlphabet to the testcase file
   *
   * @tparam std::mt19937 The Generator to use in the generation
   * @tparam std::uniform_int_distribution<long long> The Distribution to use in
   * the sampling.
   * @param randomAlphabet The RandomAlphabet type to use here.
   * @return char The Generated Random Alphabet
   */
  template <class gen = std::mt19937,
            class dis = std::uniform_int_distribution<long long>>
  char add(types::RandomAlphabet<gen, dis>& randomAlphabet) {
    if (this->finalized) {
      throw testcaser::exceptions::maker::FinalizationError(
          "Cannot add new alphabet once file has been finalized");
    }
    char u = randomAlphabet.get();
    if (this->buffer_full()) this->perform_write();
    to_write += std::to_string(u);
    return u;
  };
  /**
   * @brief Adds a new RandomLowerAlphabet to the testcase file
   *
   * @tparam std::mt19937 The Generator to use in the generation
   * @tparam std::uniform_int_distribution<long long> The Distribution to use in
   * the sampling.
   * @param randomLowerAlphabet The RandomLowerAlphabet type to use here.
   * @return char The Generated Random Lower Alphabet
   */
  template <class gen = std::mt19937,
            class dis = std::uniform_int_distribution<long long>>
  char add(types::RandomLowerAlphabet<gen, dis>& randomLowerAlphabet) {
    if (this->finalized) {
      throw testcaser::exceptions::maker::FinalizationError(
          "Cannot add new lower alphabet once file has been finalized");
    }
    char u = randomLowerAlphabet.get();
    if (this->buffer_full()) this->perform_write();
    to_write += std::to_string(u);
    return u;
  };
  /**
   * @brief Adds a new RandomUpperAlphabet to the testcase file
   *
   * @tparam std::mt19937 The Generator to use in the generation
   * @tparam std::uniform_int_distribution<long long> The Distribution to use in
   * the sampling.
   * @param randomUpperAlphabet The RandomUpperAlphabet type to use here.
   * @return char The Generated Random Upper Alphabet
   */
  template <class gen = std::mt19937,
            class dis = std::uniform_int_distribution<long long>>
  char add(types::RandomUpperAlphabet<gen, dis>& randomUpperAlphabet) {
    if (this->finalized) {
      throw testcaser::exceptions::maker::FinalizationError(
          "Cannot add new alphabet once file has been finalized");
    }
    char u = randomUpperAlphabet.get();
    if (this->buffer_full()) this->perform_write();
    to_write += std::to_string(u);
    return u;
  };
  /**
   * @brief Adds a new RandomInteger to the testcase file
   *
   * @tparam std::mt19937 The Generator to use in the generation
   * @tparam std::uniform_int_distribution<long long> The Distribution to use in
   * the sampling.
   * @param randomInteger The RandomInteger type to use here.
   * @return long long The Generated Random Integer
   */
  template <class gen = std::mt19937,
            class dis = std::uniform_int_distribution<long long>>
  long long add(types::RandomInteger<gen, dis>& randomInteger) {
    if (this->finalized) {
      throw testcaser::exceptions::maker::FinalizationError(
          "Cannot add new line once file has been finalized");
    }
    long long res = randomInteger.get();
    if (this->buffer_full()) this->perform_write();
    to_write += std::to_string(res);
    return res;
  };
  /**
   * @brief Adds a new RandomBinary to the testcase file.
   *
   * @tparam std::mt19937 The Generator to use in the generation
   * @tparam std::uniform_int_distribution<unsigned long long> The Distribution
   * to use in the sampling.
   * @param randomBinary The RandomBinary type to use here.
   * @return unsigned long long The Generated Random Binary
   */
  template <class gen = std::mt19937,
            class dis = std::uniform_int_distribution<unsigned long long>>
  unsigned long long add(types::RandomBinary<gen, dis>& randomBinary) {
    if (this->finalized) {
      throw testcaser::exceptions::maker::FinalizationError(
          "Cannot add new binary line once file has been finalized");
    }
    unsigned long long res = randomBinary.get_as_int();
    if (this->buffer_full()) this->perform_write();
    to_write += std::to_string(res);
    return res;
  };
  /**
   * @brief Adds a new RandomTernary to the testcase file.
   *
   * @tparam std::mt19937 The Generator to use in the generation
   * @tparam std::uniform_int_distribution<unsigned long long> The Distribution
   * to use in the sampling.
   * @param randomTernary The RandomTernary type to use here.
   * @return unsigned long long The Generated Random Ternary
   */
  template <class gen = std::mt19937,
            class dis = std::uniform_int_distribution<unsigned long long>>
  unsigned long long add(types::RandomTernary<gen, dis>& randomTernary) {
    if (this->finalized) {
      throw testcaser::exceptions::maker::FinalizationError(
          "Cannot add new ternary line once file has been finalized");
    }
    unsigned long long res = randomTernary.get_as_int();
    if (this->buffer_full()) this->perform_write();
    to_write += std::to_string(res);
    return res;
  };
  /**
   * @brief Adds a new RandomQuaternary to the testcase file.
   *
   * @tparam std::mt19937 The Generator to use in the generation
   * @tparam std::uniform_int_distribution<unsigned long long> The Distribution
   * to use in the sampling.
   * @param randomQuaternary The RandomQuaternary type to use here.
   * @return unsigned long long The Generated Random Quaternary
   */
  template <class gen = std::mt19937,
            class dis = std::uniform_int_distribution<unsigned long long>>
  unsigned long long add(types::RandomQuaternary<gen, dis>& randomQuaternary) {
    if (this->finalized) {
      throw testcaser::exceptions::maker::FinalizationError(
          "Cannot add new binary quaternary once file has been finalized");
    }
    unsigned long long res = randomQuaternary.get_as_int();
    if (this->buffer_full()) this->perform_write();
    to_write += std::to_string(res);
    return res;
  };
  /**
   * @brief Adds a new RandomQuinary to the testcase file.
   *
   * @tparam std::mt19937 The Generator to use in the generation
   * @tparam std::uniform_int_distribution<unsigned long long> The Distribution
   * to use in the sampling.
   * @param randomQuinary The RandomQuinary type to use here.
   * @return unsigned long long The Generated Random Quinary
   */
  template <class gen = std::mt19937,
            class dis = std::uniform_int_distribution<unsigned long long>>
  unsigned long long add(types::RandomQuinary<gen, dis>& randomQuinary) {
    if (this->finalized) {
      throw testcaser::exceptions::maker::FinalizationError(
          "Cannot add new quinary line once file has been finalized");
    }
    unsigned long long res = randomQuinary.get_as_int();
    if (this->buffer_full()) this->perform_write();
    to_write += std::to_string(res);
    return res;
  };
  /**
   * @brief Adds a new RandomSenary to the testcase file.
   *
   * @tparam std::mt19937 The Generator to use in the generation
   * @tparam std::uniform_int_distribution<unsigned long long> The Distribution
   * to use in the sampling.
   * @param randomSenary The RandomSenary type to use here.
   * @return unsigned long long The Generated Random Senary
   */
  template <class gen = std::mt19937,
            class dis = std::uniform_int_distribution<unsigned long long>>
  unsigned long long add(types::RandomSenary<gen, dis>& randomSenary) {
    if (this->finalized) {
      throw testcaser::exceptions::maker::FinalizationError(
          "Cannot add new senary line once file has been finalized");
    }
    unsigned long long res = randomSenary.get_as_int();
    if (this->buffer_full()) this->perform_write();
    to_write += std::to_string(res);
    return res;
  };
  /**
   * @brief Adds a new RandomUnsignedInteger to the testcase file.
   *
   * @tparam std::mt19937 The Generator to use in the generation
   * @tparam std::uniform_int_distribution<unsigned long long> The Distribution
   * to use in the sampling.
   * @param randomUnsignedInteger The RandomUnsigned type to use here.
   * @return unsigned long long The Generated Random Unsigned
   */
  template <class gen = std::mt19937,
            class dis = std::uniform_int_distribution<unsigned long long>>
  unsigned long long add(
      types::RandomUnsignedInteger<gen, dis>& randomUnsignedInteger) {
    if (this->finalized) {
      throw testcaser::exceptions::maker::FinalizationError(
          "Cannot add new unsigned long long once file has been finalized");
    }
    unsigned long long res = randomUnsignedInteger.get();
    if (this->buffer_full()) this->perform_write();
    to_write += std::to_string(res);
    return res;
  };
  /**
   * @brief Adds a new RandomFrom to the testcase file.
   *
   * @tparam T The type of the collection to sample from.
   * @tparam std::mt19937 The Generator to use in the generation
   * @tparam std::uniform_int_distribution<unsigned long long> The Distribution
   * to use in the sampling.
   * @param randomFrom The object of RandomFrom to use
   * @return T The Randomly Sampled value.
   */
  template <class T, class gen = std::mt19937,
            class dis = std::uniform_int_distribution<unsigned long long>>
  T add(types::RandomFrom<T, gen, dis>& randomFrom) {
    if (this->finalized) {
      throw testcaser::exceptions::maker::FinalizationError(
          "Cannot add new randomFrom once file has been finalized");
    }
    auto res = randomFrom.get();
    if (this->buffer_full()) this->perform_write();
    if (typeid(T) == typeid(char)) {
      char buf[2];
      buf[0] = res;
      buf[1] = '\0';
      to_write.append(buf);
    } else
      to_write += std::to_string(res);
    return res;
  };

  /**
   * @brief Adds a new Random Integer which will be more than value specified
   *
   * @tparam std::mt19937 The Random Number Generator
   * @tparam std::uniform_int_distribution<long long> The Uniform Sampler for
   * Sampling the Numbers.
   * @param val The value of restriction. Output will be more than this value
   * always.
   * @param randomInteger The RandomInteger Object to sample the values from
   * @return long long The Value that satisfies the restriction
   */

  template <class gen = std::mt19937,
            class dis = std::uniform_int_distribution<long long>>
  long long add_more_than(long long val,
                          types::RandomInteger<gen, dis>& randomInteger) {
    auto res = randomInteger.get_more_than(val);
    if (this->buffer_full()) this->perform_write();
    to_write += std::to_string(res);
    return res;
  }
  /**
   * @brief Adds a new Random Unsigned Integer which will be more than value
   * specified
   *
   * @tparam std::mt19937 The Random Number Generator
   * @tparam std::uniform_int_distribution<long long> The Uniform Sampler for
   * Sampling the Numbers.
   * @param val The value of restriction. Output will be more than this value
   * always.
   * @param randomUnsignedInteger The RandomUnsignedInteger Object to sample the
   * values from
   * @return unsigned long long The Value that satisfies the restriction
   */

  template <class gen = std::mt19937,
            class dis = std::uniform_int_distribution<unsigned long long>>
  unsigned long long add_more_than(
      unsigned long long val,
      types::RandomUnsignedInteger<gen, dis>& randomUnsignedInteger) {
    auto res = randomUnsignedInteger.get_more_than(val);
    if (this->buffer_full()) this->perform_write();
    to_write += std::to_string(res);
    return res;
  }
  /**
   * @brief Adds a new Random Integer which will be less than value specified
   *
   * @tparam std::mt19937 The Random Number Generator
   * @tparam std::uniform_int_distribution<long long> The Uniform Sampler for
   * Sampling the Numbers.
   * @param val The value of restriction. Output will be less than this value
   * always.
   * @param randomInteger The RandomInteger Object to sample the values from
   * @return long long The Value that satisfies the restriction
   */

  template <class gen = std::mt19937,
            class dis = std::uniform_int_distribution<long long>>
  long long add_less_than(long long val,
                          types::RandomInteger<gen, dis>& randomInteger) {
    auto res = randomInteger.get_less_than(val);
    if (this->buffer_full()) this->perform_write();
    to_write += std::to_string(res);
    return res;
  }
  /**
   * @brief Adds a new Random Unsigned Integer which will be less than value
   * specified
   *
   * @tparam std::mt19937 The Random Number Generator
   * @tparam std::uniform_int_distribution<long long> The Uniform Sampler for
   * Sampling the Numbers.
   * @param val The value of restriction. Output will be less than this value
   * always.
   * @param randomUnsignedInteger The RandomUnsignedInteger Object to sample the
   * values from
   * @return unsigned long long The Value that satisfies the restriction
   */

  template <class gen = std::mt19937,
            class dis = std::uniform_int_distribution<unsigned long long>>
  unsigned long long add_less_than(
      unsigned long long val,
      types::RandomUnsignedInteger<gen, dis>& randomUnsignedInteger) {
    auto res = randomUnsignedInteger.get_less_than(val);
    if (this->buffer_full()) this->perform_write();
    to_write += std::to_string(res);
    return res;
  }
  /**
   * @brief Adds a Single Space to the file.
   *
   * @return char The Space character
   */
  char add_space() {
    if (this->finalized) {
      throw testcaser::exceptions::maker::FinalizationError(
          "Cannot add space once file has been finalized");
    }
    if (this->buffer_full()) this->perform_write();
    to_write.append(" ");
    return ' ';
  };
  /**
   * @brief Adds a new Character to the file.
   *
   * @param chr The Character to write to file.
   * @return char The Written character
   */
  char add_character(char chr) {
    if (this->finalized) {
      throw testcaser::exceptions::maker::FinalizationError(
          "Cannot add special character once file has been finalized");
    }
    if (this->buffer_full()) this->perform_write();
    char buf[2];
    buf[0] = chr;
    buf[1] = '\n';
    to_write.append(buf);
    return chr;
  };
  /**
   * @brief Adds a new line to the file.
   *
   * @return char The New line Character
   */
  char add_line() {
    if (this->finalized) {
      throw testcaser::exceptions::maker::FinalizationError(
          "Cannot add new line once file has been finalized");
    }
    if (this->buffer_full()) this->perform_write();
    to_write.append("\n");
    return '\n';
  }
  /**
   * @brief Finalizes the file so that no new changes or addition can be done on
   * the file. This Operations closes the builder and freezes it to furthur
   * modification.
   */
  void finalize() {
    this->perform_write();
    this->finalized = true;
    std::cout << "\nWritten " << this->fname << " successfully.\n";
    file.close();
  }
  /**
   * @brief Destroy the Test Case Builder object. If builder was not finalized
   * this also destroys the old existing file.
   *
   */
  virtual ~TestCaseBuilder() {
    if (this->file.is_open()) this->file.close();
    if (!this->finalized) {
      std::cerr << "Warning : Removing the unfinalized file " + fname + "\n";
      if (std::remove(this->fname.c_str()) != 0) {
        std::cerr << "Failed to remove Unfinalized file " << fname;
      };
    }
  }
};
}  // namespace maker
}  // namespace testcaser
#endif
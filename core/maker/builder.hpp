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
#ifndef __BUILDER_HPP__
#define __BUILDER_HPP__

#include <stdio.h>
#include <core/exceptions/BuildException.hpp>
#include <core/maker/randoms/RandomTypes.hpp>
#include <fstream>
#include <iostream>
#include <random>
#include <string>

#define NEW_LINE ('\n')

namespace testcaser {
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

 public:
  TestCaseBuilder() = delete;
  TestCaseBuilder(TestCaseBuilder&) = delete;
  TestCaseBuilder(TestCaseBuilder&&) = delete;
  /**
   * @brief Construct a new Test Case Builder object
   *
   * @param abs_name The Absolute name of the testfile to generate. it should be
   * a txt file
   */
  explicit TestCaseBuilder(std::string abs_name) : fname(abs_name) {
    file = std::ofstream(abs_name, std::ios::out);
    if (!file.is_open() || !file.good()) {
      throw testcaser::exceptions::maker::TestFileIOError(
          "File is Open : " + std::to_string(file.is_open()) +
          " :: File is Good : " + std::to_string(file.good()));
    }
    file.seekp(0, std::ios::beg);
  }
  /**
   * @brief Adds a new RandomAlphabet to the testcase file
   *
   * @tparam std::mt19937 The Random Number Engine to use to Generate Random
   * Characters defaults to std::mt19937
   * @tparam std::uniform_int_distribution<long long> The sistribution to use to
   * sample the generator's output. defaults to
   * std::uniform_int_distribution<..>
   * @param ra The reference to RandomAlphabet Type
   * @param ender Should we place new char at the end of random alphabet
   * @param use_only_lower Should we only generate lower case letters
   * @param use_only_upper Should we only generate upper case letters. You must
   * set use_only_lower to false
   * @param end_with the char to write after random character. if ender is true
   * @return char the character that was generated
   */
  template <class gen = std::mt19937,
            class dis = std::uniform_int_distribution<long long>>
  char add_new(types::RandomAlphabet<gen, dis>& ra, bool ender,
               bool use_only_lower = false, bool use_only_upper = false,
               char end_with = '\n') {
    if (this->finalized) {
      throw testcaser::exceptions::maker::FinalizationError(
          "Cannot add new alphabet once file has been finalized");
    }
    char u = ra.get();
    char v = ra.get_lower();
    char s = ra.get_upper();
    if (ender) {
      if (use_only_lower == use_only_upper) {
        file << u << end_with;
        return u;
      }
      if (use_only_lower) {
        file << v << end_with;
        return v;
      }
      if (use_only_upper) {
        file << s << end_with;
        return s;
      }
    } else {
      if (use_only_upper == use_only_lower) {
        file << u;
        return u;
      }
      if (use_only_lower) {
        file << v;
        return v;
      }
      if (use_only_upper) {
        file << s;
        return s;
      }
    }
  };
  /**
   * @brief Adds a new RandomInteger to the test file
   *
   * @tparam std::mt19937 the default random number engine to use
   * @tparam std::uniform_int_distribution<long long> the default distribution
   * to use to sample from random numbers
   * @param ri the Reference to the RandomIntger type
   * @param ender should random integer be followed by some char in file
   * @param end_with if ender, which character will follow the random number in
   * test file
   * @return long long the generated integer
   */
  template <class gen = std::mt19937,
            class dis = std::uniform_int_distribution<long long>>
  long long add_new(types::RandomInteger<gen, dis>& ri, bool ender,
                    char end_with = '\n') {
    if (this->finalized) {
      throw testcaser::exceptions::maker::FinalizationError(
          "Cannot add new line once file has been finalized");
    }
    long long res = ri.get();
    if (ender)
      file << res << end_with;
    else
      file << res;
    return res;
  };
  /**
   * @brief Adds a RandomBinary bit to test file
   *
   * @tparam std::mt19937 the engine to generate random number
   * @tparam std::uniform_int_distribution<unsigned long long> distribution to
   * sample the binary
   * @param ri Reference to RandomBinary object to use to generate the binary
   * number
   * @param ender should binary number be followed by some char in file
   * @param end_with if ender, what should it be followed by?
   * @return unsigned long long the generated random number
   */
  template <class gen = std::mt19937,
            class dis = std::uniform_int_distribution<unsigned long long>>
  unsigned long long add_new(types::RandomBinary<gen, dis>& ri, bool ender,
                             char end_with = '\n') {
    if (this->finalized) {
      throw testcaser::exceptions::maker::FinalizationError(
          "Cannot add new binary line once file has been finalized");
    }
    unsigned long long res = ri.get_as_int();
    if (ender)
      file << res << end_with;
    else
      file << res;
    return res;
  };
  /**
   * @brief Adds a RandomTernary to test file
   *
   * @tparam std::mt19937 the engine to generate random number
   * @tparam std::uniform_int_distribution<unsigned long long> the distribution
   * to sample random numbers from
   * @param ri Reference to RandomTernary object to use to generate the binary
   * number
   * @param ender should ternary number be followed by some char in file
   * @param end_with if ender, what should it be followed by?
   * @return unsigned long long the generated random number
   */
  template <class gen = std::mt19937,
            class dis = std::uniform_int_distribution<unsigned long long>>
  unsigned long long add_new(types::RandomTernary<gen, dis>& ri, bool ender,
                             char end_with = '\n') {
    if (this->finalized) {
      throw testcaser::exceptions::maker::FinalizationError(
          "Cannot add new ternary line once file has been finalized");
    }
    unsigned long long res = ri.get_as_int();
    if (ender)
      file << res << end_with;
    else
      file << res;
    return res;
  };
  /**
   * @brief Adds a RandomQuaternary to test file
   *
   * @tparam std::mt19937 the engine to generate random number
   * @tparam std::uniform_int_distribution<unsigned long long> the distribution
   * to sample random numbers from
   * @param ri Reference to RandomQuaternary object to use to generate the
   * binary number
   * @param ender should quaternary number be followed by some char in file
   * @param end_with if ender, what should it be followed by?
   * @return unsigned long long the generated random number
   */
  template <class gen = std::mt19937,
            class dis = std::uniform_int_distribution<unsigned long long>>
  unsigned long long add_new(types::RandomQuaternary<gen, dis>& ri, bool ender,
                             char end_with = '\n') {
    if (this->finalized) {
      throw testcaser::exceptions::maker::FinalizationError(
          "Cannot add new binary quaternary once file has been finalized");
    }
    unsigned long long res = ri.get_as_int();
    if (ender)
      file << res << end_with;
    else
      file << res;
    return res;
  };
  /**
   * @brief Adds a RandomQuinary to test file
   *
   * @tparam std::mt19937 the engine to generate random number
   * @tparam std::uniform_int_distribution<unsigned long long> the distribution
   * to sample random numbers from
   * @param ri Reference to RandomQuinary object to use to generate the binary
   * number
   * @param ender should Quinary number be followed by some char in file
   * @param end_with if ender, what should it be followed by?
   * @return unsigned long long the generated random number
   */
  template <class gen = std::mt19937,
            class dis = std::uniform_int_distribution<unsigned long long>>
  unsigned long long add_new(types::RandomQuinary<gen, dis>& ri, bool ender,
                             char end_with = '\n') {
    if (this->finalized) {
      throw testcaser::exceptions::maker::FinalizationError(
          "Cannot add new quinary line once file has been finalized");
    }
    unsigned long long res = ri.get_as_int();
    if (ender)
      file << res << end_with;
    else
      file << res;
    return res;
  };
  /**
   * @brief Adds a RandomSenery to test file
   *
   * @tparam std::mt19937 the engine to generate random number
   * @tparam std::uniform_int_distribution<unsigned long long> the distribution
   * to sample random numbers from
   * @param ri Reference to RandomSenery object to use to generate the binary
   * number
   * @param ender should senery number be followed by some char in file
   * @param end_with if ender, what should it be followed by?
   * @return unsigned long long the generated random number
   */
  template <class gen = std::mt19937,
            class dis = std::uniform_int_distribution<unsigned long long>>
  unsigned long long add_new(types::RandomSenary<gen, dis>& ri, bool ender,
                             char end_with = '\n') {
    if (this->finalized) {
      throw testcaser::exceptions::maker::FinalizationError(
          "Cannot add new senary line once file has been finalized");
    }
    unsigned long long res = ri.get_as_int();
    if (ender)
      file << res << end_with;
    else
      file << res;
    return res;
  };
  /**
   * @brief Adds a RandomUnsignedInteger to test file
   *
   * @tparam std::mt19937 the engine to generate random number
   * @tparam std::uniform_int_distribution<unsigned long long> the distribution
   * to sample random numbers from
   * @param rui Reference to RandomUnsignedInteger object to use to generate the
   * binary number
   * @param ender should unsigned Integer number be followed by some char in
   * file
   * @param end_with if ender, what should it be followed by?
   * @return unsigned long long the generated random number
   */
  template <class gen = std::mt19937,
            class dis = std::uniform_int_distribution<unsigned long long>>
  unsigned long long add_new(types::RandomUnsignedInteger<gen, dis>& rui,
                             bool ender, char end_with = '\n') {
    if (this->finalized) {
      throw testcaser::exceptions::maker::FinalizationError(
          "Cannot add new line once file has been finalized");
    }
    unsigned long long res = rui.get();
    if (ender)
      file << res << end_with;
    else
      file << res;
    return res;
  };
  /**
   * @brief Adds a RandomTernary to test file
   *
   * @tparam T the type to choose the from.
   * @tparam std::mt19937 the engine to generate random number
   * @tparam std::uniform_int_distribution<unsigned long long> the distribution
   * to sample random numbers from
   * @param rft Reference to RandomTernary object to use to generate the binary
   * number
   * @param ender should ternary number be followed by some char in file
   * @param end_with if ender, what should it be followed by?
   * @return T the generated random value from given list of values
   */
  template <class T, class gen = std::mt19937,
            class dis = std::uniform_int_distribution<unsigned long long>>
  T add_new(types::RandomFrom<T, gen, dis>& rft, bool ender,
            char end_with = '\n') {
    if (this->finalized) {
      throw testcaser::exceptions::maker::FinalizationError(
          "Cannot add new line once file has been finalized");
    }
    auto res = rft.get();
    if (ender)
      file << res << end_with;
    else
      file << res;
    return res;
  };

  /**
   * @brief Adds a single space to file
   *
   */
  void add_single_space() {
    if (this->finalized) {
      throw testcaser::exceptions::maker::FinalizationError(
          "Cannot add space once file has been finalized");
    }
    file << ' ';
  };
  /**
   * @brief Adds a special character to file
   *
   * @param chr the character to add
   * @param ender should the character be followed by another character
   * @param end_with if ender? which character will follow it
   */
  void add_special_character(char chr, bool ender, char end_with = '\n') {
    if (this->finalized) {
      throw testcaser::exceptions::maker::FinalizationError(
          "Cannot add special character once file has been finalized");
    }
    if (ender)
      file << chr << end_with;
    else
      file << chr;
  };
  /**
   * @brief Adds a new line to the file
   *
   */
  void add_new_line() {
    if (this->finalized) {
      throw testcaser::exceptions::maker::FinalizationError(
          "Cannot add new line once file has been finalized");
    }
    file << std::endl;
  }
  /**
   * @brief Finalizes the file so that no new changes or addition can be done on
   * the file
   *
   */
  void finalize() {
    this->finalized = true;
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
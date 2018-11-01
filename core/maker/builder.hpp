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
class TestCaseBuilder {
  std::ofstream file;
  bool finalized = false;
  std::string fname;

 public:
  TestCaseBuilder() = delete;
  TestCaseBuilder(TestCaseBuilder&) = delete;
  TestCaseBuilder(TestCaseBuilder&&) = delete;
  explicit TestCaseBuilder(std::string abs_name) : fname(abs_name) {
    file = std::ofstream(abs_name, std::ios::out);
    if (!file.is_open() || !file.good()) {
      throw testcaser::exceptions::maker::TestFileIOError(
          "File is Open : " + std::to_string(file.is_open()) +
          " :: File is Good : " + std::to_string(file.good()));
    }
    file.seekp(0, std::ios::beg);
  }

  template <class gen = std::mt19937,
            class dis = std::uniform_int_distribution<long long>>
  char add_new(types::RandomAlphabet<gen, dis>& ra, bool ender,
               bool use_only_lower = false,
               bool use_only_upper = false, char end_with = '\n') {
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
      } if (use_only_lower) {
        file << v << end_with;
        return v;
      } if (use_only_upper) {
        file << s << end_with;
        return s;
      }
    } else {
      if (use_only_upper == use_only_lower) {
        file << u;
        return u;
      } if (use_only_lower) {
        file << v;
        return v;
      } if (use_only_upper) {
        file << s;
        return s;
      }
    }
  };
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
  template <class gen = std::mt19937,
            class dis = std::uniform_int_distribution<unsigned long long>>
  unsigned long long add_new(types::RandomBinary<gen, dis>& ri,
                             bool ender, char end_with = '\n') {
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
  template <class gen = std::mt19937,
            class dis = std::uniform_int_distribution<unsigned long long>>
  unsigned long long add_new(types::RandomTernary<gen, dis>& ri,
                             bool ender, char end_with = '\n') {
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
  template <class gen = std::mt19937,
            class dis = std::uniform_int_distribution<unsigned long long>>
  unsigned long long add_new(types::RandomQuaternary<gen, dis>& ri,
                             bool ender, char end_with = '\n') {
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
  template <class gen = std::mt19937,
            class dis = std::uniform_int_distribution<unsigned long long>>
  unsigned long long add_new(types::RandomQuinary<gen, dis>& ri,
                             bool ender, char end_with = '\n') {
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
  template <class gen = std::mt19937,
            class dis = std::uniform_int_distribution<unsigned long long>>
  unsigned long long add_new(types::RandomSenary<gen, dis>& ri,
                             bool ender, char end_with = '\n') {
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

  void add_single_space() {
    if (this->finalized) {
      throw testcaser::exceptions::maker::FinalizationError(
          "Cannot add space once file has been finalized");
    }
    file << ' ';
  };
  void add_special_character(char chr, bool ender,
                             char end_with = '\n') {
    if (this->finalized) {
      throw testcaser::exceptions::maker::FinalizationError(
          "Cannot add special character once file has been finalized");
    }
    if (ender)
      file << chr << end_with;
    else
      file << chr;
  };
  void add_new_line() {
    if (this->finalized) {
      throw testcaser::exceptions::maker::FinalizationError(
          "Cannot add new line once file has been finalized");
    }
    file << std::endl;
  }
  void finalize() {
    this->finalized = true;
    file.close();
  }
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
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
namespace testcaser {
namespace maker {
class TestCaseBuilder {
  std::ofstream file;
  bool finalized = false;
  std::string fname;

 public:
  TestCaseBuilder() = delete;
  TestCaseBuilder(std::string& abs_name) : fname(abs_name) {
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
  TestCaseBuilder& add_new_line(types::RandomAlphabet<gen, dis>& ra,
                                char end_with = '\n') {
    if (this->finalized) {
      throw testcaser::exceptions::maker::FinalizationError(
          "Cannot add new line once file has been finalized");
    }
    file << ra.get() << end_with;
    return *this;
  };
  template <class gen = std::mt19937,
            class dis = std::uniform_int_distribution<long long>>
  TestCaseBuilder& add_new_line(types::RandomInteger<gen, dis>& ri,
                                char end_with = '\n') {
    if (this->finalized) {
      throw testcaser::exceptions::maker::FinalizationError(
          "Cannot add new line once file has been finalized");
    }
    file << ri.get() << end_with;
    return *this;
  };
  template <class gen = std::mt19937,
            class dis = std::uniform_int_distribution<unsigned long long>>
  TestCaseBuilder& add_new_line(types::RandomUnsignedInteger<gen, dis>& rui,
                                char end_with = '\n') {
    if (this->finalized) {
      throw testcaser::exceptions::maker::FinalizationError(
          "Cannot add new line once file has been finalized");
    }
    file << rui.get() << end_with;
    return *this;
  };
  template <class T, class gen = std::mt19937,
            class dis = std::uniform_int_distribution<unsigned long long>>
  TestCaseBuilder& add_new_line(types::RandomFrom<T, gen, dis>& rft,
                                char end_with = '\n') {
    if (this->finalized) {
      throw testcaser::exceptions::maker::FinalizationError(
          "Cannot add new line once file has been finalized");
    }
    file << rft.get() << end_with;
    return *this;
  };

  TestCaseBuilder& add_single_space() {
    if (this->finalized) {
      throw testcaser::exceptions::maker::FinalizationError(
          "Cannot add space once file has been finalized");
    }
    file << ' ';
    return *this;
  };
  TestCaseBuilder& add_special_character(char chr, char end_with = '\n') {
    if (this->finalized) {
      throw testcaser::exceptions::maker::FinalizationError(
          "Cannot add special character once file has been finalized");
    }
    file << chr << end_with;
    return *this;
  };
  TestCaseBuilder& add_new_line() {
    if (this->finalized) {
      throw testcaser::exceptions::maker::FinalizationError(
          "Cannot add new line once file has been finalized");
    }
    file << std::endl;
    return *this;
  }
  TestCaseBuilder& finalize() {
    this->finalized = true;
    file.close();
  }
  virtual ~TestCaseBuilder() {
    if (this->file.is_open()) this->file.close();
    if (!this->finalized) {
      if (std::remove(this->fname.c_str()) != 0) {
        std::cerr << "Failed to remove Unfinalized file " << fname;
      };
    }
  }
};
}  // namespace maker
}  // namespace testcaser
#endif
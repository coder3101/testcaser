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

#ifndef __BASE_EXCEPTION_HPP
#define __BASE_EXCEPTION_HPP

#include <exception>
#include <string>

namespace testcaser {
namespace exceptions {
class BaseException : public std::exception {
  const char *message;
  std::string possible_resolution;
  bool is_resolvable;

 protected:
  std::string more_info;

 public:
  BaseException() = delete;
  BaseException(std::string reason) : message(reason.c_str()) {
    this->is_resolvable = false;
  }
  void set_resolution(std::string resolution) {
    this->possible_resolution = resolution;
    this->is_resolvable = true;
  }
  virtual void add_more_info() = 0;

  virtual const char *what() const noexcept final override {
    std::string m2 = "\nAn Exception occured :  " + std::string(message) +
                     ".\nMore Information : " + more_info;
    if (this->is_resolvable)
      m2 += ". Possible Resolution : " + possible_resolution;
    return m2.c_str();
  }
};
}  // namespace exceptions
}  // namespace testcaser
#endif

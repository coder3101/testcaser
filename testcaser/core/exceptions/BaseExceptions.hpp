/**
 *   Copyright 2019 Ashar <ashar786khan@gmail.com>
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
/**
 * @brief The Main Exception namespace that holds the exceptions that are
 * generated by the testcaser
 *
 */
namespace exceptions {
/**
 * @brief The Base Abstract exception class. All the Exceptions that will be
 * thrown by the library will be inherited from this class.
 *
 */
class BaseException : public std::exception {
  std::string message;
  std::string possible_resolution, *m2 = nullptr;

 protected:
  /**
   * @brief more_info contains more information about the Exception that shook
   * the framework
   *
   */
  std::string more_info;

 public:
  BaseException() = delete;
  /**
   * @brief Construct a new Base Exception object
   *
   * @param reason The message that will be carry forwarded to the what(). It
   * usually specifies the reason of the exception
   */
  BaseException(std::string reason) : message(reason) {}
  /**
   * @brief Set the resolution string
   *
   * @param resolution If this error is generic and can be resolved. Help user
   * with tips to fix this fatal exception
   */
  void set_resolution(std::string resolution) {
    this->possible_resolution = resolution;
  }
  /**
   * @brief A pure virtual function that must be overridden by decendants.
   *
   */
  virtual void add_more_info() = 0;

  /**
   * @brief The final reason for the exception
   *
   * @return const char* The message of the exception
   */
  virtual char const *what() const noexcept final override {
    std::string *m2 = new std::string();
    *m2 = "\n" + std::string(message) + ".\nMore Information : " +
          (more_info.length() == 0 ? "No Information" : more_info);
    *m2 = *m2 + std::string("\nPossible Resolution : ") +
          (possible_resolution.length() == 0 ? "No Information"
                                             : possible_resolution);
    return m2->c_str();
  }
  /**
   * @brief Destroy the Base Exception object
   *
   */
  ~BaseException() { delete m2; }
};
}  // namespace exceptions
}  // namespace testcaser
#endif

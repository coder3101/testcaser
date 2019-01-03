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

#ifndef __BUILD_EXCEPTION_HPP__
#define __BUILD_EXCEPTION_HPP__

#include <testcaser/core/exceptions/BaseExceptions.hpp>

namespace testcaser {
namespace exceptions {
namespace maker {
/**
 * @brief TestFileIOError exception is thrown as soon as new test-case file
 * failed to open or was opened in s state that does not offers write the file
 *
 */
class TestFileIOError final : public BaseException {
  std::string tmp;

 public:
  /**
   * @brief Construct a new Test File I O Error object
   *
   * @param details A Generic message for exception
   */
  TestFileIOError(std::string details)
      : BaseException("FileIOError : Unable to open file in write mode"),
        tmp(details) {}
  /**
   * @brief adds more information to exception such as what was expected and
   * what was provided.
   *
   */
  void add_more_info() final override { this->more_info = this->tmp; }
};
/**
 * @brief Exception that is thrown when a finalized builder is modified with
 * add_line(..)
 *
 */
class FinalizationError final : public BaseException {
  std::string tmp;

 public:
  /**
   * @brief Construct a new Finalization Error object
   *
   * @param details Generic message to show to use for the exception
   */
  FinalizationError(std::string details)
      : BaseException(
            "FinalizationError : No action is allowed after file has been "
            "finalized."),
        tmp(details) {}
  /**
   * @brief Extra details that shows the state that caused the exception
   *
   */
  void add_more_info() final override { this->more_info = this->tmp; }
};
}  // namespace maker
}  // namespace exceptions
}  // namespace testcaser
#endif
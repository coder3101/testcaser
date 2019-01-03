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

#ifndef __INVALID_LIMIT_HPP__
#define __INVALID_LIMIT_HPP__

#include <testcaser/core/exceptions/BaseExceptions.hpp>

namespace testcaser {
namespace exceptions {
namespace maker {
/**
 * @brief Exception that is raised when an invalid limit is given to any Random
 * class
 *
 */
class LimitError final : public testcaser::exceptions::BaseException {
  std::string tmp;

 public:
  /**
   * @brief Construct a new Limit Error object
   *
   * @param details the Generic Error type message
   */
  LimitError(std::string details)
      : BaseException("LimitError : Lower bound exceeds upper bound"),
        tmp(details) {}
  /**
   * @brief The Error message that will be shown to the user that explains the
   * actual state of the exception
   *
   */
  void add_more_info() final override { this->more_info = this->tmp; }
};

/**
 * @brief Exception that is raised when an Interval setting to limits are
 * ambigious
 *
 */
class LimitIntervalError final : public testcaser::exceptions::BaseException {
  std::string tmp;

 public:
  /**
   * @brief Construct a new Limit Interval Error object
   *
   * @param details the Generic message type for the exception
   */
  LimitIntervalError(std::string details)
      : testcaser::exceptions::BaseException(
            "LimitIntervalError : Interval out of Range"),
        tmp(details) {}
  /**
   * @brief Adds more information that explains the stat of the exception
   *
   */
  void add_more_info() final override { this->more_info = this->tmp; }
};

/**
 * @brief Exception that is thrown when all interval exceptions have exhaused
 * the limit size
 *
 */
class LimitExhaustedError final : public testcaser::exceptions::BaseException {
  std::string tmp;

 public:
  /**
   * @brief Construct a new Limit Exhausted Error object
   *
   * @param details the Generic message for the exception
   */
  LimitExhaustedError(std::string details)
      : testcaser::exceptions::BaseException(
            "LimitExhaustedError : Exception Intervals Exhausted limit"),
        tmp(details) {}
  /**
   * @brief More information about the state in which exception was raised
   *
   */
  void add_more_info() final override { this->more_info = this->tmp; }
};
}  // namespace maker
}  // namespace exceptions
}  // namespace testcaser
#endif

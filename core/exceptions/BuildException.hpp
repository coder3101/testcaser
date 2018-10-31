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

#ifndef __BUILD_EXCEPTION_HPP__
#define __BUILD_EXCEPTION_HPP__

#include <core/exceptions/BaseExceptions.hpp>

namespace testcaser {
namespace exceptions {
namespace maker {
class TestFileIOError final : public BaseException {
  std::string tmp;

 public:
  TestFileIOError(std::string details)
      : BaseException("FileIOError : Unable to open file in write mode"),
        tmp(details) {}
  void add_more_info() final override { this->more_info = this->tmp; }
};

}  // namespace maker
}  // namespace exceptions
}  // namespace testcaser
#endif
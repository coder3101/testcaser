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

#include<core/maker/randoms/RandomTypes.hpp>
#include<string>
#include<core/exceptions/BuildException.hpp>
namespace testcaser {
namespace maker {
class TestCaseBuilder {
    public:
    TestCaseBuilder() = delete;
    TestCaseBuilder(std::string &);
    unsigned long long add_test_case_count(unsigned long long);
    unsigned long long add_test_case_count(types::RandomUnsignedInteger&);
    void start_single_test_case_format();
    void add_new_line(types::RandomAlphabet<>&);
    void add_new_line(types::RandomInteger<>&);
    void add_new_line(types::RandomUnsignedInteger<>&);
    void add_single_space();
    void add_special_character(char);
    void add_new_line();
    void stop_single_test_case();
    void repeat_for_all_test_case_count();




};
}  // namespace maker
}  // namespace testcaser
#endif
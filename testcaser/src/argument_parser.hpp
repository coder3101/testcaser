/**
 * Copyright 2018-2019 Ashar <ashar786khan@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ARGUMENT_PARSER_HPP
#define ARGUMENT_PARSER_HPP

#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

namespace testcaser {
namespace internals {

class ArgumentParser {
  int count;
  std::vector<std::string> args;

 public:
  ArgumentParser(int argc, char *argv[]) {
    count = argc - 1;
    for (int t = 1; t < argc; t++)
      args.push_back(std::string(static_cast<char const *>(argv[t])));

    if (!args.size() % 2)
      throw std::length_error(
          "Argument Count mismatch. Did you forgot to specifiy a value for a "
          "flag.");
  }

  std::unordered_map<std::string, std::string> parse() {
    std::unordered_map<std::string, std::string> map;
    for (int t = 0; t < args.size() - 1; t += 2)
      map[args[t].substr(2, std::string::npos)] = args[t + 1];
    return map;
  }

  static bool handle_version(int argv, char *argc[],
                             std::function<void()> callback) {
    if (argv > 2 || argv == 1) return false;
    if (std::string(argc[1]) != "--version") return false;
    callback();
    return true;
  }

  static bool handle_help(int argv, char *argc[],
                          std::function<void()> callback) {
    if (argv == 1) {
      std::cerr << "You must specify --program and --input for judge to run\n";
      return true;
    }
    if (argv > 2)
      return false;
    else {
      callback();
      return true;
    }
  }
};
}  // namespace internals
}  // namespace testcaser
#endif

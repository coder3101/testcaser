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

#include <iostream>
#include <stdexcept>
#include <testcaser/integrator>
#include <testcaser/src/argument_parser.hpp>

using std::cin;
using std::cout;
using std::endl;

using testcaser::integrator::VirtualJudge;
using testcaser::internals::ArgumentParser;

void show_version() { cout << "Virtual Judge 0.4.1-beta" << std::endl; }

void show_help() {
  cout
      << "\n--program <executable_path> (*) : Specifies the path of executable "
         "or a script to be judged by the Virtual Judge.\n\n";
  cout << "--input <input_path> (*) : Specifies the path of input file. The "
          "Program will read from this file.\n\n";
  cout << "--output <output_path> : Specifies the path of output file. The "
          "Program will write to this file. If unspecified program will write "
          "to console.\n\n";
  cout << "--memory <number> : Sets the memory limit in MB for the Program. "
          "This is defaulted to 256 MB.\n\n";
  cout << "--time <number> : Sets the time limit in seconds for the Program. "
          "This is defaulted to 1 second.\n\n";
  cout << "--help : Shows this message.\n\n";
  cout << "--version : Shows the current version of the Virtual Judge "
          "Installed.\n\n";
  cout << "NOTE :: IF YOU MIS-SPELL ANY ARGUMENT. VIRTUAL JUDGE WILL SILENTLY "
          "SKIP THAT AND SET THE DEFAULT VALUE FOR THAT ARGUMENT. THE (*) "
          "MEANS A REQUIRED ARGUMENT.\n\n";
}

int main(int argv, char* argc[]) {
  bool handled = ArgumentParser::handle_version(argv, argc, show_version);
  if (handled) return EXIT_SUCCESS;
  handled = ArgumentParser::handle_help(argv, argc, show_help);
  if (handled) return EXIT_SUCCESS;
  try {
    auto map = ArgumentParser(argv, argc).parse();
    if (map.find("program") == map.end()) {
      std::cerr << "Opps!! You missed to specify the --program\n";
      return EXIT_FAILURE;
    }
    if (map.find("input") == map.end()) {
      std::cerr << "Opps!! You missed to specify the --input\n";
      return EXIT_FAILURE;
    }
    VirtualJudge judge;

    judge.set_binary(map["program"]);
    judge.set_input_file(map["input"]);

    if (map.find("time") != map.end())
      judge.set_time_limit(std::stoi(map["time"]));
    if (map.find("memory") != map.end())
      judge.set_memory_limit(std::stoi(map["memory"]) * 1024);
    if (map.find("output") != map.end()) judge.set_output_file(map["output"]);

    auto result = judge.execute();
    cout << "\n";
    result.print_result();
    return 0;
  } catch (std::exception &e) {
    std::cerr << "Opps!! Your arguments are not correct.\n"<<"Cause : "<<e.what()<<"\n";
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;

  /**
   * @todo Fails to Remove the Environment Variable from System
   * @body The Install Script and Uninstall Scripts are not working
   * in the Windows. This issue is related to #15
   */
}
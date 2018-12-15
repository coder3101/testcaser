# TestCaser

---
[![Build Status](https://travis-ci.org/coder3101/testcaser.svg?branch=master)](https://travis-ci.org/coder3101/testcaser) 
[![CocoapodsMetrics](https://img.shields.io/cocoapods/metrics/doc-percent/AFNetworking.svg)](https://coder3101.github.io/testcaser) 
[![GitHub commit merge status](https://img.shields.io/github/commit-status/badges/shields/master/5d4ab86b1b5ddfb3c4a70a70bd19932c52603b8c.svg)](https://coder3101.github.io/testcaser) 
[![](https://img.shields.io/hexpm/l/plug.svg)](https://github.com/coder3101/testcaser/blob/master/LICENSE) 
[![](https://img.shields.io/badge/release-v0.1--alpha-blue.svg)](https://github.com/coder3101/testcaser/releases/tag/v0.1-alpha)




TestCaser is a header-only light-weight test case maker library written in C++. It is easy, flexible and powerful library that can generate testcases, run your program on those test cases and compare two program's output for the given test case files and lists down the input that causes a different output to be produced. These features can come in handy when you are stuck on some corner cases for a problem or when you want to check your program on valid random inputs. TestCaser has three submodules namely maker, integrator and comparator (comparator is not developed yet). Maker module is used to generate test cases. Integrator integrates a program to accept the test cases made by maker. Comparator compares two program's outputs for given inputs.

---

## Installation

TestCaser is only available on github. You need to download it to your local machine to use it.
Run this command from your preferred directory (say downloads) on command line

```bash
wget https://github.com/coder3101/testcaser/archive/v0.1-alpha.zip && unzip v0.1-alpha.zip && cd testcaser-0.1-alpha
```

Running the above command will download the testcaser respository unzip it and switch to and switch to that directory.

There is no need to Compile the Source code. It is Header only hence you only need to specify to compiler the path of the testcaser. By default C++ compilers look at `/usr/include` for includes in a program. So we need to move testcaser to that directory.

We provide two bash scripts along with the source code namely `unix_install.sh` and `unix_uninstall.sh` To install the testcaser on a linux machine run the install script as a superuser.

You are invited to check the scripts before you run them.

```bash
sudo ./unix_install.sh
```

Type in your password and wait for the script to install the testcaser.

If you get any Error make sure that scripts are executable by running

```bash
sudo chmod +x unix_install.sh && sudo chmod +x unix_uninstall.sh
```

Now you can re-run the install script. If you are non-linux or you don't want to install testcaser. You can specify the location using -I flag of g++ or clang++.

---

## Writing your First TestCase

```cpp
#include <testcaser/maker>

using testcaser::maker::TestCaseBuilder;
using testcaser::maker::types::RandomUnsignedInteger;

int main() {
  TestCaseBuilder builder("./test.txt");

  RandomUnsignedInteger<> a({1, 100000});
  RandomUnsignedInteger<> b({1, 100});
  RandomUnsignedInteger<> t({1, 10});

  auto tt = builder.add(t);
  builder.add_line();

  for (int p = 0; p < tt; p++) {
    builder.add(a);
    builder.add_space();
    builder.add(b);
    builder.add_line();
  }

  builder.finalize();

  return 0;
}
```

It generates a testcaser binary for the problem given below. Everytime you execute this binary it will generate a test case valid random file.

>> **Input Format**
>> 
>> The first contains T denoting the number of testcase Each test case contains two space
>> separated Integer A and B
>>
>> **Constraints**
>>
>> 1 <= A < 100000
>>
>> 1 <= B < 100
>>
>> 1 <= T < 10

For Code Explaination and more information. Read the docs [here](https://coder3101.github.io/testcaser)

## Writing your First VirtualJudge

```cpp
#include <testcaser/integrator>

using testcaser::integrator::VirtualJudge;

int main() {
  const std::string root = "./testcaser/core/integrator/tests/";
  VirtualJudge()
      .set_binary(root + "program.out")
      .set_input_file(root + "input.txt")
      .set_output_file(root + "output2.txt")
      .set_time_limit(5)
      .set_memory_limit(1024*25)
      .execute()
      .print_result();
  return 0;
}
```

It Generates a binary which when executed tests if the `program.out` runs before 5 seconds and under 25 MB memory on `input.txt`. It also creates a `output2.txt` file which contains
the output from the program. 

Here is a Sample Output that it will generate.
```
>>> Child Process created with pid 19398
>>> Setting the time constraint to 5 seconds
>>> Process will be killed if not returned before 5 second
>>> Executing ./testcaser/core/integrator/tests/program.out on child process.
>>> Completed the child process with exit code 0

************** RESULTS ***************
Allocted Virtual Memory : 25600 KB (25 MB)
Physical Memory Used    : 3412 KB (3.33203 MB)
Virtual Memory Used     : 20364 KB (19.8867 MB)
Allocated Time          : 5 second(s)
Execution Time          : 0.112149 second(s)
Exit Code               : 0
Remark                  : Success. Ran under memory and time limit
***************************************
```

For Code Explaination and more information. Read the docs [here](https://coder3101.github.io/testcaser)

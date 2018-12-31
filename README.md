# TestCaser

---

| Platform | CI Status                                                                                                                                                            |
| -------- | :------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| OSX      | [![OSX Build Status](http://badges.herokuapp.com/travis/coder3101/testcaser?env=BADGE=osx&label=build&branch=master)](https://travis-ci.org/coder3101/testcaser)     |
| Linux    | [![Linux Build Status](http://badges.herokuapp.com/travis/coder3101/testcaser?env=BADGE=linux&label=build&branch=master)](https://travis-ci.org/coder3101/testcaser) |
| Windows | [![Build status](https://ci.appveyor.com/api/projects/status/kkggh13ohwi6w6qi/branch/master?svg=true)](https://ci.appveyor.com/project/coder3101/testcaser/branch/master)



[![CocoapodsMetrics](https://img.shields.io/badge/docs-100%25-yellow.svg)](https://coder3101.github.io/testcaser) 
[![LICENSE](https://img.shields.io/hexpm/l/plug.svg)](https://github.com/coder3101/testcaser/blob/master/LICENSE) 
[![RELEASE](https://img.shields.io/badge/release-v0.4.1--beta-orange.svg)](https://github.com/coder3101/testcaser/releases/tag/v0.4.1-beta)




TestCaser is a header-only light-weight test case maker library written in C++. It is easy, flexible and powerful library that can generate testcases, run your program on those test cases and compare two program's output for the given test case files and lists down the input that causes a different output to be produced. These features can come in handy when you are stuck on some corner cases for a problem or when you want to check your program on valid random inputs. TestCaser has three submodules namely maker, integrator and comparator (comparator is not developed yet). Maker module is used to generate test cases. Integrator integrates a program to accept the test cases made by maker. Comparator compares two program's outputs for given inputs. We also offer command a compiled virtualjudge binary which can be installed along side of the library.

---

## Installation of Library

*For Updating the Version You need to First Uninstall the previous version and reinstall the new version.*

### For Linux and MACOS

TestCaser is only available on github. You need to download it to your local machine to use it.
Run this command from your preferred directory (say downloads) on command line

```bash
wget https://github.com/coder3101/testcaser/archive/v0.4.1-beta.zip && unzip v0.4.1-beta.zip && cd testcaser-0.4.1-beta
```

Running the above command will download the testcaser respository unzip it and switch to that directory.

There is no need to Compile the Source code. It is Header only hence you only need to specify to compiler the path of the testcaser. By default C++ compilers look at `/usr/include/` or `/usr/local/include/` for includes in a program. So we need to move testcaser to that directory.

We provide two bash scripts along with the source code namely `install.sh` and `uninstall.sh` To install the testcaser on a your machine run the install script as a superuser.

You are invited to check the scripts before you run them.

```bash
sudo ./install.sh
```

Type in your password and wait for the script to install the testcaser. You will be asked if you want to install `virtualjudge` as well. Depending upon the choice, script will install the requested components.  

If you get any Error make sure that scripts are executable by running

```bash
sudo chmod +x install.sh && sudo chmod +x uninstall.sh
```

You can also specify the location using -I flag of g++ or clang++.

### For Windows

Download the sources in a zip format from [here](https://github.com/coder3101/testcaser/archive/v0.4.1-beta.zip) and unzip it at your preferred  location. Since testcase is Header-only you can simply use `-I\path\to\testcaser\root` flag while compiling with any C++ compiler. Make sure you enforce `-std=c++11` as well.


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

It generates a testcaser binary for the problem given below. Everytime you execute this binary it will generate a random-valued test case file.

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

## Installation of Binary

### For Linux and MACOS

It can difficult at times to write a complete VirtualJudge Program, so we provide a pre-compiled virtual judge binary `virtualjudge` for you to quickly judge your programs. Once you run the install script it will install testcaser and asks you to install `virtualjudge`, if installed it can be invoked from command line.

### For Windows

You can install the VirtualJudge Binary by running `install.bat` and remove it by running `uninstall.bat` **Run them from the root of the testcaser** . It will set/unset the path of virtualbinary in your environment variable. So that you can use it from command line.

## Checking the Installation

You can check if virtual judge is correctly installed or not by running.

```bash
virtualjudge --version
```

It will show the version of testcaser upon which this virtualjudge was compiled.

Using virtualjudge is as easy as a cake. To run the judge you need to provide at least 2 arguments, a simple virtualjudge invocation will look like

```bash
virtualjudge --program your_executable --input your_input_file.txt
```

`your_executable` is the path to a executable or the python script with `.py` extension.

`your_input_file.txt` is the path of the file that contains the input for the program.

You can also set the time limit and memory limit for the judge as

```bash
virtualjudge --program executable \
             --input input.txt \
             --output output.txt \
             --time 5 \
             --memory 256
```

`--time` takes value in seconds and `--memory` takes value in Megabytes (MB). 

For More Information You can run `virtualjudge --help`.
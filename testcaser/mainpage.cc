/**
 *
 *  \mainpage Getting started with TestCaser
 * \warning
 *  TestCaser is still in Beta
 *
 *  \warning
 *  This library is based on C++11. Make sure while compiling you use the flag
 *  <b>-std=c++11</b>
 *
 *  \tableofcontents
 *  \section sec_intro Introduction
 *
 *  TestCaser is a header-only light-weight test case maker library written in
 *  C++. It is easy, flexible and powerful library that can generate testcases,
 *  run your program on those test cases and compare two program's output for
 *  the
 *  given test case files and lists down the input that causes a different
 *  output to be produced.
 *  These features can come in handy when you are stuck on some corner cases for
 *  a problem or
 *  when you want to check your program on valid random inputs.
 *  TestCaser has three submodules namely maker, integrator and comparator
 *  (comparator is not developed yet).
 *  Maker module is used to generate test cases. Integrator integrates a
 *  program to accept the test cases made by maker.
 *  Comparator compares two program's outputs for given inputs. 
 *  We also offer command a compiled virtualjudge binary which can be 
 *  installed along side of the library.
 *
 *  Enough Let's get you started with TestCaser.
 * 
 * ---
 *
 *  \section sec_install Installation
 *  \subsection step1 Step 1
 *   TestCaser is only available on github. You need to clone it to your local
 * machine to use it.
 *
 *  Run this command from your preferred directory (say downloads) on command
 * line
 *  \code{.sh}
 *  git clone https://github.com/coder3101/testcaser.git && cd testcaser
 *  \endcode
 *  Running the above command will download the testcaser repository and switch
 * to that directory.
 *
 *  \subsection step2 Step 2
 *  There is no need to Compile the Source code. It is Header only hence you
 * only need to
 *  specify to the compiler the path of the testcaser. By default C++ compilers
 * look at `/usr/include` or `usr/local/include`
 *  for includes in a program. So we need to move testcaser to that directory.
 *
 *  We provide two bash scripts along with the source code namely <a
 * href="https://github.com/coder3101/testcaser/blob/master/install.sh"><b>install.sh</b></a>
 * and <a
 * href="https://github.com/coder3101/testcaser/blob/master/uninstall.sh"><b>uninstall.sh</b></a>
 *  To install the testcaser on a linux machine <b>run the install script as a
 * superuser</b>.
 *
 *  You are invited to check the scripts before you run them.
 *
 *  \code{.sh}
 *  sudo ./install.sh
 *  \endcode
 *
 *  Type in your password and wait for the script to install the testcaser.  
 *  You will be asked if you want to install `virtualjudge` as well. 
 *  Depending upon the choice, script will install the requested components.
 *
 *  If you get any Error make sure that scripts are executable by running
 *  \code{.sh}
 *  sudo chmod +x install.sh && sudo chmod +x uninstall.sh
 *  \endcode
 *
 *  Now you can re-run the install script.
 *  If you are non-linux or you don't want to install testcaser. You can specify
 * the location using `-I` flag of `g++`.
 * 
 * ---
 *
 *  \section started Your First Test Case
 *  Now that you have testcaser Installed Let's get you started with a simple
 *  program.
 *
 * Here is a simple program that generates test cases for following
 * problem
 * <BLOCKQUOTE>
 * <b>Input Format</b>
 *
 * The first contains T denoting the number of testcase
 * Each test case contains two space separated Integer A and B
 *
 * <b>Constraints</b>
 *
 * 1 <= A < 100000
 *
 * 1 <= B < 100
 *
 * 1 <= T < 10
 * </BLOCKQUOTE>
 *
 * \code{.cpp}
 *
 * #include <testcaser/maker>
 *
 * using testcaser::maker::TestCaseBuilder;
 * using testcaser::maker::types::RandomUnsignedInteger;
 *
 * int main() {
 * TestCaseBuilder builder("./test.txt");
 *
 * RandomUnsignedInteger<> a({1, 100000});
 * RandomUnsignedInteger<> b({1, 100});
 * RandomUnsignedInteger<> t({1, 10});
 *
 * auto tt = builder.add(t);
 * builder.add_line();
 *
 * for (int p = 0; p < tt; p++) {
 *   builder.add(a);
 *   builder.add_space();
 *   builder.add(b);
 *   builder.add_line();
 * }
 *
 * builder.finalize();
 *
 * return 0;
 * }
 *  \endcode
 *
 * Compile  and Run it. You will have a <b>test.txt</b> test case file with the
 * test cases in the specifed
 * format. Rerun it to generate different valued test case file.
 * 
 * ---
 *
 * \section under_standing Understanding Your Program
 * <b>Line 1</b> : Includes the `testcaser/maker` module into your program
 *
 * <b>Line 2</b> : Brings in the TestCaseBuilder from its namespace to your
 * program. TestCaseBuilder is the object responsible for creating and writing
 * into the file.
 *
 * <b>Line 3</b> : Brings RandomUnsignedInteger from its namespace.
 * Our Values of A,B and T are all unsigned so we are bring the
 * RandomUnsignedInteger
 * class. It is responsible for generating the random numbers.
 *
 * <b>Line 4 </b> : Starting the main
 *
 * <b>Line 5 </b> : Creating the object of the TestCaseBuilder. It takes a
 * string path & name of the file to write. In our case <b>test.txt</b>
 * in current working directory.
 *
 * <b>Line 6-8 </b> : Creates RandomUnsignedInteger Objects corresponding
 * to A,B,T in Question. We specifed the limits of those random integers
 * For testcase value t, the limit is set to [0,10) and so on.
 *
 * <b>Line 9 </b> : We follow the sequence as mentioned in the problem
 * statement. First line contains t denoting the number of test case. We write a
 * variable by calling `builder.add(t)` and it returns the value that was
 * written
 * in the file.
 * In this case it will return a number in [0,10) denoting testcase of the
 * problem.
 *
 * <b>Line 10</b> : Now we need a new  line after this testcase count.
 *  So we add a new line in the file
 *
 * <b>Line 11-16 </b> : We now repeat for each testcase in a for loop.
 * Remember `tt` is the number of testcase written to file. For Each test
 * case we write 'a' and then put space and write 'b' then give a new line.
 * You can check from the problem statement it was the input format.
 *
 * <b>Line 16-18 </b> : Finally after we have written everything it is important
 * to finalize the builder by calling `builder.finalize()` and return from main.
 *
 * <BLOCKQUOTE>
 * <b>It is important to finalize the builder before the builder goes out of
 * scope. if you forget the file will not be written.
 * </b>
 * </BLOCKQUOTE>
 * 
 * ---
 *
 * \section virtual_judge Your Virtual Judge
 * We provide a simulator in testcaser that can simulate an Online Judge, like
 * that of codeforces or codechef.
 * You can check if your program runs on time and memory limit of the problem or
 * not.
 * Below is the code for creating and running on a Virtual Judge, but before you
 * do so make sure
 * you have compiled your target program and got the inputs in a text file
 * generated by the maker.
 *
 * \code{.cpp}
 * #include <testcaser/integrator>
 *
 * using testcaser::integrator::VirtualJudge;
 *
 * int main() {
 *  const std::string root = "./testcaser/core/integrator/tests/";
 *  VirtualJudge()
 *    .set_binary(root + "program.out")
 *    .set_input_file(root + "input.txt")
 *    .set_output_file(root + "output2.txt")
 *    .set_time_limit(5)
 *    .set_memory_limit(1024*25)
 *    .execute()
 *    .print_result();
 *  return 0;
 * }
 * \endcode
 * Compile it and Run it. It will run the <b>`program.out`</b> with the input to
 * it from file <b>`input.txt`</b> and dumps the output of the program to a file
 * <b>output2.txt</b>. It also prints the following on the console
 *
 * \code
 * >>> Child Process created with pid 19398
 * >>> Setting the time constraint to 5 seconds
 * >>> Process will be killed if not returned before 5 second
 * >>> Executing ./testcaser/core/integrator/tests/program.out on child process.
 * >>> Completed the child process with exit code 0

 * ************** RESULTS ***************
 * Allocted Virtual Memory : 25600 KB (25 MB)
 * Physical Memory Used    : 3412 KB (3.33203 MB)
 * Virtual Memory Used     : 20364 KB (19.8867 MB)
 * Allocated Time          : 5 second(s)
 * Execution Time          : 0.112149 second(s)
 * Exit Code               : 0
 * Remark                  : Success. Ran under memory and time limit
 * ***************************************
 * \endcode
 * 
 * ---
 *
 * \section understanding_v_j Understanding Your Judge Program
 * 
 * <b>Line 1 </b> : Include the `testcaser/integrator` module to the program.
 * 
 * <b>Line 2 </b> : Brings VirtualJudge from the namespace.
 * 
 * <b>Line 3 </b> : Starts the main function
 * 
 * <b>Line 4 </b> : root is a parent path where out `program.out` and
 * `input.txt`
 * exist. To save writing the complete path, we put it into a variable.
 * 
 * <b>Line 5 </b> : Create the VirtualJudge Object. We will use the builder form
 * here.
 * 
 * <b>Line 6 </b> : Set the program to execute. It can be a binary or even a
 * python script path or any other executable. It is a required value.
 * 
 * <b>Line 7 </b> : Set the file from which to read the input to the program. It
 * is also a required.
 * 
 * <b>Line 8 </b> : Set a path where the outputs from the program will be
 * dumped. This is optional,
 * If you skip this. The outputs will be shown in the console (stdout).
 * 
 * <b>Line 9 </b> : Set the time limit to the program in Seconds. This is
 * optional and defaults to
 * 1 second if not specified by the programmer.
 * 
 * <b>Line 10 </b> : Set the memory limit to the program in Kilobytes. This is
 * optional and defaults
 * to 256 MB virtual memory if not specified by the programmer.
 * 
 * <b>Line 11 </b> : Execute starts the execution of the program specified as a
 * new process.
 * This call is blocking unless the program terminates. It returns a Result
 * object with result of execution.
 * 
 * <b>Line 12 </b> : Prints the result of the execution on the console.
 * 
 * <b>Line 13 </b> : Returns Zero and Completes the main.
 *
 * ---
 * 
 * \section more_example More Examples.
 * You can head over
 * <a
 * href="https://github.com/coder3101/testcaser/tree/master/examples"><b>here</b></a>
 * for
 * more examples of building the test case.
 *
 *
 */
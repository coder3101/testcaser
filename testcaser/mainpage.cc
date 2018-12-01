/**
 *
 *  \mainpage Getting started with TestCaser
 * \warning
 *  This is a preview version of testcaser.
 *  \tableofcontents
 *  \section sec_intro Introduction
 *
 *  TestCaser is a header-only light-weight test case maker library written in
 *  C++. It is easy, flexible and powerful library that can generate testcases,
 *  run your program on those test cases and compare two program's output for
the
 *  given test case files and lists down the input that causes a different
output to be produced.
 *  These features can come in handy when you are stuck on some corner cases for
a problem or
 *  when you want to check your program on valid random inputs.
 *  TestCaser has three submodules namely maker, integrator and comparator (only
maker is ready for use as of now).
 *  Maker module is used to generate test cases. Integrator integreates a
program to accept the test cases made by maker.
 *  Comparator compares two program's outputs for given inputs.
 *
 *  Enough Let's get you started with TestCaser.
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
 *  Running the above command will download the testcaser respository and switch
 * to that directory.
 *
 *  \subsection step2 Step 2
 *  There is no need to Compile the Source code. It is Header only hence you
only need to
 *  specify to the compiler the path of the testcaser. By default C++ compilers
look at `/usr/include`
 *  for includes in a program. So we need to move testcaser to that directory.
 *
 *  We provide two bash scripts along with the source code namely <a
href="https://github.com/coder3101/testcaser/blob/master/unix_install.sh"><b>unix_install.sh</b></a>
and <a
href="https://github.com/coder3101/testcaser/blob/master/unix_uninstall.sh"><b>unix_uninstall.sh</b></a>
 *  To install the testcaser on a linux machine <b>run the install script as a superuser</b>.
 *
 *  You are invited to check the scripts before you run them.
 *
 *  \code{.sh}
 *  sudo ./unix_install.sh
 *  \endcode
 *
 *  Type in your password and wait for the script to install the testcaser.
 *
 *  If you get any Error make sure that scripts are executable by running
 *  \code{.sh}
 *  sudo chmod +x unix_install.sh && sudo chmod +x unix_uninstall.sh
 *  \endcode
 *
 *  Now you can re-run the install script.
 *  If you are non-linux or you don't want to install testcaser. You can specify the location using `-I` flag of `g++`.
 *
 *  \section started Writing your first Test Case
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
 *  TestCaseBuilder builder("./test.txt");
 *  RandomUnsignedInteger<> a({1, 100000});
 *  RandomUnsignedInteger<> b({1, 100});
 *  RandomUnsignedInteger<> t({1, 10});
 *
 *  auto tt = builder.add_new(t, true, NEW_LINE);
 *
 *  for (int p = 0; p < T; p++) {
 *      builder.add_new(a, true, SPACE);
 *      builder.add_new(b, true, NEW_LINE);
 *  }
 *  builder.finalize();
 *  return 0;
 * }
 *  \endcode
 *
 * Compile  and Run it. You will have a <b>test.txt</b> test case file with the
 * test cases in the specifed
 * format. Rerun it to generate different valued test case file.
 *
 * \section under_standing Understanding Your first Program
 * <b>Line 1</b> : Includes the testcaser/maker module into your program
 *
 * <b>Line 2</b> : Brings in the TestCaseBuilder from its namespace to your
 * program. TestCaseBuilder is the object responsible for creating and writing
 * into
 * the file.
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
 * variable by calling `builder.add_new(...)` and it returns the value that was written
 * in the file.
 * In this case it will return a number in [0,10) denoting testcase of the
 * problem.
 *
 *
 * <b>Line 10-13 </b> : We now repeat for each testcase in a for loop.
 * Remember `tt` is the number of testcase written to file. For Each test
 * case we write 'a' and then put space and write 'b' then give a new line.
 * You can check from the problem statement it was the input format.
 *
 * <b>Line 14-16 </b> : Finally after we have written everything it is important
 * to finalize the builder by calling `builder.finalize()` and return from main.
 *
 * <BLOCKQUOTE>
 * <b>It is important to finalize the builder before the builder goes out of
 * scope. if you forget the file will not be written.
 * </b>
 * </BLOCKQUOTE>
 * <BLOCKQUOTE>
 * <b>builder.add_new() expects 3 arguments.</b> 
 * 
 * First a
 * RandomType(RandomIntegers or RandomAlphabets or others).
 * 
 * Second a boolean value where false means the next add_new() will write the
 * value just after the last one ends. 
 * 
 * Third the value to end the write with. Usually a macro or you can give your own character.
 * 
 * You should use `builder.add_new(.. ,false)` when generating random strings because that
 * requires concatenation of large non space separated characters.
 * If you pass true, you specify how to end this write. For the above example
 * `builder.add_new(t, true, NEW_LINE)` means that after writing t move to new
 * line.
 * </BLOCKQUOTE>
 *
 * \section more_example More Examples.
 * You can head over 
 * <a href="https://github.com/coder3101/testcaser/tree/master/examples"><b>here</b></a> for
 * more examples of building the test case.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
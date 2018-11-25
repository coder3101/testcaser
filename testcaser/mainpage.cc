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
 *  when want to check your program on random inputs but valid inputs.
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
 *  Run this command from your preferred directory (say downloads) in command
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
look at /usr/include
 *  for includes in a program. So we need to get testcaser to that directory.
 *
 *  We provide two bash scripts along with the source code namely <a
href="https://github.com/coder3101/testcaser/install.sh"><b>install.sh</b></a>
and <a
href="https://github.com/coder3101/testcaser/install.sh"><b>uninstall.sh</b></a>
 *  To install the testcaser <b>run the install script as a superuser</b>.
 *
 *  You are invited to check the scripts before you run them.
 *
 *  \code{.sh}
 *  sudo ./install.sh
 *  \endcode
 *
 *  Type in your password and wait for the script to install the testcaser.
 *
 *  If you get any Error make sure that scripts are executable by running
 *  \code{.sh}
 *  sudo chmod +x install.sh && sudo chmod +x uninstall.sh
 *  \endcode
 *
 *  Now you can re-run the install script.
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
 * The first line of each testcase contains T denoting the number of testcase
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
 *  auto T = builder.add_new(t, true, NEW_LINE);
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
 * Compile it and Execute it. You will have a <b>test.txt</b> file with the specifed
 * format as in the problem. Rerun it to generate different values.
 * 
 * \section under_standing Understanding Your first Program
 *
 *
 *
 *
 *
 *
 *
 *
 */
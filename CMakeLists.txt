cmake_minimum_required(VERSION 3.8)
project(Tests)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")
add_executable(vitualjudge testcaser/src/main.cc)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./make_output")

add_executable(first examples/simple-program.cc)
add_executable(second examples/maker_randomBinary.cc)
add_executable(third examples/integrator_virtual-judge.cc)

if(NOT DEFINED ENV{CI})
 include_directories(AFTER ./)    
endif()

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

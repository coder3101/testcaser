cmake_minimum_required(VERSION 3.8)
project(Tests)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")
add_executable(virtualjudge testcaser/src/main.cc)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./out")

add_executable(first examples/simple-program.cc)
add_executable(second examples/maker_randomBinary.cc)
add_executable(third examples/integrator_virtual-judge.cc)

if(NOT DEFINED ENV{TRAVIS})
 include_directories(AFTER ./)    
endif()

if(APPLE)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
    message("-- INFO : Skipping STATIC Executables for APPLE Platforms")
else()
# static building of OSX fails so skip it.
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -static")
    message("-- INFO : Building STATIC Builds")
endif()
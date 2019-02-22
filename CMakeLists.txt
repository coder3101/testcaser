cmake_minimum_required(VERSION 3.8)
project(Tests)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")

if (DEFINED ENV{ARM_CROSS_BUILD})
    message("Cross Compiling using default ARM toolchain")
    set(CMAKE_SYSTEM_NAME Linux)
    set(CMAKE_SYSTEM_PROCESSOR arm)
    set(CMAKE_C_COMPILER /usr/bin/arm-linux-gnueabi-gcc)
    set(CMAKE_CXX_COMPILER /usr/bin/arm-linux-gnueabi-g++)
    add_executable(virtualjudge-arm testcaser/src/main.cc)
else()
    if(NOT WIN32)
        set(CMAKE_C_COMPILER /usr/bin/cc)
        set(CMAKE_CXX_COMPILER /usr/bin/c++)
    endif()
    add_executable(virtualjudge testcaser/src/main.cc)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./out")

add_executable(first examples/simple-program.cc)
add_executable(second examples/maker_randomBinary.cc)
add_executable(third examples/integrator_virtual-judge.cc)

if(NOT DEFINED ENV{TRAVIS})
 include_directories(AFTER ./)    
endif()

if(APPLE)
    # Cannot build static binaries here on apple.
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -O3")
    message("-- INFO : Skipping STATIC Executables for APPLE Platforms")
else()
# static building is possible.
    if(NOT WIN32)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -static -O3")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -static -O3")
    endif()
    message("-- INFO : Building STATIC Builds")
endif()

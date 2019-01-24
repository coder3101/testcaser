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
    # Cannot build static binaries here on apple.
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -fsanitize=undefined")
    message("-- INFO : Skipping STATIC Executables for APPLE Platforms")
else()
# static building is possible.
    if(NOT WIN32)
        # If linux, we can either use GNU or CLANG.
        if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
            message("-- INFO : Not using sanitizer for GCC")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -static -Wextra")
        else()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -static -Wextra -fsanitize=undefined")
        endif()
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -static")
    endif()
    message("-- INFO : Building STATIC Builds")
endif()

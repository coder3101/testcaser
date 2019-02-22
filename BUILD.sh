#!/bin/bash 

cd build
export ARM_CROSS_BUILD=1
cmake ..
make
unset ARM_CROSS_BUILD
cmake .. 
make


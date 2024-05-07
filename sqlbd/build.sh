#!/bin/bash

mkdir -p build
cd build || return

if [[ ($@ == *'--test'*) ]]
then
    cmake -DCMAKE_BUILD_TYPE=Debug ..
    cmake --build . --target Tests -j 16
else
    cmake ..
    cmake --build . -j 16
fi

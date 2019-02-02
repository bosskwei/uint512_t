#! /bin/bash

cd build

if [[ $1 ]]; then
    rm -rf *
fi

cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j4

if [[ $? != 0 ]]; then
    exit $?
fi

./main

cd -
./script/test_1.py



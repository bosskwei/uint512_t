#! /bin/bash

cd build

if [[ $1 ]]; then
    rm -rf *
fi

cmake ..
make -j4

if [[ $? != 0 ]]; then
    exit $?
fi

./main

cd -
./script/test_1.py



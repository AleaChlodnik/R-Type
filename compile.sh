#!/usr/bin/env bash

cmake -B build

if [ $? -ne 0 ]; then
    echo "CMake failed"
    exit 1
fi

cmake --build build
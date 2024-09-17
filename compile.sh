#!/usr/bin/env bash

./install_sfml_X11.sh

cmake -B build

if [ $? -ne 0 ]; then
    echo "CMake failed"
    exit 1
fi

cmake --build build
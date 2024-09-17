#!/usr/bin/env bash

grep_str="^.*.[cpp|hpp]$"

all_file="$(find "${PWD}/src" -maxdepth 5 -type f -not -path '*/\.*' | grep "$grep_str")"
clang-format -i "$all_file"
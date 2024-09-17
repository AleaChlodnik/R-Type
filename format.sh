#!/usr/bin/env bash

grep_str="^.*.[c]$"

zappy_server="$(find "$(PWD)/Zappy_server" -maxdepth 5 -type f -not -path '*/\.*' | grep "$grep_str")"
clang-format -i $zappy_server
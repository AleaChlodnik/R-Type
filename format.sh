#!/usr/bin/env bash

grep_str="^.*.[cpp|hpp]$"

all_client_file="$(find "${PWD}/Client" -maxdepth 5 -type f -not -path '*/\.*' | grep "$grep_str")"
clang-format -i $all_client_file

all_ecs_file="$(find "${PWD}/ECS" -maxdepth 5 -type f -not -path '*/\.*' | grep "$grep_str")"
clang-format -i $all_ecs_file

all_interface_file="$(find "${PWD}/Interface" -maxdepth 2 -type f -not -path '*/\.*' | grep "$grep_str")"
clang-format -i $all_interface_file

all_server_file="$(find "${PWD}/Server" -maxdepth 5 -type f -not -path '*/\.*' | grep "$grep_str")"
clang-format -i $all_server_file
#!/bin/bash

# MAKE SURE SCRIPT ALWAYS RUNS IN cryptopals DIR
cd "$(dirname "$0")"

if [ "$#" -ne 1 ]; then
    echo "Illegal number of parameters - expected number of exercise to compile!"
    exit 1
fi

# AUTOMATICALLY SCAN util DIRECTORY FOR
# DEPENDENCIES AND ADD EXERCISE TO COMPILE
dependencies=($(find util -name '*.c' | sed 's/..$//'))
dependencies+=("exercises/exercise$1")

# COMPILE OBJECT FILES
for dependency in "${dependencies[@]}"
do
   gcc -Wall -c $dependency.c -o $dependency.o
done

function join { local IFS="$1"; shift; echo "$*"; }

# LINK
dependency_object_files=("${dependencies[@]/%/.o}")
joined_dependencies=$(join ' ' ${dependency_object_files[@]})
gcc $joined_dependencies -o exercise$1

# CLEAN UP OBJECT FILES
for dependency in "${dependencies[@]}"
do
   rm $dependency.o
done
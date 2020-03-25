#!/bin/bash


usage () {
cat <<EOF
Usage: $0 [<option> ...]

Configures the CMAKE build environment.

-h, --help              display this message and exit
--debug                 build debug with debug symbols (default: off)
EOF
  exit 0
}

die () {
    echo "*** $0: $*" 1>&2
    exit 1
}

build_type=Release

while [ $# -gt 0 ]
do
    case $1 in
        -h|--help) usage;;
        --debug)
            build_type=Debug;
            ;;
        *) die "unexpected argument: $1";;
    esac
    shift
done

cmake_opts="-DCMAKE_BUILD_TYPE=$build_type"

mkdir -p build
cd build || exit 1
cmake .. $cmake_opts 2>&1
cd ..

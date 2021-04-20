#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
DEPS=$DIR/../deps

usage () {
    cat <<EOF
Usage: $0 [<option> ...]

Sets up the smt-switch API for interfacing with SMT solvers through a C++ API.

-h, --help              display this message and exit
--debug                 build a debug version
--cvc4-home             use an already downloaded version of CVC4
EOF
    exit 0
}

die () {
    echo "*** $0: $*" 1>&2
    exit 1
}

cvc4_home=default

while [ $# -gt 0 ]
do
    case $1 in
        -h|--help) usage;;
        --debug)
            CONF_OPTS=--debug;;
        --cvc4-home) 
            echo "missing argument to $1 (see -h)" 
            exit 1;;
        --cvc4-home=*)
            cvc4_home=${1##*=}
            # Check if cvc4_home is an absolute path and if not, make it
            # absolute.
            case $cvc4_home in
                /*) ;;                            # absolute path
                *) cvc4_home=$(pwd)/$cvc4_home ;; # make absolute path
            esac
            CONF_OPTS="$CONF_OPTS --cvc4-home=$cvc4_home"
            ;;
        *) 
            echo "unexpected argument: $1"
            exit 1;;
    esac
    shift
done

mkdir -p $DEPS

if [ ! -d "$DEPS/smt-switch" ]; then
    cd $DEPS
    git clone https://github.com/makaimann/smt-switch
    cd smt-switch
    git checkout -f 970f5aaa9f262f30f26f85f2de9364be33483d7b
    [[ $cvc4_home == default ]] && echo "Downloading cvc4" && ./travis-scripts/download-cvc4.sh
    ./contrib/setup-flex.sh
    ./contrib/setup-bison.sh
    ./configure.sh --cvc4 --msat --msat-home=../mathsat --prefix=local --static --smtlib-reader $CONF_OPTS
    cd build
    make -j$(nproc)
    make test
    make install
    cd $DIR
else
    echo "$DEPS/smt-switch already exists. If you want to rebuild, please remove it manually."
fi

if [ -f $DEPS/smt-switch/local/lib/libsmt-switch.a ] && [ -f $DEPS/smt-switch/local/lib/libsmt-switch-msat.a ] && [ -f $DEPS/smt-switch/local/lib/libsmt-switch-cvc4.a ]; then \
    echo "It appears smt-switch with MathSAT and CVC4 was successfully installed to $DEPS/smt-switch/local."
else
    echo "Building smt-switch failed."
    echo "You might be missing some dependencies."
    echo "Please see the github page for installation instructions: https://github.com/makaimann/smt-switch"
    exit 1
fi

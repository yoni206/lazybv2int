#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
DEPS=$DIR/../deps

usage () {
    cat <<EOF
Usage: $0 [<option> ...]

Sets up ddsmt.

-h, --help              display this message and exit
EOF
    exit 0
}

while [ $# -gt 0 ]
do
    case $1 in
        -h|--help) usage;;
        --debug)
            CONF_OPTS=--debug;;
        *) die "unexpected argument: $1";;
    esac
    shift
done

mkdir -p $DEPS

if [ ! -d "$DEPS/ddsmt" ]; then
    cd $DEPS
    git clone https://github.com/aniemetz/ddSMT.git
    cd ddSMT
    cd $DIR
else
    echo "$DEPS/ddsmt already exists. If you want to rebuild, please remove it manually."
fi

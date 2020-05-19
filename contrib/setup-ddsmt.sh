#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
DEPS=$DIR/../deps
echo get ddSMT from https://github.com/aniemetz/ddSMT.git and clone it into `realpath $DEPS`/ddSMT

#!/bin/bash

# This script assumes ./deps/smt-switch already exists
# It then pulls the latest master and rebuilds
# Note: it does *not* update the underlying solvers

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
DEPS=$DIR/../deps

if [ ! -d "$DEPS/smt-switch" ]; then
    echo "Expecting $DEPS/smt-switch to already exist, but it does not"
    exit 0
fi

cd $DEPS/smt-switch
git checkout master
git fetch --all
git pull origin master
rm -rf build
./configure.sh --cvc4 --msat --prefix=local
cd build
make -j$(nproc)
make test
make install
cd $DIR
exit 0

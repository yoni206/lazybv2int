#!/bin/bash

mkdir -p build
cd build || exit 1
cmake ..
cd ..

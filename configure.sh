#!/bin/bash


usage () {
cat <<EOF
Usage: $0 [<option> ...]

Configures the CMAKE build environment.

-h, --help              display this message and exit
--debug                 build debug with debug symbols (default: off)
--static-lib            build a static library (default: off)
--static                build a static executable, automatically sets --static-lib also (default: off)
EOF
  exit 0
}

die () {
    echo "*** $0: $*" 1>&2
    exit 1
}

build_type=Release
lib_type=SHARED
static_opt=""
static_exec=NO

while [ $# -gt 0 ]
do
    case $1 in
        -h|--help) usage;;
        --debug)
            build_type=Debug;
            ;;
        --static-lib)
            lib_type=STATIC;
            ;;
        --static)
            static_exec=YES;
            lib_type=STATIC;
            ;;
        *) die "unexpected argument: $1";;
    esac
    shift
done

cmake_opts="-DCMAKE_BUILD_TYPE=$build_type"
cmake_opts="${cmake_opts} -DLBV2I_LIB_TYPE=${lib_type}"
cmake_opts="${cmake_opts} -DLBV2I_STATIC_EXEC=${static_exec}"

mkdir -p build
cd build || exit 1
echo "configuring with: ${cmake_opts}"
cmake .. $cmake_opts 2>&1
cd ..

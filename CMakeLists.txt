cmake_minimum_required(VERSION 3.1)

project(lazybv2int)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (WITH_MSAT)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DWITH_MSAT")
endif()

include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/src")

# TODO: Use find_package
# find package
#list(APPEND CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/smt-switch")

add_executable(lazybv2int
  "${PROJECT_SOURCE_DIR}/main.cpp"
  "${PROJECT_SOURCE_DIR}/src/lbv2isolver.cpp"
  "${PROJECT_SOURCE_DIR}/src/bv2int.cpp"
  "${PROJECT_SOURCE_DIR}/src/preprocessor.cpp"
  "${PROJECT_SOURCE_DIR}/src/smtlibsolver.cpp"
  )

if (APPLE)
  set(SHARED_LIBRARY_EXT dylib)
else()
  set(SHARED_LIBRARY_EXT so)
endif()

# Check that dependencies are there
if (NOT EXISTS "${PROJECT_SOURCE_DIR}/deps/smt-switch/local/include/smt-switch/smt.h")
  message(FATAL_ERROR "Missing smt-switch headers -- try running ./contrib/setup-smt-switch.sh")
endif()

if (NOT EXISTS "${PROJECT_SOURCE_DIR}/deps/smt-switch/local/lib/libsmt-switch.${SHARED_LIBRARY_EXT}")
  message(FATAL_ERROR "Missing smt-switch library -- try running ./contrib/setup-smt-switch.sh")
endif()

if (NOT EXISTS "${PROJECT_SOURCE_DIR}/deps/smt-switch/local/lib/libsmt-switch-btor.${SHARED_LIBRARY_EXT}")
  message(FATAL_ERROR "Missing smt-switch boolector library -- try running ./contrib/setup-smt-switch.sh")
endif()

if (WITH_MSAT)
  if (NOT EXISTS "${PROJECT_SOURCE_DIR}/deps/smt-switch/local/lib/libsmt-switch-msat.${SHARED_LIBRARY_EXT}")
    message(FATAL_ERROR "Missing smt-switch mathsat library -- try running ./contrib/setup-smt-switch.sh --with-msat")
  endif()
endif()

target_include_directories(lazybv2int PUBLIC "${PROJECT_SOURCE_DIR}/src")
target_include_directories(lazybv2int PUBLIC "${PROJECT_SOURCE_DIR}/contrib")
target_include_directories(lazybv2int PUBLIC "${PROJECT_SOURCE_DIR}/contrib/smtlib2parser-1.4")
#target_include_directories(lazybv2int PUBLIC "${PROJECT_SOURCE_DIR}/contrib/optionparser-1.7/src")
target_include_directories(lazybv2int PUBLIC "${PROJECT_SOURCE_DIR}/deps/smt-switch/local/include")

target_link_libraries(lazybv2int PUBLIC "${PROJECT_SOURCE_DIR}/deps/smt-switch/local/lib/libsmt-switch.${SHARED_LIBRARY_EXT}")
target_link_libraries(lazybv2int PUBLIC "${PROJECT_SOURCE_DIR}/deps/smt-switch/local/lib/libsmt-switch-btor.${SHARED_LIBRARY_EXT}")
if (WITH_MSAT)
  target_link_libraries(lazybv2int PUBLIC "${PROJECT_SOURCE_DIR}/deps/smt-switch/local/lib/libsmt-switch-msat.${SHARED_LIBRARY_EXT}")
endif()
target_link_libraries(lazybv2int PUBLIC gmp)

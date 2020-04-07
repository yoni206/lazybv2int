cmake_minimum_required(VERSION 3.1)

project(lazybv2int)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/src")

message("-- CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}")

add_library(lazybv2int "${LBV2I_LIB_TYPE}"
  "${PROJECT_SOURCE_DIR}/src/utils.cpp"
  "${PROJECT_SOURCE_DIR}/src/lbv2isolver.cpp"
  "${PROJECT_SOURCE_DIR}/src/bv2int.cpp"
  "${PROJECT_SOURCE_DIR}/src/preprocessor.cpp"
  "${PROJECT_SOURCE_DIR}/src/postprocessor.cpp"
  "${PROJECT_SOURCE_DIR}/src/axioms.cpp"
  "${PROJECT_SOURCE_DIR}/src/smtlibsolver.cpp"
  "${PROJECT_SOURCE_DIR}/src/bw_functions.cpp"
  "${PROJECT_SOURCE_DIR}/src/smtlibmsatparser.cpp"
  "${PROJECT_SOURCE_DIR}/src/opts.cpp"
  "${PROJECT_SOURCE_DIR}/src/main.cpp"
  )

# Check that dependencies are there
if (NOT EXISTS "${PROJECT_SOURCE_DIR}/deps/smt-switch/local/include/smt-switch/smt.h")
  message(FATAL_ERROR "Missing smt-switch headers -- try running ./contrib/setup-smt-switch.sh")
endif()

if (NOT EXISTS "${PROJECT_SOURCE_DIR}/deps/smt-switch/local/lib/libsmt-switch.a")
  message(FATAL_ERROR "Missing smt-switch library -- try running ./contrib/setup-smt-switch.sh")
endif()

if (NOT EXISTS "${PROJECT_SOURCE_DIR}/deps/smt-switch/local/lib/libsmt-switch-msat.a")
  message(FATAL_ERROR "Missing smt-switch mathsat library -- try running ./contrib/setup-smt-switch.sh --with-msat")
endif()

if (NOT EXISTS "${PROJECT_SOURCE_DIR}/deps/smt-switch/local/lib/libsmt-switch-cvc4.a")
  message(FATAL_ERROR "Missing smt-switch cvc4 library -- try running ./contrib/setup-smt-switch.sh")
endif()

# Tests are with MathSAT only for now
enable_testing()
add_subdirectory(test)

target_include_directories(lazybv2int PUBLIC "${PROJECT_SOURCE_DIR}/src")
target_include_directories(lazybv2int PUBLIC "${PROJECT_SOURCE_DIR}/contrib")
target_include_directories(lazybv2int PUBLIC "${PROJECT_SOURCE_DIR}/contrib/smtlib2parser-1.4")
#target_include_directories(lazybv2int PUBLIC "${PROJECT_SOURCE_DIR}/contrib/optionparser-1.7/src")
target_include_directories(lazybv2int PUBLIC "${PROJECT_SOURCE_DIR}/deps/smt-switch/local/include")

# HACK: Using MathSAT parser (need to expose some of smt-switch internals)
target_include_directories(lazybv2int PUBLIC
  "${PROJECT_SOURCE_DIR}/smt-switch/local/include"
  "${PROJECT_SOURCE_DIR}/deps/smt-switch"
  "${PROJECT_SOURCE_DIR}/deps/smt-switch/include"
  "${PROJECT_SOURCE_DIR}/deps/smt-switch/deps/mathsat/include")


target_link_libraries(lazybv2int PUBLIC "${PROJECT_SOURCE_DIR}/deps/smt-switch/local/lib/libsmt-switch-msat.a")
target_link_libraries(lazybv2int PUBLIC "${PROJECT_SOURCE_DIR}/deps/smt-switch/local/lib/libsmt-switch-cvc4.a")
target_link_libraries(lazybv2int PUBLIC "${PROJECT_SOURCE_DIR}/deps/smt-switch/local/lib/libsmt-switch.a")
target_link_libraries(lazybv2int PUBLIC gmp)

add_executable(lazybv2int-bin
  "${PROJECT_SOURCE_DIR}/src/main.cpp"
)
set_target_properties(lazybv2int-bin PROPERTIES OUTPUT_NAME lazybv2int)
target_link_libraries(lazybv2int-bin lazybv2int)

if("${LBV2I_STATIC_EXEC}" STREQUAL "YES")
  target_link_libraries(lazybv2int-bin -static)
endif()

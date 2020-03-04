cmake_minimum_required(VERSION 3.1)

project(lazybv2int)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/src")

add_library(lazybv2int SHARED
  "${PROJECT_SOURCE_DIR}/src/lbv2isolver.cpp"
  "${PROJECT_SOURCE_DIR}/src/bv2int.cpp"
  "${PROJECT_SOURCE_DIR}/src/preprocessor.cpp"
  "${PROJECT_SOURCE_DIR}/src/axioms.cpp"
  "${PROJECT_SOURCE_DIR}/src/smtlibsolver.cpp"
  "${PROJECT_SOURCE_DIR}/src/bw_functions.cpp"
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

if (NOT EXISTS "${PROJECT_SOURCE_DIR}/deps/smt-switch/local/lib/libsmt-switch-msat.${SHARED_LIBRARY_EXT}")
  message(FATAL_ERROR "Missing smt-switch mathsat library -- try running ./contrib/setup-smt-switch.sh --with-msat")
endif()

# Tests are with MathSAT only for now
enable_testing()
add_subdirectory(test)

target_include_directories(lazybv2int PUBLIC "${PROJECT_SOURCE_DIR}/src")
target_include_directories(lazybv2int PUBLIC "${PROJECT_SOURCE_DIR}/contrib")
target_include_directories(lazybv2int PUBLIC "${PROJECT_SOURCE_DIR}/contrib/smtlib2parser-1.4")
#target_include_directories(lazybv2int PUBLIC "${PROJECT_SOURCE_DIR}/contrib/optionparser-1.7/src")
target_include_directories(lazybv2int PUBLIC "${PROJECT_SOURCE_DIR}/deps/smt-switch/local/include")

target_link_libraries(lazybv2int PUBLIC "${PROJECT_SOURCE_DIR}/deps/smt-switch/local/lib/libsmt-switch.${SHARED_LIBRARY_EXT}")
target_link_libraries(lazybv2int PUBLIC "${PROJECT_SOURCE_DIR}/deps/smt-switch/local/lib/libsmt-switch-msat.${SHARED_LIBRARY_EXT}")
target_link_libraries(lazybv2int PUBLIC gmp)

add_executable(lazybv2int-bin
  "${PROJECT_SOURCE_DIR}/main.cpp"
)
set_target_properties(lazybv2int-bin PROPERTIES OUTPUT_NAME lazybv2int)
target_link_libraries(lazybv2int-bin lazybv2int)

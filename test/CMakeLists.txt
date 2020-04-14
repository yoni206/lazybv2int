set(TESTS
  test1
  test2
  test3
  test4
  # Add more tests here
  )

foreach(test ${TESTS})
  add_executable(${test}.out ${test}.cpp)
  target_include_directories(${test}.out PUBLIC "${PROJECT_SOURCE_DIR}/deps/smt-switch/local/include")
  target_link_libraries(${test}.out lazybv2int)
  target_link_libraries(${test}.out "${PROJECT_SOURCE_DIR}/deps/smt-switch/local/lib/libsmt-switch.a")
  target_link_libraries(${test}.out "${PROJECT_SOURCE_DIR}/deps/smt-switch/local/lib/libsmt-switch-msat.a")
  add_test(${test} ${test}.out)
endforeach()

set(TESTS
  test1
  # Add more tests here
  )

foreach(test ${TESTS})
  add_executable(${test}.out ${test}.cpp)
  target_include_directories(${test}.out PUBLIC "${PROJECT_SOURCE_DIR}/deps/smt-switch/local/include")
  target_link_directories(${test}.out PUBLIC "${PROJECT_SOURCE_DIR}/deps/smt-switch/local/lib")
  target_link_libraries(${test}.out lazybv2int)
  target_link_libraries(${test}.out smt-switch)
  target_link_libraries(${test}.out smt-switch-msat)
  add_test(${test} ${test}.out)
endforeach()

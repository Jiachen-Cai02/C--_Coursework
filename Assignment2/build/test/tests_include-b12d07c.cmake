if(EXISTS "/workspaces/PHAS0100Assignment2/build/test/tests_tests-b12d07c.cmake")
  include("/workspaces/PHAS0100Assignment2/build/test/tests_tests-b12d07c.cmake")
else()
  add_test(tests_NOT_BUILT-b12d07c tests_NOT_BUILT-b12d07c)
endif()

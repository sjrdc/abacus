
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
  )

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(test_abacus test_store.cpp test_abacus.cpp test_parse.cpp main.cpp test_store.cpp)
target_include_directories(test_abacus 
  PRIVATE ${ABACUS_INCLUDE_DIR}
  PRIVATE ${CMAKE_SOURCE_DIR}/src
  )
target_link_libraries(test_abacus abacus gtest_main)

include(GoogleTest)
gtest_discover_tests(test_abacus
  PROPERTIES
  DISCOVERY_TIMEOUT  # how long to wait (in seconds) before crashing
  10
  )

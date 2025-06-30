
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
  )

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(test_abacus main.cpp test_store.cpp test_abacus.cpp test_parse.cpp test_parser.cpp test_printer.cpp)
target_include_directories(test_abacus 
  PRIVATE ${CMAKE_SOURCE_DIR}/src
  PRIVATE ${Boost_INCLUDE_DIRS}
  )
target_link_libraries(test_abacus abacus gtest_main)

include(GoogleTest)
gtest_discover_tests(test_abacus
  PROPERTIES
  DISCOVERY_TIMEOUT  # how long to wait (in seconds) before crashing
  10
  )


include_directories(${CMAKE_SOURCE_DIR}/src)
add_executable(abacuscli main.cpp)
target_link_libraries(abacuscli abacus::abacus)

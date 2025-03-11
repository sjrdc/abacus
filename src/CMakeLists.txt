include_directories(${Boost_include_dirs})
add_library(abacus abacus.cpp abacus.h calculator.h calculator.cpp "ast_adapted.h" "store.h" "store.cpp")

add_executable(abacuscli main.cpp)
target_link_libraries(abacuscli abacus)

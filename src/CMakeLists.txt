include_directories(${Boost_include_dirs})
add_library(abacus parse.cpp abacus.h calculator.h calculator.cpp ast_adapted.h store.h store.cpp)

add_library(abacus parse.cpp calculator.h calculator.cpp ast_adapted.h store.h store.cpp)
target_include_directories(abacus PRIVATE ${Boost_INCLUDE_DIRS})
target_include_directories(abacus PUBLIC  
    $<BUILD_INTERFACE:${ABACUS_INCLUDE_DIR}>  
    $<INSTALL_INTERFACE:include>  # <prefix>/include
)
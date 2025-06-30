add_library(abacus parse.cpp visitors/calculator.h visitors/calculator.cpp 
    evaluate.cpp visitors/is_evaluatable.cpp visitors/is_evaluatable.h operand.cpp parser.cpp 
    ast_adapted.h visitors/printer.h visitors/printer.cpp store.h store.cpp)
target_include_directories(abacus PRIVATE ${Boost_INCLUDE_DIRS})
target_include_directories(abacus PUBLIC  
    $<BUILD_INTERFACE:${ABACUS_INCLUDE_DIR}>  
    $<INSTALL_INTERFACE:include>  # <prefix>/include
)

cmake_minimum_required(VERSION 3.8...3.30)

project(abacus LANGUAGES CXX VERSION 0.0.1)

if(NOT DEFINED CMAKE_CXX_STANDARD OR CMAKE_CXX_STANDARD STREQUAL "98")
    set(CMAKE_CXX_STANDARD 23)
endif()

set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/WX)
else()
    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        set(CLANG_USED TRUE)
    endif()
    option(CLANG_USE_LIBCPP "Use libc++ for clang compilation" ${CLANG_USED})
    if(APPLE OR CLANG_USE_LIBCPP)
        message(STATUS "Use libc++")
        add_compile_options(-stdlib=libc++)
        # TODO: use add_link_options(-stdlib=libc++ -lc++abi") bud this needs cmake 3.13! CK
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")
    endif()

endif()

find_package(Boost REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()
add_subdirectory(src)

add_library(abacus::abacus ALIAS abacus)
target_include_directories(abacus INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

option(ABACUS_INSTALL "Generate the install target" ${ABACUS_MASTER_PROJECT})
if(ABACUS_INSTALL)
    include(GNUInstallDirs)
    include(CMakePackageConfigHelpers)

    install(TARGETS abacus EXPORT ${PROJECT_NAME}Targets)
    install(DIRECTORY include/ABACUS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

    set(configFile ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/cmake/Config.cmake)
    set(versionFile ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake)
    set(configInstallDestination ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

    configure_package_config_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in
        ${configFile}
        INSTALL_DESTINATION ${configInstallDestination}
    )
    if(${CMAKE_VERSION} VERSION_GREATER 3.13)
        write_basic_package_version_file("${versionFile}" COMPATIBILITY SameMajorVersion ARCH_INDEPENDENT)
    else()
        write_basic_package_version_file("${versionFile}" COMPATIBILITY SameMajorVersion)
    endif()
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.pc.in
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc
        @ONLY
    )

    install(FILES ${configFile} ${versionFile} DESTINATION ${configInstallDestination})
    install(
        EXPORT ${PROJECT_NAME}Targets
        NAMESPACE "ABACUS::"
        DESTINATION ${configInstallDestination}
    )
    install(
        FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig
    )
endif()

option(BUILD_ABACUS_TESTS "Build tests" ON)
if(BUILD_ABACUS_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

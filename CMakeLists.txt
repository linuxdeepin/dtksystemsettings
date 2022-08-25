# SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
#
# SPDX-License-Identifier: LGPL-3.0-or-later

cmake_minimum_required(VERSION 3.13)

# If do't define version number, specify the version number
if (NOT DEFINED VERSION)
    set(VERSION "1.0.0")
endif()

project(dtkdemo
    LANGUAGES CXX
    HOMEPAGE_URL https://github.com/Groveer/dtk
    DESCRIPTION "dtk library template"
    VERSION ${VERSION})

# specify install dir
include(GNUInstallDirs)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall -Wextra")
set(CMAKE_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS} "-Wl,--as-needed")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Install settings
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX /usr)
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1 -g -fsanitize=address -fno-omit-frame-pointer")
    set(BUILD_TESTING ON)
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast")
endif ()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core DBus)
find_package(Doxygen)
# find_package(PkgConfig REQUIRED)
# pkg_search_module(XCB REQUIRED xcb)

set (BUILD_DOCS ON)

if (BUILD_DOCS AND DOXYGEN_FOUND)
    set (QCH_INSTALL_DESTINATION ${CMAKE_INSTALL_PREFIX}/share/dtk/doc CACHE STRING "QCH install location")
    set (DOXYGEN_GENERATE_HTML "YES" CACHE STRING "Doxygen HTML output")
    set (DOXYGEN_GENERATE_XML "NO" CACHE STRING "Doxygen XML output")
    set (DOXYGEN_GENERATE_QHP "YES" CACHE STRING "Doxygen QHP output")
    set (DOXYGEN_FILE_PATTERNS *.cpp *.h *.md *.zh_CN.dox CACHE STRING "Doxygen File Patterns")
    set (DOXYGEN_PROJECT_NUMBER ${CMAKE_PROJECT_VERSION} CACHE STRING "") # Should be the same as this project is using.
    set (DOXYGEN_EXTRACT_STATIC YES)
    set (DOXYGEN_OUTPUT_LANGUAGE "Chinese")
    set (DOXYGEN_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/docs/)
    set (DOXYGEN_QHG_LOCATION "qhelpgenerator")
    set (DOXYGEN_QHP_NAMESPACE "org.deepin.dde.${CMAKE_PROJECT_NAME}")
    set (DOXYGEN_QCH_FILE "${CMAKE_PROJECT_NAME}.qch")
    set (DOXYGEN_QHP_VIRTUAL_FOLDER ${CMAKE_PROJECT_NAME})
    set (DOXYGEN_HTML_EXTRA_STYLESHEET "" CACHE STRING "Doxygen custom stylesheet for HTML output")
    set (DOXYGEN_TAGFILES "qtcore.tags=qthelp://doc.qt.io/qt-5/" CACHE STRING "Doxygen tag files")
    set (DOXYGEN_MACRO_EXPANSION "YES")
    set (DOXYGEN_EXPAND_ONLY_PREDEF "YES")
    set (DOXYGEN_PREDEFINED
        "\"DDEMO_BEGIN_NAMESPACE=namespace Dtk { namespace Demo {\""
        "\"DDEMO_END_NAMESPACE=}}\""
        "\"DDEMO_USE_NAMESPACE=using namespace Dtk::Demo;\""
    )

    doxygen_add_docs (doxygen
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/docs
        ALL
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generate documentation via Doxygen"
    )

    install (FILES ${CMAKE_CURRENT_BINARY_DIR}/docs/html/${CMAKE_PROJECT_NAME}.qch DESTINATION ${QCH_INSTALL_DESTINATION})
endif ()

file(GLOB_RECURSE INCLUDE_FILES "include/*.h")
file(GLOB_RECURSE SRCS
    "src/*.h"
    "src/*.cpp"
)

set(BIN_NAME dtkdemo)

# for pc file config
set(PC_LIBS_PRIVATE Qt${QT_VERSION_MAJOR}Core)
set(PC_REQ_PRIVATE)
set(PC_REQ_PUBLIC)

# config template file
configure_file(misc/${BIN_NAME}.pc.in ${BIN_NAME}.pc @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${BIN_NAME}.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
configure_file(misc/${BIN_NAME}Config.cmake.in ${BIN_NAME}Config.cmake @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${BIN_NAME}Config.cmake DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${BIN_NAME})

add_library(${BIN_NAME} SHARED
    ${INCLUDE_FILES}
    ${SRCS})

set_target_properties(${BIN_NAME} PROPERTIES
    VERSION ${CMAKE_PROJECT_VERSION}
    SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR})

target_compile_definitions(${BIN_NAME} PRIVATE VERSION="${CMAKE_PROJECT_VERSION}")

set(BIN_INCLUDE_DIRS
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::DBus
)

set(BIN_LIBRARIES
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::DBus
)

target_include_directories(${BIN_NAME} PUBLIC
    ${BIN_INCLUDE_DIRS}
)

target_link_libraries(${BIN_NAME} PRIVATE
    ${BIN_LIBRARIES}
)

install(FILES ${INCLUDE_FILES} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${BIN_NAME})
install(TARGETS ${BIN_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})

# test
if (BUILD_TESTING)
    enable_testing()
    find_package(Qt5 REQUIRED COMPONENTS Test)
    file(GLOB_RECURSE TEST_FILES "tests/*.cpp")
    include(./tests/dbus/fakeInterface.cmake)

    add_executable(ut-${BIN_NAME}
        ${INCLUDE_FILES}
        ${SRCS}
        ${TEST_FILES}
        ${DFAKE_INTERFACE_DBUS_XML})

    if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        target_compile_options(ut-${BIN_NAME} PRIVATE -fprofile-instr-generate -ftest-coverage)
    endif()
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(ut-${BIN_NAME} PRIVATE -fprofile-arcs -ftest-coverage)
    endif()

    target_include_directories(ut-${BIN_NAME} PUBLIC
        ${BIN_INCLUDE_DIRS}
    )

    target_link_libraries(ut-${BIN_NAME} PRIVATE
        ${BIN_LIBRARIES}
#        Qt5::Test     # QTest functions
        -lpthread
        -lgcov
        -lgtest
    )

    add_test(NAME ut-${BIN_NAME} COMMAND ut-${BIN_NAME})
endif ()

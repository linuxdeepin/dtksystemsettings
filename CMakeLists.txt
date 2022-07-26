# SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
#
# SPDX-License-Identifier: LGPL-3.0-only

cmake_minimum_required(VERSION 3.13)

# If do't define version number, specify the version number
if (NOT DEFINED VERSION)
    set(VERSION "1.0.0")
endif()

project(dframework
    LANGUAGES CXX
    HOMEPAGE_URL https://github.com/Groveer/dframework
    DESCRIPTION "dframework library"
    VERSION ${VERSION})

include(GNUInstallDirs)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall -Wextra")
set(CMAKE_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS} "-Wl,--as-needed")

# Install settings
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX /usr)
endif ()

if (NOT (${CMAKE_BUILD_TYPE} MATCHES "Debug"))
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast")
endif ()

find_package(PkgConfig REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Core)
#pkg_search_module(XCB REQUIRED xcb)

file(GLOB_RECURSE INCLUDE_FILES "include/*.h")
file(GLOB_RECURSE SRCS
    "src/*.h"
    "src/*.cpp"
)

set(BIN_NAME dframework)

set(PC_LIBS_PRIVATE Qt5Core)
set(PC_REQ_PRIVATE)
set(PC_REQ_PUBLIC)

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

target_include_directories(${BIN_NAME} PUBLIC
    Qt5::Core
)

target_link_libraries(${BIN_NAME} PRIVATE
    Qt5::Core
)

install(FILES ${INCLUDE_FILES} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${BIN_NAME})
install(TARGETS ${BIN_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})

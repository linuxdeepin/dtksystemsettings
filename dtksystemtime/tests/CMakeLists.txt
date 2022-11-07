# SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
#
# SPDX-License-Identifier: LGPL-3.0-or-later

set(BIN_NAME ut-${BIN_NAME})

find_package(GTest REQUIRED)
file(GLOB_RECURSE INCLUDE_FILES "../include/*.h")
file(GLOB_RECURSE SRCS
    "../src/*.h"
    "../src/*.cpp"
)
file(GLOB_RECURSE TEST_FILES "./*.h" "./*.cpp")

include_directories(
    "../include"
    "../src/dbus"
    ${DtkCore_INCLUDE_DIRS}
)

add_definitions(-DUSE_FAKE_INTERFACE)

add_executable(${BIN_NAME}
    ${INCLUDE_FILES}
    ${SRCS}
    ${TEST_FILES}
)

target_link_libraries(${BIN_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::DBus
    ${DtkCore_LIBRARIES}
    pthread
    gcov
    gtest
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${BIN_NAME} PRIVATE -fprofile-instr-generate -ftest-coverage)
endif()
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${BIN_NAME} PRIVATE -fprofile-arcs -ftest-coverage)
endif()
target_compile_options(${BIN_NAME} PRIVATE -fno-access-control)

enable_testing()
add_test(NAME ${BIN_NAME} COMMAND ${BIN_NAME})

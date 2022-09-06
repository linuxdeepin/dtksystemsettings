# SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
#
# SPDX-License-Identifier: LGPL-3.0-or-later

set(BIN_NAME ut-dtkdemo)

add_definitions(-DUSE_MOCK_INTERFACE)

include(./dbus/fakeInterface.cmake)

file(GLOB_RECURSE INCLUDE_FILES "../include/*.h")
file(GLOB_RECURSE SRCS
    "../src/*.h"
    "../src/*.cpp"
)
file(GLOB_RECURSE TEST_FILES "./*.cpp")

include_directories(
    "../include"
    "../src/dbus"
)

add_executable(${BIN_NAME}
    ${INCLUDE_FILES}
    ${SRCS}
    ${TEST_FILES}
    ${DFAKE_INTERFACE_DBUS_XML}
)

target_include_directories(${BIN_NAME} PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::DBus
)

target_link_libraries(${BIN_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::DBus
    -lpthread
    -lgcov
    -lgtest
    -ldl            # dlsym
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${BIN_NAME} PRIVATE -fprofile-instr-generate -ftest-coverage)
endif()
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${BIN_NAME} PRIVATE -fprofile-arcs -ftest-coverage)
endif()

enable_testing()
add_test(NAME ${BIN_NAME} COMMAND ${BIN_NAME})

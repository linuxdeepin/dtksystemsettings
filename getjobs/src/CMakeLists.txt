# SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
#
# SPDX-License-Identifier: LGPL-3.0-or-later

file(GLOB_RECURSE INCLUDE_FILES "../include/*.h")
file(GLOB_RECURSE SRCS
    "./*.h"
    "./*.cpp"
)

if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "x86_64")
    set(GLIBPREFIX "x86_64")
elseif(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "aarch64")
    set(GLIBPREFIX "aarch64")
elseif(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "mips64")
    set(GLIBPREFIX "mips64el")
    set(GLIBSUFFIX "abi64")
elseif(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "sw_64")
    set(GLIBPREFIX "sw_64")
elseif(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "loongarch64")
    set(GLIBPREFIX "loongarch64")
else()
    set(GLIBPREFIX "i386")
endif()
include_directories(../include /usr/include/${GLIBPREFIX}-linux-gnu/qt5/QtCore /usr/include/${GLIBPREFIX}-linux-gnu/qt5)

add_library(${BIN_NAME} STATIC
    ${INCLUDE_FILES}
    ${SRCS}
)

set_target_properties(${BIN_NAME} PROPERTIES
    VERSION ${CMAKE_PROJECT_VERSION}
    SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR})

target_compile_definitions(${BIN_NAME} PRIVATE VERSION="${CMAKE_PROJECT_VERSION}")

install(FILES ${INCLUDE_FILES} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${BIN_NAME})
install(TARGETS ${BIN_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})

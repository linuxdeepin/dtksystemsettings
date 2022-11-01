# SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
#
# SPDX-License-Identifier: LGPL-3.0-or-later

file(GLOB_RECURSE INCLUDE_FILES "../include/*.h")
set(BIN_NAME getjobstest)
#set(LIB_NAME ${BIN_NAME})
add_executable(${BIN_NAME}
    ${INCLUDE_FILES}
    main.cpp
)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)


include_directories(../include)

target_include_directories(${BIN_NAME} PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
)

target_link_libraries(${BIN_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    /usr/lib/x86_64-linux-gnu/libcups.so
    /usr/lib/libgetjobs.a
)

# SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
#
# SPDX-License-Identifier: LGPL-3.0-or-later

file(GLOB_RECURSE INCLUDE_FILES "../include/*.h")
include_directories(../include)

set(BIN1 dkbbacklightdemo)
add_executable(
    ${BIN1}
    dkbbacklightdemo.cpp
)
target_link_libraries(
    ${BIN1} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::DBus
    dtkpower
)


set(BIN2 dpowerdevicedemo)
add_executable(
    ${BIN2}
    dpowerdevicedemo.cpp
)
target_link_libraries(
    ${BIN2} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::DBus
    dtkpower
)


set(BIN3 dpowersettingsdemo)
add_executable(
    ${BIN3}
    dpowersettingsdemo.cpp
)
target_link_libraries(
    ${BIN3} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::DBus
    dtkpower
)
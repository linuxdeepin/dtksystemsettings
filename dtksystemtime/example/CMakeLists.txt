# SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
#
# SPDX-License-Identifier: LGPL-3.0-or-later

file(GLOB_RECURSE INCLUDE_FILES "../include/*.h")
include_directories(../include)

set(BIN1 dsystemtimedemo)
add_executable(
    ${BIN1}
    dsystemtimedemo.cpp
)
target_link_libraries(
    ${BIN1} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::DBus
    dtksystemtime
)



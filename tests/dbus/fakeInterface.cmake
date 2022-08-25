# SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
#
# SPDX-License-Identifier: LGPL-3.0-or-later

find_package(Qt5DBus REQUIRED)
set(CMAKE_AUTOMOC ON)
add_definitions(-DUSE_FAKE_INTERFACE)

set(FAKE_SERVICE "com.deepin.dtk.fakeInterface")
set(FAKE_PATH "/com/deepin/dtk/fakeInterface")
set(FAKE_INTERFACE "com.deepin.dtk.fakeInterface")

# 由于包含自定义类型 'a(uo)'，xml 文件需要自行编辑一下 生成 adaptor。
qt5_add_dbus_adaptor(DFAKE_INTERFACE_DBUS_XML ${CMAKE_CURRENT_LIST_DIR}/${FAKE_SERVICE}.xml
    dfakeinterface.h DFakeInterface
    dfakeinterface_adaptor DFakeInterfaceAdaptor)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/dbus
    ${CMAKE_CURRENT_LIST_DIR})

add_definitions(-DFAKE_SERVICE="${FAKE_SERVICE}")
add_definitions(-DFAKE_PATH="${FAKE_PATH}")
add_definitions(-DFAKE_INTERFACE="${FAKE_INTERFACE}")


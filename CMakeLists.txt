# SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
#
# SPDX-License-Identifier: LGPL-3.0-or-later

cmake_minimum_required(VERSION 3.13)

# If do't define version number, specify the version number
set(VERSION "1.0.0" CACHE STRING "define project version")

project(dtksystemsettings
    LANGUAGES CXX
    HOMEPAGE_URL https://github.com/linuxdeepin/dtksystemsettings
    DESCRIPTION "dtk library for systemsettings."
    VERSION ${VERSION}
)

add_subdirectory(dtklogin)
add_subdirectory(dtkpower)
add_subdirectory(dtkaccounts)
add_subdirectory(dtksystemtime)
add_subdirectory(dtkrfmanager)
add_subdirectory(dtknotifications)

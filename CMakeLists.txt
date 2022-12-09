# SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
#
# SPDX-License-Identifier: LGPL-3.0-or-later

cmake_minimum_required(VERSION 3.13)

# If do't define version number, specify the version number
set(VERSION "1.0.0" CACHE STRING "define project version")

project(DtkSystemSettings
    LANGUAGES CXX
    HOMEPAGE_URL https://github.com/linuxdeepin/dtksystemsettings
    DESCRIPTION "dtk library for systemsettings."
    VERSION ${VERSION}
)

set(LIB_NAME dtksystemsettings)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH}) # Set module path for include() command search

include(DtkUtils) # Include cmake/DtkUtils.cmake
include(GNUInstallDirs) # Specify install dir
include(CMakePackageConfigHelpers)
include(CMakePrintHelpers)

set_install_dir(INCLUDE include/dtk1/DSystemSettings)
set(MKSPECS_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/qt5/mkspecs/modules" CACHE STRING "Install directory for qt pri files")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall -Wextra")
set(CMAKE_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS} "-Wl,--as-needed")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(ConfigPackageLocation ${CMAKE_INSTALL_LIBDIR}/cmake/DtkSystemSettings)

# Install settings
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX /usr)
endif ()

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose Debug or Release" FORCE)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(BUILD_TESTING ON)
    set(BUILD_EXAMPLES ON)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
endif ()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core DBus)
find_package(Dtk REQUIRED COMPONENTS Core)

file(GLOB_RECURSE LIB_PUBLIC_HEADERS "${PROJECT_SOURCE_DIR}/include/*") # Get all headers which will be exported

add_subdirectory(src)

set(BUILD_DOCS ON CACHE BOOL "Generate doxygen-based documentation")
find_package(Doxygen)
if (BUILD_DOCS AND DOXYGEN_FOUND)
    add_subdirectory(docs)
endif()

# example
if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# test
if (BUILD_TESTING)
    add_subdirectory(tests)
endif()

target_link_directories(${LIB_NAME} INTERFACE
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_LIBDIR}>
)

write_basic_package_version_file(
    DtkSystemSettingsConfigVersion.cmake
    VERSION ${VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(misc/DtkSystemSettingsConfig.cmake.in
    DtkSystemSettingsConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/DtkSystemSettings
    PATH_VARS CMAKE_INSTALL_INCLUDEDIR CMAKE_INSTALL_LIBDIR
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/DtkSystemSettingsConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/DtkSystemSettingsConfigVersion.cmake DESTINATION ${ConfigPackageLocation})

set(PC_REQUIRES "Qt${QT_VERSION_MAJOR}Core Qt${QT_VERSION_MAJOR}DBus dtkcore")
configure_file(misc/dtksystemsettings.pc.in dtksystemsettings.pc @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/dtksystemsettings.pc DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig")

set(DTK_MODULE ${LIB_NAME})
set(DTK_DEPS "core dbus dtkcore")
set(DTK_CFG "v2 ltcg")
configure_file(misc/qt_lib_dtksystemsettings.pri.in qt_lib_dtksystemsettings.pri @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/qt_lib_dtksystemsettings.pri DESTINATION "${MKSPECS_INSTALL_DIR}")

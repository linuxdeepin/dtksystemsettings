cmake_minimum_required(VERSION 3.19)
project(dframework
    LANGUAGES CXX
    HOMEPAGE_URL https://test.com
    DESCRIPTION "Test library"
    VERSION 1.0.0)

include(GNUInstallDirs)
set(CMAKE_CXX_STANDARD_REQUIRED 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall -Wextra")

message(CMAKE_PROJECT_VERSION = ${CMAKE_PROJECT_VERSION})

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

set(PC_LIBS_PRIVATE)
set(PC_REQ_PRIVATE)
set(PC_REQ_PUBLIC)

configure_file(misc/dframework.pc.in dframework.pc @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/dframework.pc DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig)
configure_file(misc/DFrameworkConfig.cmake.in DFramework/DFrameworkConfig.cmake @ONLY)
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/DFramework DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/cmake)

add_library(${BIN_NAME} SHARED
    ${INCLUDE_FILES}
    ${SRCS})

target_include_directories(${BIN_NAME} PUBLIC
    Qt5::Core
)

target_link_libraries(${BIN_NAME} PRIVATE
    Qt5::Core
)

install(FILES ${INCLUDE_FILES} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(TARGETS ${BIN_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})

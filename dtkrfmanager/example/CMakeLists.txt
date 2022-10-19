# SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
#
# SPDX-License-Identifier: LGPL-3.0-or-later

file(GLOB_RECURSE INCLUDE_FILES "../include/*.h")
set(LIB_NAME ${BIN_NAME})
set(BIN_NAME rf_example)

add_executable(${BIN_NAME}
    ${INCLUDE_FILES}
    main.cpp
    demo.h
    demo.cpp
)

include_directories(../include)

target_include_directories(${BIN_NAME} PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
)

target_link_libraries(${BIN_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    ${LIB_NAME}
)

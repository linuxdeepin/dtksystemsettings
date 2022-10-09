# SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
#
# SPDX-License-Identifier: LGPL-3.0-or-later

include_directories(../include)
file(GLOB_RECURSE SRCS "*.h" "*.cpp")


add_executable(demo
    ${SRCS}
)

target_link_libraries(demo PRIVATE
    ${BIN_NAME}
    Qt${QT_VERSION_MAJOR}::Core
)


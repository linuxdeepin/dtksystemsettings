# SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
#
# SPDX-License-Identifier: LGPL-3.0-or-later

function(set_install_dir TYPE DIR)
    set(FULLDIR ${CMAKE_INSTALL_PREFIX}/${DIR})    
    _set_install_dir(${TYPE} ${DIR} ${FULLDIR})
endfunction()

macro(_set_install_dir TYPE DIR FULLDIR)
    set(CMAKE_INSTALL_${TYPE}DIR ${DIR} PARENT_SCOPE)
    set(CMAKE_INSTALL_FULL_${TYPE}DIR ${FULLDIR} PARENT_SCOPE)    
endmacro()

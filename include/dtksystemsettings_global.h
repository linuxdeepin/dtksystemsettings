// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DTKSYSTEMSETTINGS_GLOBAL_H
#define DTKSYSTEMSETTINGS_GLOBAL_H

#if defined(DTK_STATIC_LIB)
#define LIBDTKSYSTEMSETTINGSSHARED_EXPORT
#else
#if defined(LIBDTKSYSTEMSETTINGS_LIBRARY)
#define LIBDTKSYSTEMSETTINGSSHARED_EXPORT Q_DECL_EXPORT
#else
#define LIBDTKSYSTEMSETTINGSSHARED_EXPORT Q_DECL_IMPORT
#endif
#endif

#endif  // DTKSYSTEMSETTINGS_GLOBAL_H
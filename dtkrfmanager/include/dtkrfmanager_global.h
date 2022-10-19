// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <QObject>

#define DRFMGR_NAMESPACE Dtk::RfMgr

#define DRFMGR_USE_NAMESPACE using namespace DRFMGR_NAMESPACE;

#define DRFMGR_BEGIN_NAMESPACE namespace Dtk { namespace RfMgr {

#define DRFMGR_END_NAMESPACE }}

#if defined(DTK_STATIC_LIB)
#  define LIBDTKRFMRGSHARED_EXPORT
#else
#if defined(LIBDTKRFMRG_LIBRARY)
#  define LIBDTKRFMRGSHARED_EXPORT Q_DECL_EXPORT
#else
#  define LIBDTKRFMRGSHARED_EXPORT Q_DECL_IMPORT
#endif
#endif

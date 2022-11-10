// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <QObject>
#define DTK_NAMESPACE Dtk
#define DRFMGR_NAMESPACE RfMgr
#define DTK_RFMGR_NAMESPACE DTK_NAMESPACE::DRFMGR_NAMESPACE

#define DRFMGR_USE_NAMESPACE using namespace DTK_RFMGR_NAMESPACE;

#define DRFMGR_BEGIN_NAMESPACE namespace DTK_NAMESPACE { namespace DRFMGR_NAMESPACE {

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

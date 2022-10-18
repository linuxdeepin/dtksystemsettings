// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
#ifndef DSYSTEMTIME_GLOBLE_H
#define DSYSTEMTIME_GLOBLE_H

#define DSYSTEMTIME_NAMESPACE Dtk::SystemTime

#define DSYSTEMTIME_USE_NAMESPACE using namespace DSYSTEMTIME_NAMESPACE;

#define DSYSTEMTIME_BEGIN_NAMESPACE                                                                                              \
    namespace Dtk {                                                                                                              \
    namespace SystemTime {
#define DSYSTEMTIME_END_NAMESPACE                                                                                                \
    }                                                                                                                            \
    }

#endif
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dlogintypes.h"
#include "dloginutils.h"
#include <QDebug>

DLOGIN_BEGIN_NAMESPACE

QDebug operator<<(QDebug debug, const Inhibitor &inhibitor)
{
    debug << "{";
    debug << "what: " << Utils::decodeBehavior(inhibitor.what) << ", ";
    debug << "who: " << inhibitor.who << ", ";
    debug << "why: " << inhibitor.why << ", ";
    debug << "mode: " << Utils::modeToString(inhibitor.mode) << ", ";
    debug << "UID: " << inhibitor.UID << ", ";
    debug << "PID: " << inhibitor.PID << "}";
    return debug;
}

DLOGIN_END_NAMESPACE
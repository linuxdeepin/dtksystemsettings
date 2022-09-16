// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "daccountstypes_p.h"
#include "daccountstypes.h"
#include <qdbusargument.h>
#include <qdbusextratypes.h>
#include <qdbusmetatype.h>

DACCOUNTS_BEGIN_NAMESPACE

const QDBusArgument &operator>>(const QDBusArgument &arg, LoginHistory_p &history)
{
    arg.beginStructure();
    arg >> history.login_time;
    arg >> history.logout_time;
    arg >> history.session_info;
    arg.endStructure();
    return arg;
}

QDBusArgument &operator<<(QDBusArgument &arg, const LoginHistory_p &history)
{
    arg.beginStructure();
    arg << history.login_time;
    arg << history.logout_time;
    arg << history.session_info;
    arg.endStructure();
    return arg;
}

void LoginHistory_p::registerMetaType()
{
    qRegisterMetaType<LoginHistory_p>("LoginHistory_p");
    qDBusRegisterMetaType<LoginHistory_p>();
    qDBusRegisterMetaType<QList<LoginHistory_p>>();
}

DACCOUNTS_END_NAMESPACE

// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "daccountstypes_p.h"
#include <qdbusargument.h>
#include <qdbusextratypes.h>
#include <qdbusmetatype.h>

DACCOUNTS_BEGIN_NAMESPACE

const QDBusArgument &operator>>(const QDBusArgument &arg, LoginHistory_p &history)
{
    arg.beginStructure();
    arg >> history.loginTime;
    arg >> history.logoutTime;
    arg >> history.sessionInfo;
    arg.endStructure();
    return arg;
}

QDBusArgument &operator<<(QDBusArgument &arg, const LoginHistory_p &history)
{
    arg.beginStructure();
    arg << history.loginTime;
    arg << history.logoutTime;
    arg << history.sessionInfo;
    arg.endStructure();
    return arg;
}

const QDBusArgument &operator>>(const QDBusArgument &arg, ReminderInfo_p &info)
{
    arg.beginStructure();

    arg >> info.userName;

    arg.beginStructure();
    arg >> info.spent.expired;
    arg >> info.spent.inactive;
    arg >> info.spent.lastChange;
    arg >> info.spent.max;
    arg >> info.spent.min;
    arg >> info.spent.warn;
    arg.endStructure();

    arg.beginStructure();
    arg >> info.currentLogin.address;
    arg >> info.currentLogin.host;
    arg >> info.currentLogin.inittabID;
    arg >> info.currentLogin.line;
    arg >> info.currentLogin.time;

    arg >> info.lastLogin.address;
    arg >> info.lastLogin.host;
    arg >> info.lastLogin.inittabID;
    arg >> info.lastLogin.line;
    arg >> info.lastLogin.time;
    arg.endStructure();

    arg >> info.failCountSinceLastLogin;

    arg.endStructure();
    return arg;
}

QDBusArgument &operator<<(QDBusArgument &arg, ReminderInfo_p &info)
{
    arg.beginStructure();

    arg << info.userName;

    arg.beginStructure();
    arg << info.spent.expired;
    arg << info.spent.inactive;
    arg << info.spent.lastChange;
    arg << info.spent.max;
    arg << info.spent.min;
    arg << info.spent.warn;
    arg.endStructure();

    arg.beginStructure();
    arg << info.currentLogin.address;
    arg << info.currentLogin.host;
    arg << info.currentLogin.inittabID;
    arg << info.currentLogin.line;
    arg << info.currentLogin.time;

    arg << info.lastLogin.address;
    arg << info.lastLogin.host;
    arg << info.lastLogin.inittabID;
    arg << info.lastLogin.line;
    arg << info.lastLogin.time;
    arg.endStructure();

    arg << info.failCountSinceLastLogin;

    arg.endStructure();
    return arg;
}

void LoginHistory_p::registerMetaType()
{
    qRegisterMetaType<LoginHistory_p>("LoginHistory_p");
    qDBusRegisterMetaType<LoginHistory_p>();
    qDBusRegisterMetaType<QList<LoginHistory_p>>();
}

void ShadowInfo_p::registerMetaType()
{
    qRegisterMetaType<ShadowInfo_p>("ShadowInfo_p");
    qDBusRegisterMetaType<ShadowInfo_p>();
}

void ReminderInfo_p::registerMetaType()
{
    qRegisterMetaType<ReminderInfo_p>("ReminderInfo_p");
    qDBusRegisterMetaType<ReminderInfo_p>();
}

DACCOUNTS_END_NAMESPACE

// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "namespace.h"
#include <QMap>
#include <QString>
#include <QVariant>

DACCOUNTS_BEGIN_NAMESPACE

// DBus Custom Type
struct LoginHistory
{
    qint64 login_time;
    qint64 logout_time;
    QMap<QString, QVariant> session_info;
};

// Common Custom Type

enum class AccountTypes : qint32 {
    DEFAULT = 0,
    ADMIN = 1,
    UNKNOWN = 2
};

enum class keyType{
        IconFile,
        Layout,
        LayoutList,
        Locale,
        UUID,
};

enum class PasswdStatus{
    P,
    NP,
    L,
    UNKNOWN
};

enum class PasswdExpirInfo{
    NOR,
    CLO,
    EXP,
    UNKNOWN
};

struct Question{
    qint32 questionIndex;
    QByteArray encryptQuestion;
};
struct shadowInfo{
    qint32 lastChange;
    qint32 min;
    qint32 max;
    qint32 warn;
    qint32 inactive;
    qint32 expired;
};
struct loginUtmpx{
    QByteArray inittabID;
    QByteArray Line;
    QByteArray Host;
    QByteArray Address;
    QByteArray Time;
};
struct ReminderInfo{
    QByteArray userName;
    shadowInfo spent;
    loginUtmpx currentLogin;
    loginUtmpx lastLogin; 
    qint32 failCountSinceLastLogin;
};

DACCOUNTS_END_NAMESPACE

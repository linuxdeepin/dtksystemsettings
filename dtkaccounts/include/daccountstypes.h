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
    qint64 loginTime;
    qint64 logoutTime;
    QMap<QString, QVariant> sessionInfo;
};

// Common Custom Type

enum class AccountTypes : qint32 { Default = 0, Admin, Udcp };

enum class keyType {
    IconFile,
    Layout,
    LayoutList,
    Locale,
    UUID,
};

enum class PasswdStatus { P, NP, L };

enum class PasswdExpirInfo { NOR, CLO, EXP };

struct Question
{
    qint32 questionIndex;
    QByteArray encryptQuestion;
};
struct ShadowInfo
{
    qint32 lastChange;
    qint32 min;
    qint32 max;
    qint32 warn;
    qint32 inactive;
    qint32 expired;
};
struct LoginUtmpx
{
    QByteArray inittabID;
    QByteArray line;
    QByteArray host;
    QByteArray address;
    QByteArray time;
};
struct ReminderInfo
{
    QByteArray userName;
    ShadowInfo spent;
    LoginUtmpx currentLogin;
    LoginUtmpx lastLogin;
    qint32 failCountSinceLastLogin;
};

DACCOUNTS_END_NAMESPACE

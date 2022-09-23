// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "namespace.h"
#include <QMap>
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

enum class AccountTypes : qint32 {
    Default = 0,  // 普通账户
    Admin,        // 管理员
    Udcp,         // 域管账户
    Unknown       // 未知
};

enum class keyType {
    IconFile,    // 图标路径
    Layout,      // 布局
    LayoutList,  // 历史布局
    Locale,      // 本地化
    UUID,        // 用户的UUID
    Unknown      // 未知
};

enum class PasswdStatus {
    P,       // 有密码
    NP,      // 无密码
    L,       // 账户被锁定
    Unknown  // 未知
};

enum class PasswdExpirInfo {
    Normal,   // 没有过期
    Closed,   // 将要过期
    Expired,  // 已过期
    Unknown   // 未知
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

struct ValidMsg
{
    bool valid;
    qint32 code;
    QString msg;
};

DACCOUNTS_END_NAMESPACE

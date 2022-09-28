// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "namespace.h"
#include <QMap>
#include <QVariant>

DACCOUNTS_BEGIN_NAMESPACE

// Common Custom Type

/**
 * @brief type of user account
 */
enum class AccountTypes : qint32 {
    Default = 0,
    Admin,
    Udcp, /**< Domain Controller */
    Unknown
};

/**
 * @brief keys in the configuration file
 */
enum class keyType {
    IconFile,   /**< icon file path     */
    Layout,     /**< keyboard layout     */
    LayoutList, /**< keyboard layout list*/
    Locale,
    UUID,
    Unknown
};

/**
 * @brief password status
 */
enum class PasswdStatus { Password, NoPassword, Locked, Unknown };

/**
 * @brief Password Expiration Information
 */
enum class PasswdExpirInfo { Normal, Closed, Expired, Unknown };

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

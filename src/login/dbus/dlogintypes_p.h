// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "dtklogin_global.h"

#include <qdbusargument.h>
#include <qdbusextratypes.h>
#include <qdbusmetatype.h>
#include <qglobal.h>
#include <qlist.h>
#include <qmetatype.h>
#include <qnamespace.h>

DLOGIN_BEGIN_NAMESPACE

struct DBusScheduledShutdownValue
{
    QString type;
    quint64 usec;
    static void registerMetaType();
    bool operator==(const DBusScheduledShutdownValue &v);
    bool operator!=(const DBusScheduledShutdownValue &v);
};

struct DBusInhibitor
{
    QString what;
    QString who;
    QString why;
    QString mode;
    quint32 UID;
    quint32 PID;
    static void registerMetaType();
};

struct DBusSeat
{
    QString seatId;
    QDBusObjectPath path;
    static void registerMetaType();
    bool operator==(const DBusSeat &v);
    bool operator!=(const DBusSeat &v);
};

struct DBusSeatPath
{
    QString seatId;
    QDBusObjectPath path;
    static void registerMetaType();
    bool operator==(const DBusSeatPath &v);
    bool operator!=(const DBusSeatPath &v);
};

struct DBusSession
{
    QString sessionId;
    quint32 userId;
    QString userName;
    QString seatId;
    QDBusObjectPath path;
    static void registerMetaType();
};

struct DBusUser
{
    quint32 userId;
    QString userName;
    QDBusObjectPath path;
    static void registerMetaType();
};

struct DBusSessionPath
{
    QString sessionId;
    QDBusObjectPath path;
    static void registerMetaType();
    bool operator==(const DBusSessionPath &v);
    bool operator!=(const DBusSessionPath &v);
};

struct DBusUserPath
{
    uint userId;
    QDBusObjectPath path;
    static void registerMetaType();
    bool operator==(const DBusUserPath &v);
    bool operator!=(const DBusUserPath &v);
};

QDBusArgument &operator<<(QDBusArgument &arg, const DBusScheduledShutdownValue &value);
const QDBusArgument &operator>>(const QDBusArgument &arg, DBusScheduledShutdownValue &value);
QDBusArgument &operator<<(QDBusArgument &arg, const DBusInhibitor &inhibitor);
const QDBusArgument &operator>>(const QDBusArgument &arg, DBusInhibitor &inhibitor);
QDBusArgument &operator<<(QDBusArgument &arg, const DBusSeat &seat);
const QDBusArgument &operator>>(const QDBusArgument &arg, DBusSeat &seat);
QDBusArgument &operator<<(QDBusArgument &arg, const DBusSeatPath &seat);
const QDBusArgument &operator>>(const QDBusArgument &arg, DBusSeatPath &seat);
QDBusArgument &operator<<(QDBusArgument &arg, const DBusSession &session);
const QDBusArgument &operator>>(const QDBusArgument &arg, DBusSession &session);
QDBusArgument &operator<<(QDBusArgument &arg, const DBusUser &user);
const QDBusArgument &operator>>(const QDBusArgument &arg, DBusUser &user);
QDBusArgument &operator<<(QDBusArgument &arg, const DBusSessionPath &path);
const QDBusArgument &operator>>(const QDBusArgument &arg, DBusSessionPath &path);
QDBusArgument &operator<<(QDBusArgument &arg, const DBusUserPath &path);
const QDBusArgument &operator>>(const QDBusArgument &arg, DBusUserPath &path);

DLOGIN_END_NAMESPACE
Q_DECLARE_METATYPE(DTK_LOGIN_NAMESPACE::DBusScheduledShutdownValue)
Q_DECLARE_METATYPE(DTK_LOGIN_NAMESPACE::DBusInhibitor)
Q_DECLARE_METATYPE(DTK_LOGIN_NAMESPACE::DBusSeat)
Q_DECLARE_METATYPE(DTK_LOGIN_NAMESPACE::DBusSeatPath)
Q_DECLARE_METATYPE(DTK_LOGIN_NAMESPACE::DBusSession)
Q_DECLARE_METATYPE(DTK_LOGIN_NAMESPACE::DBusUser)
Q_DECLARE_METATYPE(DTK_LOGIN_NAMESPACE::DBusSessionPath)
Q_DECLARE_METATYPE(DTK_LOGIN_NAMESPACE::DBusUserPath)

// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "namespace.h"
#include <qdbusargument.h>
#include <qdbusextratypes.h>
#include <qdbusmetatype.h>
#include <qmetatype.h>
#include <qglobal.h>
#include <qlist.h>
#include <qnamespace.h>

DLOGIN_BEGIN_NAMESPACE

struct DBusScheduledShutdownValue
{
    QString type;
    quint64 usec;
    static void registerMetaType();
};

struct DBusSessionProperty
{
    QString name;
    QDBusVariant var;
    static void registerMetaType();
};

struct DBusInhibitor
{
    QString what;
    QString who;
    QString why;
    QString mode;
    uint    uid;
    uint    pid;
    static void registerMetaType();
};

struct DBusSeat
{
    QString seatId;
    QDBusObjectPath path;
    static void registerMetaType();
};

struct DBusSession
{
    QString sessionId;
    uint userId;
    QString userName;
    QString seatId;
    QDBusObjectPath path;
    static void registerMetaType();
};

struct DBusUser
{
    uint userId;
    QString userName;
    QDBusObjectPath path;
    static void registerMetaType();
};

typedef DBusSeat DBusSeatPath;

struct DBusSessionPath
{
    QString sessionId;
    QDBusObjectPath path;
    static void registerMetaType();
};

struct DBusUserPath
{
    uint userId;
    QDBusObjectPath path;
    static void registerMetaType();
};

QDBusArgument &operator<<(QDBusArgument &arg, const DBusScheduledShutdownValue &value);
const QDBusArgument &operator>>(const QDBusArgument &arg, DBusScheduledShutdownValue &value);
QDBusArgument &operator<<(QDBusArgument &arg, const DBusSessionProperty &property);
const QDBusArgument &operator>>(const QDBusArgument &arg, DBusSessionProperty &property);
QDBusArgument &operator<<(QDBusArgument &arg, const DBusInhibitor &inhibitor);
const QDBusArgument &operator>>(const QDBusArgument &arg, DBusInhibitor &inhibitor);
QDBusArgument &operator<<(QDBusArgument &arg, const DBusSeat &seat);
const QDBusArgument &operator>>(const QDBusArgument &arg, DBusSeat &seat);
QDBusArgument &operator<<(QDBusArgument &arg, const DBusSession &session);
const QDBusArgument &operator>>(const QDBusArgument &arg, DBusSession &session);
QDBusArgument &operator<<(QDBusArgument &arg, const DBusUser &user);
const QDBusArgument &operator>>(const QDBusArgument &arg, DBusUser &user);
QDBusArgument &operator<<(QDBusArgument &arg, const DBusSessionPath &path);
const QDBusArgument &operator>>(const QDBusArgument &arg, DBusSessionPath &path);
QDBusArgument &operator<<(QDBusArgument &arg, const DBusUserPath &path);
const QDBusArgument &operator>>(const QDBusArgument &arg, DBusUserPath &path);

DLOGIN_END_NAMESPACE
Q_DECLARE_METATYPE(DLOGIN_NAMESPACE::DBusScheduledShutdownValue)
Q_DECLARE_METATYPE(DLOGIN_NAMESPACE::DBusSessionProperty)
Q_DECLARE_METATYPE(DLOGIN_NAMESPACE::DBusInhibitor)
Q_DECLARE_METATYPE(DLOGIN_NAMESPACE::DBusSeat)
Q_DECLARE_METATYPE(DLOGIN_NAMESPACE::DBusSession)
Q_DECLARE_METATYPE(DLOGIN_NAMESPACE::DBusUser)
Q_DECLARE_METATYPE(DLOGIN_NAMESPACE::DBusSessionPath)
Q_DECLARE_METATYPE(DLOGIN_NAMESPACE::DBusUserPath)


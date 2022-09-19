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

struct ScheduledShutdownValue_p
{
    QString type;
    quint64 usec;
    static void registerMetaType();
};

struct SessionProperty_p
{
    QString name;
    QDBusVariant var;
    static void registerMetaType();
};

struct Inhibitor_p
{
    QString what;
    QString who;
    QString why;
    QString mode;
    uint    uid;
    uint    pid;
    static void registerMetaType();
};

struct Seat_p
{
    QString seatId;
    QDBusObjectPath path;
    static void registerMetaType();
};

struct Session_p
{
    QString sessionId;
    uint userId;
    QString userName;
    QString seatId;
    QDBusObjectPath path;
    static void registerMetaType();
};

struct User_p
{
    uint userId;
    QString userName;
    QDBusObjectPath path;
    static void registerMetaType();
};

typedef Seat_p SeatPath_p;

struct SessionPath_p
{
    QString sessionId;
    QDBusObjectPath path;
    static void registerMetaType();
};

struct UserPath_p
{
    uint userId;
    QDBusObjectPath path;
    static void registerMetaType();
};

QDBusArgument &operator<<(QDBusArgument &arg, const ScheduledShutdownValue_p &value);
const QDBusArgument &operator>>(const QDBusArgument &arg, ScheduledShutdownValue_p &value);
QDBusArgument &operator<<(QDBusArgument &arg, const SessionProperty_p &property);
const QDBusArgument &operator>>(const QDBusArgument &arg, SessionProperty_p &property);
QDBusArgument &operator<<(QDBusArgument &arg, const Inhibitor_p &inhibitor);
const QDBusArgument &operator>>(const QDBusArgument &arg, Inhibitor_p &inhibitor);
QDBusArgument &operator<<(QDBusArgument &arg, const Seat_p &seat);
const QDBusArgument &operator>>(const QDBusArgument &arg, Seat_p &seat);
QDBusArgument &operator<<(QDBusArgument &arg, const Session_p &session);
const QDBusArgument &operator>>(const QDBusArgument &arg, Session_p &session);
QDBusArgument &operator<<(QDBusArgument &arg, const User_p &user);
const QDBusArgument &operator>>(const QDBusArgument &arg, User_p &user);
QDBusArgument &operator<<(QDBusArgument &arg, const SessionPath_p &path);
const QDBusArgument &operator>>(const QDBusArgument &arg, SessionPath_p &path);
QDBusArgument &operator<<(QDBusArgument &arg, const UserPath_p &path);
const QDBusArgument &operator>>(const QDBusArgument &arg, UserPath_p &path);

DLOGIN_END_NAMESPACE
Q_DECLARE_METATYPE(DLOGIN_NAMESPACE::ScheduledShutdownValue_p)
Q_DECLARE_METATYPE(DLOGIN_NAMESPACE::SessionProperty_p)
Q_DECLARE_METATYPE(DLOGIN_NAMESPACE::Inhibitor_p)
Q_DECLARE_METATYPE(DLOGIN_NAMESPACE::Seat_p)
Q_DECLARE_METATYPE(DLOGIN_NAMESPACE::Session_p)
Q_DECLARE_METATYPE(DLOGIN_NAMESPACE::User_p)
Q_DECLARE_METATYPE(DLOGIN_NAMESPACE::SessionPath_p)
Q_DECLARE_METATYPE(DLOGIN_NAMESPACE::UserPath_p)


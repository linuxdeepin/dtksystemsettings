// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dlogintypes_p.h"
#include <qdbusmetatype.h>

DLOGIN_BEGIN_NAMESPACE

QDBusArgument &operator<< (QDBusArgument &arg, const ScheduledShutdownValue_p &value)
{
    arg.beginStructure();
    arg << value.type;
    arg << value.usec;
    arg.endStructure();
    return arg;
}

const QDBusArgument &operator>> (const QDBusArgument &arg, ScheduledShutdownValue_p &value)
{
    arg.beginStructure();
    arg >> value.type;
    arg >> value.usec;
    arg.endStructure();
    return arg;
}

QDBusArgument &operator<< (QDBusArgument &arg, const SessionProperty_p &property)
{
    arg.beginStructure();
    arg << property.name;
    arg << property.var;
    arg.endStructure();
    return arg;
}

const QDBusArgument &operator>> (const QDBusArgument &arg, SessionProperty_p &property)
{
    arg.beginStructure();
    arg >> property.name;
    arg >> property.var;
    arg.endStructure();
    return arg;
}

QDBusArgument &operator<< (QDBusArgument &arg, const Inhibitor_p &inhibitor)
{
    arg.beginStructure();
    arg << inhibitor.what;
    arg << inhibitor.who;
    arg << inhibitor.why;
    arg << inhibitor.mode;
    arg << inhibitor.uid;
    arg << inhibitor.pid;
    arg.endStructure();
    return arg;
}

const QDBusArgument &operator>> (const QDBusArgument &arg, Inhibitor_p &inhibitor)
{
    arg.beginStructure();
    arg >> inhibitor.what;
    arg >> inhibitor.who;
    arg >> inhibitor.why;
    arg >> inhibitor.mode;
    arg >> inhibitor.uid;
    arg >> inhibitor.pid;
    arg.endStructure();
    return arg;
}

QDBusArgument &operator<< (QDBusArgument &arg, const Seat_p &seat)
{
    arg.beginStructure();
    arg << seat.seat_id;
    arg << seat.path;
    arg.endStructure();
    return arg;
}

const QDBusArgument &operator>> (const QDBusArgument &arg, Seat_p &seat)
{
    arg.beginStructure();
    arg >> seat.seat_id;
    arg >> seat.path;
    arg.endStructure();
    return arg;
}

QDBusArgument &operator<< (QDBusArgument &arg, const Session_p &session)
{
    arg.beginStructure();
    arg << session.session_id;
    arg << session.user_id;
    arg << session.user_name;
    arg << session.seat_id;
    arg << session.path;
    arg.endStructure();
    return arg;
}

const QDBusArgument &operator>> (const QDBusArgument &arg, Session_p &session)
{
    arg.beginStructure();
    arg >> session.session_id;
    arg >> session.user_id;
    arg >> session.user_name;
    arg >> session.seat_id;
    arg >> session.path;
    arg.endStructure();
    return arg;
}

QDBusArgument &operator<< (QDBusArgument &arg, const User_p &user)
{
    arg.beginStructure();
    arg << user.user_id;
    arg << user.user_name;
    arg << user.path;
    arg.endStructure();
    return arg;
}

const QDBusArgument &operator>> (const QDBusArgument &arg, User_p &user)
{
    arg.beginStructure();
    arg >> user.user_id;
    arg >> user.user_name;
    arg >> user.path;
    arg.endStructure();
    return arg;
}

QDBusArgument &operator<< (QDBusArgument &arg, const SessionPath_p &path)
{
    arg.beginStructure();
    arg << path.session_id;
    arg << path.path;
    arg.endStructure();
    return arg;
}

const QDBusArgument &operator>> (const QDBusArgument &arg, SessionPath_p &path)
{
    arg.beginStructure();
    arg >> path.session_id;
    arg >> path.path;
    arg.endStructure();
    return arg;
}

QDBusArgument &operator<< (QDBusArgument &arg, const UserPath_p &path)
{
    arg.beginStructure();
    arg << path.user_id;
    arg << path.path;
    arg.endStructure();
    return arg;
}

const QDBusArgument &operator>> (const QDBusArgument &arg, UserPath_p &path)
{
    arg.beginStructure();
    arg >> path.user_id;
    arg >> path.path;
    arg.endStructure();
    return arg;
}

void ScheduledShutdownValue_p::registerMetaType()
{
    qRegisterMetaType<ScheduledShutdownValue_p>("ScheduledShutdownValue_p");
    qDBusRegisterMetaType<ScheduledShutdownValue_p>();
    qDBusRegisterMetaType<QList<ScheduledShutdownValue_p>>();
}

void SessionProperty_p::registerMetaType()
{
    qRegisterMetaType<SessionProperty_p>("SessionProperty_p");
    qDBusRegisterMetaType<SessionProperty_p>();
    qDBusRegisterMetaType<QList<SessionProperty_p>>();
}

void Inhibitor_p::registerMetaType()
{
    qRegisterMetaType<Inhibitor_p>("Inhibitor_p");
    qDBusRegisterMetaType<Inhibitor_p>();
    qDBusRegisterMetaType<QList<Inhibitor_p>>();
}

void Seat_p::registerMetaType()
{
    qRegisterMetaType<Seat_p>("Seat_p");
    qDBusRegisterMetaType<Seat_p>();
    qDBusRegisterMetaType<QList<Seat_p>>();
}

void Session_p::registerMetaType()
{
    qRegisterMetaType<Session_p>("Session_p");
    qDBusRegisterMetaType<Session_p>();
    qDBusRegisterMetaType<QList<Session_p>>();
}

void User_p::registerMetaType()
{
    qRegisterMetaType<User_p>("User_p");
    qDBusRegisterMetaType<User_p>();
    qDBusRegisterMetaType<QList<User_p>>();
}

void SessionPath_p::registerMetaType()
{
    qRegisterMetaType<SessionPath_p>("SessionPath_p");
    qDBusRegisterMetaType<SessionPath_p>();
    qDBusRegisterMetaType<QList<SessionPath_p>>();
}

void UserPath_p::registerMetaType()
{
    qRegisterMetaType<UserPath_p>("UserPath_p");
    qDBusRegisterMetaType<UserPath_p>();
    qDBusRegisterMetaType<QList<UserPath_p>>();
}

DLOGIN_END_NAMESPACE

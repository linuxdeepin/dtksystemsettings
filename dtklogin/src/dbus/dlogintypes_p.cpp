// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dlogintypes_p.h"
#include <qdbusmetatype.h>

DLOGIN_BEGIN_NAMESPACE

QDBusArgument &operator<< (QDBusArgument &arg, const DBusScheduledShutdownValue &value)
{
    arg.beginStructure();
    arg << value.type;
    arg << value.usec;
    arg.endStructure();
    return arg;
}

const QDBusArgument &operator>> (const QDBusArgument &arg, DBusScheduledShutdownValue &value)
{
    arg.beginStructure();
    arg >> value.type;
    arg >> value.usec;
    arg.endStructure();
    return arg;
}

QDBusArgument &operator<< (QDBusArgument &arg, const DBusSessionProperty &property)
{
    arg.beginStructure();
    arg << property.name;
    arg << property.var;
    arg.endStructure();
    return arg;
}

const QDBusArgument &operator>> (const QDBusArgument &arg, DBusSessionProperty &property)
{
    arg.beginStructure();
    arg >> property.name;
    arg >> property.var;
    arg.endStructure();
    return arg;
}

QDBusArgument &operator<< (QDBusArgument &arg, const DBusInhibitor &inhibitor)
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

const QDBusArgument &operator>> (const QDBusArgument &arg, DBusInhibitor &inhibitor)
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

QDBusArgument &operator<< (QDBusArgument &arg, const DBusSeat &seat)
{
    arg.beginStructure();
    arg << seat.seatId;
    arg << seat.path;
    arg.endStructure();
    return arg;
}

const QDBusArgument &operator>> (const QDBusArgument &arg, DBusSeat &seat)
{
    arg.beginStructure();
    arg >> seat.seatId;
    arg >> seat.path;
    arg.endStructure();
    return arg;
}

QDBusArgument &operator<< (QDBusArgument &arg, const DBusSession &session)
{
    arg.beginStructure();
    arg << session.sessionId;
    arg << session.userId;
    arg << session.userName;
    arg << session.seatId;
    arg << session.path;
    arg.endStructure();
    return arg;
}

const QDBusArgument &operator>> (const QDBusArgument &arg, DBusSession &session)
{
    arg.beginStructure();
    arg >> session.sessionId;
    arg >> session.userId;
    arg >> session.userName;
    arg >> session.seatId;
    arg >> session.path;
    arg.endStructure();
    return arg;
}

QDBusArgument &operator<< (QDBusArgument &arg, const DBusUser &user)
{
    arg.beginStructure();
    arg << user.userId;
    arg << user.userName;
    arg << user.path;
    arg.endStructure();
    return arg;
}

const QDBusArgument &operator>> (const QDBusArgument &arg, DBusUser &user)
{
    arg.beginStructure();
    arg >> user.userId;
    arg >> user.userName;
    arg >> user.path;
    arg.endStructure();
    return arg;
}

QDBusArgument &operator<< (QDBusArgument &arg, const DBusSessionPath &path)
{
    arg.beginStructure();
    arg << path.sessionId;
    arg << path.path;
    arg.endStructure();
    return arg;
}

const QDBusArgument &operator>> (const QDBusArgument &arg, DBusSessionPath &path)
{
    arg.beginStructure();
    arg >> path.sessionId;
    arg >> path.path;
    arg.endStructure();
    return arg;
}

QDBusArgument &operator<< (QDBusArgument &arg, const DBusUserPath &path)
{
    arg.beginStructure();
    arg << path.userId;
    arg << path.path;
    arg.endStructure();
    return arg;
}

const QDBusArgument &operator>> (const QDBusArgument &arg, DBusUserPath &path)
{
    arg.beginStructure();
    arg >> path.userId;
    arg >> path.path;
    arg.endStructure();
    return arg;
}

void DBusScheduledShutdownValue::registerMetaType()
{
    qRegisterMetaType<DBusScheduledShutdownValue>("ScheduledShutdownValue_p");
    qDBusRegisterMetaType<DBusScheduledShutdownValue>();
    qDBusRegisterMetaType<QList<DBusScheduledShutdownValue>>();
}

void DBusSessionProperty::registerMetaType()
{
    qRegisterMetaType<DBusSessionProperty>("SessionProperty_p");
    qDBusRegisterMetaType<DBusSessionProperty>();
    qDBusRegisterMetaType<QList<DBusSessionProperty>>();
}

void DBusInhibitor::registerMetaType()
{
    qRegisterMetaType<DBusInhibitor>("Inhibitor_p");
    qDBusRegisterMetaType<DBusInhibitor>();
    qDBusRegisterMetaType<QList<DBusInhibitor>>();
}

void DBusSeat::registerMetaType()
{
    qRegisterMetaType<DBusSeat>("Seat_p");
    qDBusRegisterMetaType<DBusSeat>();
    qDBusRegisterMetaType<QList<DBusSeat>>();
}

void DBusSession::registerMetaType()
{
    qRegisterMetaType<DBusSession>("Session_p");
    qDBusRegisterMetaType<DBusSession>();
    qDBusRegisterMetaType<QList<DBusSession>>();
}

void DBusUser::registerMetaType()
{
    qRegisterMetaType<DBusUser>("User_p");
    qDBusRegisterMetaType<DBusUser>();
    qDBusRegisterMetaType<QList<DBusUser>>();
}

void DBusSessionPath::registerMetaType()
{
    qRegisterMetaType<DBusSessionPath>("SessionPath_p");
    qDBusRegisterMetaType<DBusSessionPath>();
    qDBusRegisterMetaType<QList<DBusSessionPath>>();
}

void DBusUserPath::registerMetaType()
{
    qRegisterMetaType<DBusUserPath>("UserPath_p");
    qDBusRegisterMetaType<DBusUserPath>();
    qDBusRegisterMetaType<QList<DBusUserPath>>();
}

DLOGIN_END_NAMESPACE

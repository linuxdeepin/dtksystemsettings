// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "login1sessionservice.h"

#include <qmetaobject.h>
#include <qbytearray.h>
#include <qlist.h>
#include <qmap.h>
#include <qstring.h>
#include <qstringlist.h>
#include <qvariant.h>

#include "dlogintypes_p.h"

DLOGIN_BEGIN_NAMESPACE
/*
 * Implementation of adaptor class Login1SessionAdaptor
 */

Login1SessionService::Login1SessionService(QObject *parent)
    : QObject(parent)
{
}

bool Login1SessionService::active() const
{
    // get the value of property Active
    return qvariant_cast<bool>(parent()->property("Active"));
}

uint Login1SessionService::audit() const
{
    // get the value of property Audit
    return qvariant_cast<uint>(parent()->property("Audit"));
}

QString Login1SessionService::sessionClass() const
{
    // get the value of property Class
    return qvariant_cast<QString>(parent()->property("Class"));
}

QString Login1SessionService::desktop() const
{
    // get the value of property Desktop
    return qvariant_cast<QString>(parent()->property("Desktop"));
}

QString Login1SessionService::display() const
{
    // get the value of property Display
    return qvariant_cast<QString>(parent()->property("Display"));
}

QString Login1SessionService::id() const
{
    // get the value of property Id
    return qvariant_cast<QString>(parent()->property("Id"));
}

bool Login1SessionService::idleHint() const
{
    // get the value of property IdleHint
    return qvariant_cast<bool>(parent()->property("IdleHint"));
}

qulonglong Login1SessionService::idleSinceHint() const
{
    // get the value of property IdleSinceHint
    return qvariant_cast<qulonglong>(parent()->property("IdleSinceHint"));
}

qulonglong Login1SessionService::idleSinceHintMonotonic() const
{
    // get the value of property IdleSinceHintMonotonic
    return qvariant_cast<qulonglong>(parent()->property("IdleSinceHintMonotonic"));
}

uint Login1SessionService::leader() const
{
    // get the value of property Leader
    return qvariant_cast<uint>(parent()->property("Leader"));
}

bool Login1SessionService::lockedHint() const
{
    // get the value of property LockedHint
    return qvariant_cast<bool>(parent()->property("LockedHint"));
}

QString Login1SessionService::name() const
{
    // get the value of property Name
    return qvariant_cast<QString>(parent()->property("Name"));
}

bool Login1SessionService::remote() const
{
    // get the value of property Remote
    return qvariant_cast<bool>(parent()->property("Remote"));
}

QString Login1SessionService::remoteHost() const
{
    // get the value of property RemoteHost
    return qvariant_cast<QString>(parent()->property("RemoteHost"));
}

QString Login1SessionService::remoteUser() const
{
    // get the value of property RemoteUser
    return qvariant_cast<QString>(parent()->property("RemoteUser"));
}

QString Login1SessionService::scope() const
{
    // get the value of property Scope
    return qvariant_cast<QString>(parent()->property("Scope"));
}

DBusSeatPath Login1SessionService::seat() const
{
    // get the value of property Seat
    return qvariant_cast<DBusSeatPath>(parent()->property("Seat"));
}

QString Login1SessionService::service() const
{
    // get the value of property Service
    return qvariant_cast<QString>(parent()->property("Service"));
}

QString Login1SessionService::state() const
{
    // get the value of property State
    return qvariant_cast<QString>(parent()->property("State"));
}

QString Login1SessionService::tTY() const
{
    // get the value of property TTY
    return qvariant_cast<QString>(parent()->property("TTY"));
}

qulonglong Login1SessionService::timestamp() const
{
    // get the value of property Timestamp
    return qvariant_cast<qulonglong>(parent()->property("Timestamp"));
}

qulonglong Login1SessionService::timestampMonotonic() const
{
    // get the value of property TimestampMonotonic
    return qvariant_cast<qulonglong>(parent()->property("TimestampMonotonic"));
}

QString Login1SessionService::type() const
{
    // get the value of property Type
    return qvariant_cast<QString>(parent()->property("Type"));
}

DBusUserPath Login1SessionService::user() const
{
    // get the value of property User
    return qvariant_cast<DBusUserPath>(parent()->property("User"));
}

uint Login1SessionService::VTNr() const
{
    // get the value of property VTNr
    return qvariant_cast<uint>(parent()->property("VTNr"));
}

void Login1SessionService::Activate()
{
    // handle method call org.freedesktop.login1.Session.Activate
    QMetaObject::invokeMethod(parent(), "Activate");
}

void Login1SessionService::Kill(const QString &who, int signal_number)
{
    // handle method call org.freedesktop.login1.Session.Kill
    QMetaObject::invokeMethod(parent(), "Kill", Q_ARG(QString, who), Q_ARG(int, signal_number));
}

void Login1SessionService::Lock()
{
    // handle method call org.freedesktop.login1.Session.Lock
    QMetaObject::invokeMethod(parent(), "Lock");
}

void Login1SessionService::SetIdleHint(bool idle)
{
    // handle method call org.freedesktop.login1.Session.SetIdleHint
    QMetaObject::invokeMethod(parent(), "SetIdleHint", Q_ARG(bool, idle));
}

void Login1SessionService::Terminate()
{
    // handle method call org.freedesktop.login1.Session.Terminate
    QMetaObject::invokeMethod(parent(), "Terminate");
}
DLOGIN_END_NAMESPACE

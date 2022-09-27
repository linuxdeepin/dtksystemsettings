// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "login1userservice.h"

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
 * Implementation of adaptor class Login1UserAdaptor
 */

Login1UserService::Login1UserService(QObject *parent)
    : QObject(parent)
{
}

DBusSessionPath Login1UserService::display() const
{
    // get the value of property Display
    return qvariant_cast<DBusSessionPath>(parent()->property("Display"));
}

quint32 Login1UserService::GID() const
{
    // get the value of property GID
    return qvariant_cast<uint>(parent()->property("GID"));
}

QString Login1UserService::name() const
{
    // get the value of property Name
    return qvariant_cast<QString>(parent()->property("Name"));
}

QString Login1UserService::runtimePath() const
{
    // get the value of property RuntimePath
    return qvariant_cast<QString>(parent()->property("RuntimePath"));
}

QString Login1UserService::service() const
{
    // get the value of property Service
    return qvariant_cast<QString>(parent()->property("Service"));
}

QString Login1UserService::slice() const
{
    // get the value of property Slice
    return qvariant_cast<QString>(parent()->property("Slice"));
}

QString Login1UserService::state() const
{
    // get the value of property State
    return qvariant_cast<QString>(parent()->property("State"));
}

qulonglong Login1UserService::timestamp() const
{
    // get the value of property Timestamp
    return qvariant_cast<qulonglong>(parent()->property("Timestamp"));
}

qulonglong Login1UserService::timestampMonotonic() const
{
    // get the value of property TimestampMonotonic
    return qvariant_cast<qulonglong>(parent()->property("TimestampMonotonic"));
}

quint32 Login1UserService::UID() const
{
    // get the value of property UID
    return qvariant_cast<uint>(parent()->property("UID"));
}

void Login1UserService::Kill(const qint32 signalNumber)
{
    Q_UNUSED(signalNumber)
}

void Login1UserService::Terminate() {}

DLOGIN_END_NAMESPACE
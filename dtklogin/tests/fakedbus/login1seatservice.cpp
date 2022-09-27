// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "login1seatservice.h"

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
 * Implementation of adaptor class Login1SeatAdaptor
 */

Login1SeatService::Login1SeatService(QObject *parent)
    : QObject(parent)
{
}

DBusSessionPath Login1SeatService::activeSession() const
{
    // get the value of property ActiveSession
    return qvariant_cast<DBusSessionPath>(parent()->property("ActiveSession"));
}

bool Login1SeatService::canGraphical() const
{
    // get the value of property CanGraphical
    return qvariant_cast<bool>(parent()->property("CanGraphical"));
}

bool Login1SeatService::canTTY() const
{
    // get the value of property CanTTY
    return qvariant_cast<bool>(parent()->property("CanTTY"));
}

QString Login1SeatService::id() const
{
    // get the value of property Id
    return qvariant_cast<QString>(parent()->property("Id"));
}

void Login1SeatService::ActivateSession(const QString &sessionId)
{
    Q_UNUSED(sessionId)
}
void Login1SeatService::SwitchTo(const uint VTNr)
{
    Q_UNUSED(VTNr)
}
void Login1SeatService::SwitchToNext() {}
void Login1SeatService::SwitchToPrevious() {}

DLOGIN_END_NAMESPACE
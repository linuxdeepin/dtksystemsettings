// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "namespace.h"
#include <qobject.h>
#include <qvariant.h>

DLOGIN_BEGIN_NAMESPACE
struct ScheduledShutdownValue
{
    QString type;
    quint64 usec;
};

struct SessionProperty
{
    QString name;
    QVariant var;
};

struct Inhibitor
{
    QString what;
    QString who;
    QString why;
    QString mode;
    uint    uid;
    uint    pid;
};

struct Seat
{
    QString seatId;
    QString path;
};

struct Session
{
    QString sessionId;
    uint userId;
    QString userName;
    QString seatId;
    QString path;
};

struct User
{
    uint userId;
    QString userName;
    QString path;
};

typedef Seat SeatPath;

struct SessionPath
{
    QString sessionId;
    QString path;
};

struct UserPath
{
    uint userId;
    QString path;
};

DLOGIN_END_NAMESPACE

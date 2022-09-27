// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <qobject.h>
#include <QtDBus>

#include "namespace.h"
QT_BEGIN_NAMESPACE
class QByteArray;
template <class T>
class QList;
template <class Key, class Value>
class QMap;
class QString;
class QStringList;
class QVariant;
QT_END_NAMESPACE

DLOGIN_BEGIN_NAMESPACE
struct DBusSessionPath;
/*
 * Adaptor class for interface org.freedesktop.login1.Seat
 */
class Login1SeatService : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.freedesktop.login1.Seat")
public:
    Login1SeatService(QObject *parent);

public:  // PROPERTIES
    Q_PROPERTY(DBusSessionPath ActiveSession READ activeSession)
    Q_PROPERTY(bool CanGraphical READ canGraphical)
    Q_PROPERTY(bool CanTTY READ canTTY)
    Q_PROPERTY(QString Id READ id)

    DBusSessionPath activeSession() const;
    bool canGraphical() const;
    bool canTTY() const;
    QString id() const;

public Q_SLOTS:  // METHODS
    void ActivateSession(const QString &sessionId);
    void SwitchTo(const uint VTNr);
    void SwitchToNext();
    void SwitchToPrevious();
};
DLOGIN_END_NAMESPACE

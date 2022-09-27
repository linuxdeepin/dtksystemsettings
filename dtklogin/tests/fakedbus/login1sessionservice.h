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
struct DBusUserPath;
struct DBusSeat;
typedef DBusSeat DBusSeatPath;
/*
 * Adaptor class for interface org.freedesktop.login1.Session
 */
class Login1SessionService : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.freedesktop.login1.Session")
public:
    Login1SessionService(QObject *parent);

public:  // PROPERTIES
    Q_PROPERTY(bool Active READ active);
    Q_PROPERTY(uint Audit READ audit);
    Q_PROPERTY(QString Class READ sessionClass);
    Q_PROPERTY(QString Desktop READ desktop);
    Q_PROPERTY(QString Display READ display);
    Q_PROPERTY(QString Id READ id);
    Q_PROPERTY(bool IdleHint READ idleHint);
    Q_PROPERTY(quint64 IdleSinceHint READ idleSinceHint);
    Q_PROPERTY(quint64 IdleSinceHintMonotonic READ idleSinceHintMonotonic);
    Q_PROPERTY(quint32 Leader READ leader);
    Q_PROPERTY(bool LockedHint READ lockedHint);
    Q_PROPERTY(QString Name READ name);
    Q_PROPERTY(bool Remote READ remote);
    Q_PROPERTY(QString RemoteHost READ remoteHost);
    Q_PROPERTY(QString RemoteUser READ remoteUser);
    Q_PROPERTY(QString Scope READ scope);
    Q_PROPERTY(DBusSeatPath Seat READ seat);
    Q_PROPERTY(QString Service READ service);
    Q_PROPERTY(QString State READ state);
    Q_PROPERTY(QString TTY READ tTY);
    Q_PROPERTY(quint64 Timestamp READ timestamp);
    Q_PROPERTY(quint64 TimestampMonotonic READ timestampMonotonic);
    Q_PROPERTY(QString Type READ type);
    Q_PROPERTY(DBusUserPath User READ user);
    Q_PROPERTY(quint32 VTNr READ VTNr);

    bool active() const;
    quint32 audit() const;
    QString sessionClass() const;
    QString desktop() const;
    QString display() const;
    QString id() const;
    bool idleHint() const;
    quint64 idleSinceHint() const;
    quint64 idleSinceHintMonotonic() const;
    quint32 leader() const;
    bool lockedHint() const;
    QString name() const;
    bool remote() const;
    QString remoteHost() const;
    QString remoteUser() const;
    QString scope() const;
    DBusSeatPath seat() const;
    QString service() const;
    QString state() const;
    QString tTY() const;
    quint64 timestamp() const;
    quint64 timestampMonotonic() const;
    QString type() const;
    DBusUserPath user() const;
    quint32 VTNr() const;

public Q_SLOTS:  // METHODS
    void Activate();
    void Kill(const QString &who, int signal_number);
    void Lock();
    void SetIdleHint(bool idle);
    void Terminate();
Q_SIGNALS:  // SIGNALS
};

DLOGIN_END_NAMESPACE
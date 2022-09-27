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
 * Adaptor class for interface org.freedesktop.login1.User
 */
class Login1UserService : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.freedesktop.login1.User")
public:
    Login1UserService(QObject *parent);

public:  // PROPERTIES
    Q_PROPERTY(DBusSessionPath Display READ display);
    Q_PROPERTY(quint32 UID READ UID);
    Q_PROPERTY(quint32 GID READ GID);
    Q_PROPERTY(QString Name READ name);
    Q_PROPERTY(QString RuntimePath READ runtimePath);
    Q_PROPERTY(QString Service READ service);
    Q_PROPERTY(QString Slice READ slice);
    Q_PROPERTY(QString State READ state);
    Q_PROPERTY(quint64 Timestamp READ timestamp);
    Q_PROPERTY(quint64 TimestampMonotonic READ timestampMonotonic);

    DBusSessionPath display() const;
    quint32 UID() const;
    quint32 GID() const;
    QString name() const;
    QString runtimePath() const;
    QString service() const;
    QString slice() const;
    QString state() const;
    quint64 timestamp() const;
    quint64 timestampMonotonic() const;

public Q_SLOTS:  // METHODS
    void Kill(const qint32 signalNumber);
    void Terminate();
};

DLOGIN_END_NAMESPACE

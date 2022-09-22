// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "namespace.h"
#include "ddbusinterface.h"
#include <QObject>
#include <QString>
#include <QScopedPointer>
#include <qdbusextratypes.h>
#include <qscopedpointer.h>
#include <qdbuspendingreply.h>

DACCOUNTS_BEGIN_NAMESPACE

class DAccounts : public QObject
{
    Q_OBJECT

public:
    explicit DAccounts(QObject *parent = nullptr);
    virtual ~DAccounts() = default;

    Q_PROPERTY(QString daemonVersion READ daemonVersion)
    QString daemonVersion() const;

public slots:
    QDBusPendingReply<QDBusObjectPath> cacheUser(const QString &name);
    QDBusPendingReply<QDBusObjectPath> createUser(const QString &name, const QString &fullname, const qint32 accountType);
    QDBusPendingReply<void> deleteUser(const qint64 id, const bool removeFiles);
    QDBusPendingReply<QString> findUserById(const qint64 id);
    QDBusPendingReply<QString> findUserByName(const QString &name);
    QDBusPendingReply<QList<QDBusObjectPath>> listCachedUsers();
    QDBusPendingReply<void> uncacheUser(const QString &name);

signals:
    void ReceivedUserAdded(QString path);
    void ReceivedUserDeleted(QString path);

private slots:
    void receiveUserAdded(QDBusObjectPath user);
    void receiveUserDeleted(QDBusObjectPath user);

private:
    QScopedPointer<DDBusInterface> m_inter;
};

DACCOUNTS_END_NAMESPACE

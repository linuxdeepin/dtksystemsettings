// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "namespace.h"
#include "ddbusinterface.h"
#include <QObject>
#include <QString>
#include <QScopedPointer>

DACCOUNTS_BEGIN_NAMESPACE

class DAccounts : public QObject
{
    Q_OBJECT

public:
    explicit DAccounts(QObject *parent = nullptr);
    virtual ~DAccounts();

    Q_PROPERTY(QString DaemonVersion READ daemonVersion)
    QString daemonVersion() const;

public slots:

    QString CacheUser(const QString &name);
    QString CreateUser(const QString &name, const QString &fullname, const qint32 accountType);
    void DeleteUser(const qint64 id, const bool removeFiles);
    QString FindUserById(const qint64 id);
    QString FindUserByName(const QString &name);
    QStringList ListCachedUsers();
    void UncacheUser(const QString &name);
    QString lastError() const;

signals:
    void UserAdded(const QString &path);
    void UserDeleted(const QString &path);
    void errorMessageChanged(const QString &message);

private:
    QString m_errorMessage;
    DDBusInterface *m_inter;
};

DACCOUNTS_END_NAMESPACE

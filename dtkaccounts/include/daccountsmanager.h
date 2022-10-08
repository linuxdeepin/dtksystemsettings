// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "daccountstypes.h"
#include <QSharedPointer>
#include <QStringList>

DACCOUNTS_BEGIN_NAMESPACE

class DAccountsManagerPrivate;
class DAccountsUser;

class DAccountsManager : public QObject
{
    Q_OBJECT

public:
    explicit DAccountsManager(QObject *parent = nullptr);
    virtual ~DAccountsManager();

    Q_PROPERTY(QList<quint64> userList READ userList)

    QList<quint64> userList() const;  // TODO:创建或删除userlist无法及时刷新，调用sleep(1)正常

public slots:

    QSharedPointer<DAccountsUser> createUser(const QString &name, const QString &fullName, const AccountTypes &type);
    void deleteUser(const QString &name, const bool rmFiles);
    QSharedPointer<DAccountsUser> findUserByName(const QString &name);
    QSharedPointer<DAccountsUser> findUserById(const qint64 uid);
    QStringList groups();
    QStringList presetGroups(const AccountTypes &type);
    ValidMsg isPasswordValid(const QString &password);
    ValidMsg isUsernameValid(const QString &name);

signals:
    void UserAdded(const quint64 uid);
    void UserDeleted(const quint64 uid);

private:
    QScopedPointer<DAccountsManagerPrivate> d_ptr;
    Q_DECLARE_PRIVATE(DAccountsManager)
};

DACCOUNTS_END_NAMESPACE

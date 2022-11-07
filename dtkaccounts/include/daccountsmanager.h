// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "daccountstypes.h"
#include <QSharedPointer>
#include <QStringList>
#include <DExpected>

DACCOUNTS_BEGIN_NAMESPACE

DCORE_USE_NAMESPACE

class DAccountsManagerPrivate;
class DAccountsUser;

class DAccountsManager : public QObject
{
    Q_OBJECT

public:
    explicit DAccountsManager(QObject *parent = nullptr);
    virtual ~DAccountsManager();

public slots:
    DExpected<QList<quint64>> userList() const;  // TODO:创建或删除userlist无法及时刷新，调用sleep(1)正常
    DExpected<QSharedPointer<DTK_ACCOUNT_NAMESPACE::DAccountsUser>>
    createUser(const QString &name, const QString &fullName, const DTK_ACCOUNT_NAMESPACE::AccountTypes &type);
    DExpected<void> deleteUser(const QString &name, const bool rmFiles);
    DExpected<QSharedPointer<DTK_ACCOUNT_NAMESPACE::DAccountsUser>> findUserByName(const QString &name);
    DExpected<QSharedPointer<DTK_ACCOUNT_NAMESPACE::DAccountsUser>> findUserById(const qint64 uid);
    DExpected<QStringList> groups();
    DExpected<QStringList> presetGroups(const DTK_ACCOUNT_NAMESPACE::AccountTypes &type);
    DExpected<DTK_ACCOUNT_NAMESPACE::ValidMsg> isPasswordValid(const QString &password);
    DExpected<DTK_ACCOUNT_NAMESPACE::ValidMsg> isUsernameValid(const QString &name);

signals:
    void UserAdded(const quint64 uid);
    void UserDeleted(const quint64 uid);

private:
    QScopedPointer<DAccountsManagerPrivate> d_ptr;
    Q_DECLARE_PRIVATE(DAccountsManager)
};

DACCOUNTS_END_NAMESPACE

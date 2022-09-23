// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dsystemaccountsinterface.h"

DACCOUNTS_BEGIN_NAMESPACE

DSystemAccountsInterface::DSystemAccountsInterface(QObject *parent)
    : QObject(parent)
{
    const QString &Service = QStringLiteral("com.deepin.daemon.Accounts");
    const QString &Path = QStringLiteral("/com/deepin/daemon/Accounts");
    const QString &Interface = QStringLiteral("com.deepin.daemon.Accounts");
    m_inter.reset(new DDBusInterface(Service, Path, Interface, QDBusConnection::systemBus(), this));
    QDBusConnection::systemBus().connect(Service, Path, Interface, "UserAdded", this, "receiveUserAdded");
    QDBusConnection::systemBus().connect(Service, Path, Interface, "UserDeleted", this, "receiveUserDeleted");
};

QDBusPendingReply<QDBusObjectPath>
DSystemAccountsInterface::createUser(const QString &name, const QString &fullName, qint32 accountType)
{
    return m_inter->asyncCallWithArgumentList(
        "CreateUser", {QVariant::fromValue(name), QVariant::fromValue(fullName), QVariant::fromValue(accountType)});
}

QDBusPendingReply<void> DSystemAccountsInterface::deleteUser(const QString &name, bool rmFiles)
{
    return m_inter->asyncCallWithArgumentList("DeleteUser", {QVariant::fromValue(name), QVariant::fromValue(rmFiles)});
}

QDBusPendingReply<QStringList> DSystemAccountsInterface::getPresetGroups(qint32 accountType)
{
    return m_inter->asyncCallWithArgumentList("GetPresetGroups", {QVariant::fromValue(accountType)});
}

QDBusPendingReply<bool, QString, qint32> DSystemAccountsInterface::isPasswordValid(const QString &password)
{
    return m_inter->asyncCallWithArgumentList("IsPasswordValid", {QVariant::fromValue(password)});
}

QDBusPendingReply<bool, QString, qint32> DSystemAccountsInterface::isUsernameValid(const QString &username)
{
    return m_inter->asyncCallWithArgumentList("IsUsernameValid", {QVariant::fromValue(username)});
}

void DSystemAccountsInterface::receiveUserAdded(QString user)
{
    emit ReceivedUserAdded(std::move(user));
}

void DSystemAccountsInterface::receiveUserDeleted(QString user)
{
    emit ReceivedUserDeleted(std::move(user));
}

DACCOUNTS_END_NAMESPACE

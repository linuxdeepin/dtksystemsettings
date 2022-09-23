// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "systemaccountsinterface.h"

DACCOUNTS_BEGIN_NAMESPACE

DSystemAccountsInterface::DSystemAccountsInterface(QObject *parent)
    : QObject(parent)
{
    const QString &Service = QStringLiteral("com.deepin.daemon.Accounts");
    const QString &Path = QStringLiteral("/com/deepin/daemon/Accounts");
    const QString &Interface = QStringLiteral("com.deepin.daemon.Accounts");
    m_inter.reset(new DDBusInterface(Service, Path, Interface, QDBusConnection::systemBus(), this));
};

QDBusPendingReply<QDBusObjectPath>
DSystemAccountsInterface::createUser(const QString &name, const QString fullName, qint32 accountType)
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

DACCOUNTS_END_NAMESPACE

// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "accountsinterface.h"
#include "ddbusinterface.h"
#include <QVariant>
#include <qdbusconnection.h>

DACCOUNTS_BEGIN_NAMESPACE

DAccounts::DAccounts(QObject *parent)
    : QObject(parent)
{
    const QString &Service = QStringLiteral("org.freedesktop.Accounts");
    const QString &Path = QStringLiteral("/org/freedesktop/Accounts");
    const QString &Interface = QStringLiteral("org.freedesktop.Accounts");
    m_inter.reset(new DDBusInterface(Service, Path, Interface, QDBusConnection::systemBus(), this));
    QDBusConnection::systemBus().connect(Service, Path, Interface, "UserAdded", this, "receiveUserAdded");
    QDBusConnection::systemBus().connect(Service, Path, Interface, "UserDeleted", this, "receiveUserDeleted");
}

QString DAccounts::daemonVersion() const
{
    return qdbus_cast<QString>(m_inter->property("DaemonVersion"));
}

QDBusPendingReply<QDBusObjectPath> DAccounts::cacheUser(const QString &name)
{
    QVariantList args{QVariant::fromValue(name)};
    return m_inter->asyncCallWithArgumentList("CacheUser", args);
}

QDBusPendingReply<QDBusObjectPath> DAccounts::createUser(const QString &name, const QString &fullname, const qint32 accountType)
{
    QVariantList args{QVariant::fromValue(name), QVariant::fromValue(fullname), QVariant::fromValue(accountType)};
    return m_inter->asyncCallWithArgumentList("CreateUser", args);
}

QDBusPendingReply<void> DAccounts::deleteUser(const qint64 id, const bool removeFiles)
{
    QVariantList args{QVariant::fromValue(id), QVariant::fromValue(removeFiles)};
    auto userPath = findUserById(id);
    return m_inter->asyncCallWithArgumentList("DeleteUser", args);
}

QDBusPendingReply<QString> DAccounts::findUserById(const qint64 id)
{
    QVariantList args{QVariant::fromValue(id)};
    return m_inter->asyncCallWithArgumentList("FindUserById", args);
}

QDBusPendingReply<QString> DAccounts::findUserByName(const QString &name)
{
    QVariantList args{QVariant::fromValue(name)};
    return m_inter->asyncCallWithArgumentList("FindUserByName", args);
}

QDBusPendingReply<QList<QDBusObjectPath>> DAccounts::listCachedUsers()
{
    return m_inter->asyncCall("ListCachedUsers");
}

QDBusPendingReply<void> DAccounts::uncacheUser(const QString &name)
{
    QVariantList args{QVariant::fromValue(name)};
    return m_inter->asyncCallWithArgumentList("UncacheUser", args);
}

void DAccounts::receiveUserAdded(QDBusObjectPath user)
{
    emit ReceivedUserAdded(user.path().toUtf8());
}

void DAccounts::receiveUserDeleted(QDBusObjectPath user)
{
    emit ReceivedUserDeleted(user.path().toUtf8());
}

DACCOUNTS_END_NAMESPACE

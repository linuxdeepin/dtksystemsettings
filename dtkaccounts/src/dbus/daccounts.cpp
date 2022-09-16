// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "daccounts.h"
#include "ddbusinterface.h"
#include <QVariant>
#include <qdbusconnection.h>
#include <qdbuspendingreply.h>

DACCOUNTS_BEGIN_NAMESPACE

DAccounts::DAccounts(QObject *parent): QObject(parent)
{
    const QString &Service = QStringLiteral("org.freedesktop.Accounts");
    const QString &Path = QStringLiteral("/org/freedesktop/Accounts");
    const QString &Interface = QStringLiteral("org.freedesktop.Accounts");
    m_inter = new DDBusInterface(Service, Path, Interface, QDBusConnection::systemBus(), this);
}

DAccounts::~DAccounts(){
    delete m_inter;
}

QString DAccounts::daemonVersion() const
{
    return qdbus_cast<QString>(m_inter->property("DaemonVersion"));
}

// public slots
QString DAccounts::lastError() const
{
    return m_errorMessage;
}

QString DAccounts::CacheUser(const QString &name)
{
    QVariantList args{QVariant::fromValue(name)};
    QDBusPendingReply<QDBusObjectPath> replay = m_inter->asyncCallWithArgumentList("CacheUser", args);
    replay.waitForFinished();
    if (!replay.isValid()) {
        m_errorMessage = replay.error().message();
        emit errorMessageChanged(m_errorMessage);
    }
    return replay.value().path();
}

QString DAccounts::CreateUser(const QString &name, const QString &fullname, const int32_t accountType)
{
    QVariantList args{QVariant::fromValue(name), QVariant::fromValue(fullname), QVariant::fromValue(accountType)};
    QDBusPendingReply<QDBusObjectPath> replay = m_inter->asyncCallWithArgumentList("CreateUser", args);
    replay.waitForFinished();
    if (!replay.isValid()) {
        m_errorMessage = replay.error().message();
        emit errorMessageChanged(m_errorMessage);
    }
    auto userPath = replay.value().path();
    emit UserAdded(userPath);
    return userPath;
}

void DAccounts::DeleteUser(const qint64 id, const bool removeFiles)
{
    QVariantList args{QVariant::fromValue(id), QVariant::fromValue(removeFiles)};
    auto userPath = FindUserById(id);
    QDBusPendingReply<> replay = m_inter->asyncCallWithArgumentList("DeleteUser", args);
    replay.waitForFinished();
    if (!replay.isValid()) {
        m_errorMessage = replay.error().message();
        emit errorMessageChanged(m_errorMessage);
    }
    emit UserDeleted(userPath);
}

QString DAccounts::FindUserById(const qint64 id)
{
    QVariantList args{QVariant::fromValue(id)};
    QDBusPendingReply<QDBusObjectPath> replay = m_inter->asyncCallWithArgumentList("FindUserById", args);
    replay.waitForFinished();
    if (!replay.isValid()) {
        m_errorMessage = replay.error().message();
        emit errorMessageChanged(m_errorMessage);
    }
    return replay.value().path();
}

QString DAccounts::FindUserByName(const QString &name)
{
    QVariantList args{QVariant::fromValue(name)};
    QDBusPendingReply<QDBusObjectPath> replay = m_inter->asyncCallWithArgumentList("FindUserByName", args);
    replay.waitForFinished();
    if (!replay.isValid()) {
        m_errorMessage = replay.error().message();
        emit errorMessageChanged(m_errorMessage);
    }
    return replay.value().path();
}

QStringList DAccounts::ListCachedUsers()
{
    QDBusPendingReply<QList<QDBusObjectPath>> replay = m_inter->asyncCall("ListCachedUsers");
    replay.waitForFinished();
    if (!replay.isValid()) {
        m_errorMessage = replay.error().message();
        emit errorMessageChanged(m_errorMessage);
    }
    QStringList ret;
    for (const auto &path : replay.value()) {
        ret.push_back(path.path());
    }
    return ret;
}

void DAccounts::UncacheUser(const QString &name)
{
    QVariantList args{QVariant::fromValue(name)};
    QDBusPendingReply<> replay = m_inter->asyncCallWithArgumentList("UncacheUser", args);
    replay.waitForFinished();
    if (!replay.isValid()) {
        m_errorMessage = replay.error().message();
        emit errorMessageChanged(m_errorMessage);
    }
}

DACCOUNTS_END_NAMESPACE

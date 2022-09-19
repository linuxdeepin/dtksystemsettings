// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dloginuser.h"

#include "ddbusinterface.h"
#include "dlogintypes.h"
#include "dlogintypes_p.h"
#include "dloginuser_p.h"
#include <qdbuspendingreply.h>
#include <qlist.h>
#include <qobject.h>

DLOGIN_BEGIN_NAMESPACE
DLoginUser::DLoginUser(const QString &path, QObject *parent)
    : QObject(parent)
    , d_ptr(new DLoginUserPrivate(this))
{
    const QString &Service = QStringLiteral("org.freedesktop.login1");
    const QString &Interface = QStringLiteral("org.freedesktop.login1.User");

    SessionPath_p::registerMetaType();

    Q_D(DLoginUser);
    d->m_inter = new DDBusInterface(Service, path, Interface, QDBusConnection::systemBus(), this);
}

DLoginUser::~DLoginUser() {}

QList<SessionPath> DLoginUser::sessions() const
{
    Q_D(const DLoginUser);
    const auto &result = qdbus_cast<QList<SessionPath_p>>(d->m_inter->property("Sessions"));
    QList<SessionPath> sessions;
    for (auto && session_p : result) {
        SessionPath session;
        session.sessionId = session_p.sessionId;
        session.path =session_p.path.path();
        sessions.append(session);
    }
    return sessions;
}

bool DLoginUser::idleHint() const
{
    Q_D(const DLoginUser);
    return qdbus_cast<bool>(d->m_inter->property("IdleHint"));
}

bool DLoginUser::linger() const
{
    Q_D(const DLoginUser);
    return qdbus_cast<bool>(d->m_inter->property("Linger"));
}

QString DLoginUser::name() const
{
    Q_D(const DLoginUser);
    return qdbus_cast<QString>(d->m_inter->property("Name"));
}

QString DLoginUser::runtimePath() const
{
    Q_D(const DLoginUser);
    return qdbus_cast<QString>(d->m_inter->property("RuntimePath"));
}

QString DLoginUser::service() const
{
    Q_D(const DLoginUser);
    return qdbus_cast<QString>(d->m_inter->property("Service"));
}

QString DLoginUser::slice() const
{
    Q_D(const DLoginUser);
    return qdbus_cast<QString>(d->m_inter->property("Slice"));
}

QString DLoginUser::state() const
{
    Q_D(const DLoginUser);
    return qdbus_cast<QString>(d->m_inter->property("State"));
}

SessionPath DLoginUser::display() const
{
    Q_D(const DLoginUser);
    const auto &result = qdbus_cast<SessionPath_p>(d->m_inter->property("Display"));
    SessionPath session;
    session.path = result.path.path();
    session.sessionId = result.sessionId;
    return session;
}

uint DLoginUser::GID() const
{
    Q_D(const DLoginUser);
    return qdbus_cast<uint>(d->m_inter->property("GID"));
}

uint DLoginUser::UID() const
{
    Q_D(const DLoginUser);
    return qdbus_cast<uint>(d->m_inter->property("UID"));
}

quint64 DLoginUser::idleSinceHint() const
{
    Q_D(const DLoginUser);
    return qdbus_cast<quint64>(d->m_inter->property("IdleSinceHint"));
}

quint64 DLoginUser::idleSinceHintMonotonic() const
{
    Q_D(const DLoginUser);
    return qdbus_cast<quint64>(d->m_inter->property("IdleSinceHintMonotonic"));
}

quint64 DLoginUser::timestamp() const
{
    Q_D(const DLoginUser);
    return qdbus_cast<quint64>(d->m_inter->property("Timestamp"));
}

quint64 DLoginUser::timestampMonotonic() const
{
    Q_D(const DLoginUser);
    return qdbus_cast<quint64>(d->m_inter->property("TimestampMonotonic"));
}

// public slots

QString DLoginUser::lastError() const
{
    Q_D(const DLoginUser);
    return d->m_errorMessage;
}

void DLoginUser::kill(const int signalNumber)
{
    Q_D(DLoginUser);
    QVariantList args {QVariant::fromValue(signalNumber)};
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList("Kill", args);
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLoginUser::terminate()
{
    Q_D(DLoginUser);
    QDBusPendingReply<> reply = d->m_inter->asyncCall("Terminate");
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

DLOGIN_END_NAMESPACE

// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dlogin1user.h"

#include "ddbusinterface.h"
#include "dlogin1types.h"
#include "dlogin1types_p.h"
#include "dlogin1user_p.h"
#include <qlist.h>
#include <qobject.h>
#include <qdbuspendingreply.h>

DLOGIN1_BEGIN_NAMESPACE
DLogin1User::DLogin1User(const QString &path, QObject *parent)
    : QObject(parent)
    , d_ptr(new DLogin1UserPrivate(this))
{
    const QString &Service = QStringLiteral("org.freedesktop.login1");
    const QString &Interface = QStringLiteral("org.freedesktop.login1.User");

    SessionPath_p::registerMetaType();

    Q_D(DLogin1User);
    d->m_inter = new DDBusInterface(Service, path, Interface, QDBusConnection::systemBus(), this);
}

DLogin1User::~DLogin1User() {}

QList<SessionPath> DLogin1User::sessions() const
{
    Q_D(const DLogin1User);
    const auto &result = qdbus_cast<QList<SessionPath_p>>(d->m_inter->property("Sessions"));
    QList<SessionPath> sessions;
    for (auto && session_p : result) {
        SessionPath session;
        session.session_id = session_p.session_id;
        session.path =session_p.path.path();
        sessions.append(session);
    }
    return sessions;
}

bool DLogin1User::idleHint() const
{
    Q_D(const DLogin1User);
    return qdbus_cast<bool>(d->m_inter->property("IdleHint"));
}

bool DLogin1User::linger() const
{
    Q_D(const DLogin1User);
    return qdbus_cast<bool>(d->m_inter->property("Linger"));
}

QString DLogin1User::name() const
{
    Q_D(const DLogin1User);
    return qdbus_cast<QString>(d->m_inter->property("Name"));
}

QString DLogin1User::runtimePath() const
{
    Q_D(const DLogin1User);
    return qdbus_cast<QString>(d->m_inter->property("RuntimePath"));
}

QString DLogin1User::service() const
{
    Q_D(const DLogin1User);
    return qdbus_cast<QString>(d->m_inter->property("Service"));
}

QString DLogin1User::slice() const
{
    Q_D(const DLogin1User);
    return qdbus_cast<QString>(d->m_inter->property("Slice"));
}

QString DLogin1User::state() const
{
    Q_D(const DLogin1User);
    return qdbus_cast<QString>(d->m_inter->property("State"));
}

SessionPath DLogin1User::display() const
{
    Q_D(const DLogin1User);
    const auto &result = qdbus_cast<SessionPath_p>(d->m_inter->property("Display"));
    SessionPath session;
    session.path = result.path.path();
    session.session_id = result.session_id;
    return session;
}

uint DLogin1User::GID() const
{
    Q_D(const DLogin1User);
    return qdbus_cast<uint>(d->m_inter->property("GID"));
}

uint DLogin1User::UID() const
{
    Q_D(const DLogin1User);
    return qdbus_cast<uint>(d->m_inter->property("UID"));
}

quint64 DLogin1User::idleSinceHint() const
{
    Q_D(const DLogin1User);
    return qdbus_cast<quint64>(d->m_inter->property("IdleSinceHint"));
}

quint64 DLogin1User::idleSinceHintMonotonic() const
{
    Q_D(const DLogin1User);
    return qdbus_cast<quint64>(d->m_inter->property("IdleSinceHintMonotonic"));
}

quint64 DLogin1User::timestamp() const
{
    Q_D(const DLogin1User);
    return qdbus_cast<quint64>(d->m_inter->property("Timestamp"));
}

quint64 DLogin1User::timestampMonotonic() const
{
    Q_D(const DLogin1User);
    return qdbus_cast<quint64>(d->m_inter->property("TimestampMonotonic"));
}

// public slots

QString DLogin1User::lastError() const
{
    Q_D(const DLogin1User);
    return d->m_errorMessage;
}

void DLogin1User::kill(const int signal_number)
{
    Q_D(DLogin1User);
    QVariantList args {QVariant::fromValue(signal_number)};
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList("Kill", args);
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLogin1User::terminate()
{
    Q_D(DLogin1User);
    QDBusPendingReply<> reply = d->m_inter->asyncCall("Terminate");
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

DLOGIN1_END_NAMESPACE

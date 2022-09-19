// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dloginseat.h"

#include "ddbusinterface.h"
#include "dloginseat_p.h"
#include "dlogintypes.h"
#include "dlogintypes_p.h"
#include <qdbuspendingreply.h>
#include <qlist.h>
#include <qobject.h>

DLOGIN_BEGIN_NAMESPACE
DLoginSeat::DLoginSeat(const QString &path, QObject *parent)
    : QObject(parent)
    , d_ptr(new DLoginSeatPrivate(this))
{
    const QString &Service = QStringLiteral("org.freedesktop.login1");
    const QString &Interface = QStringLiteral("org.freedesktop.login1.Seat");

    SessionPath_p::registerMetaType();
    Q_D(DLoginSeat);
    d->m_inter = new DDBusInterface(Service, path, Interface, QDBusConnection::systemBus(), this);
}

QList<SessionPath> DLoginSeat::sessions() const
{
    Q_D(const DLoginSeat);
    const auto &result = qdbus_cast<QList<SessionPath_p>>(d->m_inter->property("Sessions"));
    QList<SessionPath> sessionPaths;
    for (auto sessionPath_p : result) {
        SessionPath sessionPath;
        sessionPath.path = sessionPath_p.path.path();
        sessionPath.session_id =sessionPath_p.session_id;
        sessionPaths.append(sessionPath);
    }
    return sessionPaths;
}

bool DLoginSeat::canGraphical() const
{
    Q_D(const DLoginSeat);
    return qdbus_cast<bool>(d->m_inter->property("CanGraphical"));
}

bool DLoginSeat::canTTY() const
{
    Q_D(const DLoginSeat);
    return qdbus_cast<bool>(d->m_inter->property("CanTTY"));
}

bool DLoginSeat::idleHint() const
{
    Q_D(const DLoginSeat);
    return qdbus_cast<bool>(d->m_inter->property("IdleHint"));
}

QString DLoginSeat::id() const
{
    Q_D(const DLoginSeat);
    return qdbus_cast<QString>(d->m_inter->property("Id"));
}

QString DLoginSeat::lastError() const
{
    Q_D(const DLoginSeat);
    return d->m_errorMessage;
}

SessionPath DLoginSeat::activeSession() const
{
    Q_D(const DLoginSeat);
    const auto & result = qdbus_cast<SessionPath_p>(d->m_inter->property("ActiveSession"));
    SessionPath path;
    path.path = result.path.path();
    path.session_id = result.session_id;
    return path;
}

quint64 DLoginSeat::idleSinceHint() const
{
    Q_D(const DLoginSeat);
    return qdbus_cast<quint64>(d->m_inter->property("IdleSinceHint"));
}

quint64 DLoginSeat::idleSinceHintMonotonic() const
{
    Q_D(const DLoginSeat);
    return qdbus_cast<quint64>(d->m_inter->property("IdleSinceHintMonotonic"));
}

void DLoginSeat::activateSession(const QString &session_id)
{
    Q_D(DLoginSeat);
    QVariantList args {QVariant::fromValue(session_id)};
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList("ActivateSession", args);
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLoginSeat::switchTo(const uint vtnr)
{
    Q_D(DLoginSeat);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("SwitchTo"),
        {QVariant::fromValue(vtnr)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLoginSeat::switchToNext()
{
    Q_D(DLoginSeat);
    QDBusPendingReply<> reply = d->m_inter->asyncCall(QStringLiteral("SwitchToNext"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLoginSeat::switchToPrevious()
{
    Q_D(DLoginSeat);
    QDBusPendingReply<> reply = d->m_inter->asyncCall(QStringLiteral("SwitchToPrevious"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLoginSeat::terminate()
{
    Q_D(DLoginSeat);
    QDBusPendingReply<> reply = d->m_inter->asyncCall(QStringLiteral("Terminate"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

DLoginSeat::~DLoginSeat() {}
DLOGIN_END_NAMESPACE

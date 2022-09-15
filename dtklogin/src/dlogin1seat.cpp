// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dlogin1seat.h"

#include "ddbusinterface.h"
#include "dlogin1seat_p.h"
#include "dlogin1types.h"
#include "dlogin1types_p.h"
#include <qlist.h>
#include <qobject.h>
#include <qdbuspendingreply.h>

DLOGIN1_BEGIN_NAMESPACE
DLogin1Seat::DLogin1Seat(const QString &path, QObject *parent)
    : QObject(parent)
    , d_ptr(new DLogin1SeatPrivate(this))
{
    const QString &Service = QStringLiteral("org.freedesktop.login1");
    const QString &Interface = QStringLiteral("org.freedesktop.login1.Seat");

    SessionPath_p::registerMetaType();
    Q_D(DLogin1Seat);
    d->m_inter = new DDBusInterface(Service, path, Interface, QDBusConnection::systemBus(), this);
}

QList<SessionPath> DLogin1Seat::sessions() const
{
    Q_D(const DLogin1Seat);
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

bool DLogin1Seat::canGraphical() const
{
    Q_D(const DLogin1Seat);
    return qdbus_cast<bool>(d->m_inter->property("CanGraphical"));
}

bool DLogin1Seat::canTTY() const
{
    Q_D(const DLogin1Seat);
    return qdbus_cast<bool>(d->m_inter->property("CanTTY"));
}

bool DLogin1Seat::idleHint() const
{
    Q_D(const DLogin1Seat);
    return qdbus_cast<bool>(d->m_inter->property("IdleHint"));
}

QString DLogin1Seat::id() const
{
    Q_D(const DLogin1Seat);
    return qdbus_cast<QString>(d->m_inter->property("Id"));
}

QString DLogin1Seat::lastError() const
{
    Q_D(const DLogin1Seat);
    return d->m_errorMessage;
}

SessionPath DLogin1Seat::activeSession() const
{
    Q_D(const DLogin1Seat);
    const auto & result = qdbus_cast<SessionPath_p>(d->m_inter->property("ActiveSession"));
    SessionPath path;
    path.path = result.path.path();
    path.session_id = result.session_id;
    return path;
}

quint64 DLogin1Seat::idleSinceHint() const
{
    Q_D(const DLogin1Seat);
    return qdbus_cast<quint64>(d->m_inter->property("IdleSinceHint"));
}

quint64 DLogin1Seat::idleSinceHintMonotonic() const
{
    Q_D(const DLogin1Seat);
    return qdbus_cast<quint64>(d->m_inter->property("IdleSinceHintMonotonic"));
}

void DLogin1Seat::activateSession(const QString &session_id)
{
    Q_D(DLogin1Seat);
    QVariantList args {QVariant::fromValue(session_id)};
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList("ActivateSession", args);
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLogin1Seat::switchTo(const uint vtnr)
{
    Q_D(DLogin1Seat);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("SwitchTo"),
        {QVariant::fromValue(vtnr)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLogin1Seat::switchToNext()
{
    Q_D(DLogin1Seat);
    QDBusPendingReply<> reply = d->m_inter->asyncCall(QStringLiteral("SwitchToNext"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLogin1Seat::switchToPrevious()
{
    Q_D(DLogin1Seat);
    QDBusPendingReply<> reply = d->m_inter->asyncCall(QStringLiteral("SwitchToPrevious"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLogin1Seat::terminate()
{
    Q_D(DLogin1Seat);
    QDBusPendingReply<> reply = d->m_inter->asyncCall(QStringLiteral("Terminate"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

DLogin1Seat::~DLogin1Seat() {}
DLOGIN1_END_NAMESPACE

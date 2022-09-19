// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dloginsession.h"

#include "ddbusinterface.h"
#include "dloginsession_p.h"
#include "dlogintypes_p.h"
#include <QDBusError>
#include <qdbuspendingreply.h>
#include <qdbusunixfiledescriptor.h>
#include <qobject.h>
#include <qvariant.h>
DLOGIN_BEGIN_NAMESPACE

DLoginSession::DLoginSession(const QString &path, QObject *parent)
    : QObject(parent)
    , d_ptr(new DLoginSessionPrivate(this))
{
    const QString &Service = QStringLiteral("org.freedesktop.login1");
    const QString &Interface = QStringLiteral("org.freedesktop.login1.Session");

    Q_D(DLoginSession);
    SeatPath_p::registerMetaType();
    UserPath_p::registerMetaType();
    d->m_inter = new DDBusInterface(Service, path, Interface, QDBusConnection::systemBus(), this);
}

DLoginSession::~DLoginSession(){};

bool DLoginSession::active() const
{
    Q_D(const DLoginSession);
    return qvariant_cast<bool>(d->m_inter->property("Active"));
}

bool DLoginSession::idleHint() const
{
    Q_D(const DLoginSession);
    return qvariant_cast<bool>(d->m_inter->property("IdleHint"));
}

bool DLoginSession::lockedHint() const
{
    Q_D(const DLoginSession);
    return qvariant_cast<bool>(d->m_inter->property("LockedHint"));
}

bool DLoginSession::remote() const
{
    Q_D(const DLoginSession);
    return qvariant_cast<bool>(d->m_inter->property("Remote"));
}
QString DLoginSession::_class() const
{
    Q_D(const DLoginSession);
    return qvariant_cast<QString>(d->m_inter->property("Class"));
}
QString DLoginSession::desktop() const
{
    Q_D(const DLoginSession);
    return qvariant_cast<QString>(d->m_inter->property("Desktop"));
}
QString DLoginSession::display() const
{
    Q_D(const DLoginSession);
    return qvariant_cast<QString>(d->m_inter->property("Display"));
}
QString DLoginSession::id() const
{
    Q_D(const DLoginSession);
    return qvariant_cast<QString>(d->m_inter->property("Id"));
}
QString DLoginSession::name() const
{
    Q_D(const DLoginSession);
    return qvariant_cast<QString>(d->m_inter->property("Name"));
}

QString DLoginSession::remoteHost() const
{
    Q_D(const DLoginSession);
    return qvariant_cast<QString>(d->m_inter->property("RemoteHost"));
}
QString DLoginSession::remoteUser() const
{
    Q_D(const DLoginSession);
    return qvariant_cast<QString>(d->m_inter->property("RemoteUser"));
}

QString DLoginSession::scope() const
{
    Q_D(const DLoginSession);
    return qvariant_cast<QString>(d->m_inter->property("Scope"));
}

QString DLoginSession::service() const
{
    Q_D(const DLoginSession);
    return qvariant_cast<QString>(d->m_inter->property("Service"));
}

QString DLoginSession::state() const
{
    Q_D(const DLoginSession);
    return qvariant_cast<QString>(d->m_inter->property("State"));
}

QString DLoginSession::TTY() const
{
    Q_D(const DLoginSession);
    return qvariant_cast<QString>(d->m_inter->property("TTY"));
}

QString DLoginSession::type() const
{
    Q_D(const DLoginSession);
    return qvariant_cast<QString>(d->m_inter->property("Type"));
}

SeatPath DLoginSession::seat() const
{
    Q_D(const DLoginSession);
    const auto &result = qvariant_cast<SeatPath_p>(d->m_inter->property("Seat"));
    SeatPath seatPath;
    seatPath.path = result.path.path();
    seatPath.seatId = result.seatId;
    return seatPath;
}
UserPath DLoginSession::user() const
{
    Q_D(const DLoginSession);
    const auto &result = qvariant_cast<UserPath_p>(d->m_inter->property("User"));
    UserPath userPath;
    userPath.path = result.path.path();
    userPath.userId = result.userId;
    return userPath;
}

uint DLoginSession::audit() const
{
    Q_D(const DLoginSession);
    return qvariant_cast<uint>(d->m_inter->property("Audit"));
}

uint DLoginSession::leader() const
{
    Q_D(const DLoginSession);
    return qvariant_cast<uint>(d->m_inter->property("Leader"));
}
uint DLoginSession::VTNr() const
{
    Q_D(const DLoginSession);
    return qvariant_cast<uint>(d->m_inter->property("VTNr"));
}

quint64 DLoginSession::idleSinceHint() const
{
    Q_D(const DLoginSession);
    return qvariant_cast<quint64>(d->m_inter->property("IdleSinceHint"));
}

quint64 DLoginSession::idleSinceHintMonotonic() const
{
    Q_D(const DLoginSession);
    return qvariant_cast<quint64>(d->m_inter->property("IdleSinceHintMonotonic"));
}

quint64 DLoginSession::timestamp() const
{
    Q_D(const DLoginSession);
    return qvariant_cast<quint64>(d->m_inter->property("Timestamp"));
}
quint64 DLoginSession::timestampMonotonic() const
{
    Q_D(const DLoginSession);
    return qvariant_cast<quint64>(d->m_inter->property("TimestampMonotonic"));
}

QString DLoginSession::lastError() const
{
    Q_D(const DLoginSession);
    return d->m_errorMessage;
}

void DLoginSession::activate()
{
    Q_D(DLoginSession);
    QDBusPendingReply<> reply = d->m_inter->asyncCall(QStringLiteral("Activate"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLoginSession::kill(const QString who, const uint signalNumber)
{
    Q_D(DLoginSession);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("Kill"),
                                                                       {
                                                                           QVariant::fromValue(who),
                                                                           QVariant::fromValue(signalNumber),
                                                                       });
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}
void DLoginSession::lock()
{
    Q_D(DLoginSession);
    QDBusPendingReply<> reply = d->m_inter->asyncCall(QStringLiteral("locked"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}
void DLoginSession::pauseDeviceComplete(const uint major, const uint minor)
{
    Q_D(DLoginSession);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("pauseDeviceComplete"),
                                                                       {
                                                                           QVariant::fromValue(major),
                                                                           QVariant::fromValue(minor),
                                                                       });
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}
void DLoginSession::releaseControl()
{
    Q_D(DLoginSession);
    QDBusPendingReply<> reply = d->m_inter->asyncCall(QStringLiteral("ReleaseControl"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}
void DLoginSession::releaseDevice(const uint major, const uint minor)
{
    Q_D(DLoginSession);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("ReleaseDevice"),
                                                                       {
                                                                           QVariant::fromValue(major),
                                                                           QVariant::fromValue(minor),
                                                                       });
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLoginSession::setBrightness(const QString &subsystem, const QString &name, const uint brightness)
{
    Q_D(DLoginSession);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("SetBrightness"),
                                                                       {
                                                                           QVariant::fromValue(subsystem),
                                                                           QVariant::fromValue(name),
                                                                           QVariant::fromValue(brightness),
                                                                       });
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLoginSession::setIdleHint(const bool idle)
{
    Q_D(DLoginSession);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("SetIdleHint"),
                                                                       {
                                                                           QVariant::fromValue(idle),
                                                                       });
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}
void DLoginSession::setLockedHint(const bool locked)
{
    Q_D(DLoginSession);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("SetLockedHint"),
                                                                       {
                                                                           QVariant::fromValue(locked),
                                                                       });
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLoginSession::setType(const QString &type)
{
    Q_D(DLoginSession);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("SetType"),
                                                                       {
                                                                           QVariant::fromValue(type),
                                                                       });
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLoginSession::takeControl(const bool force)
{
    Q_D(DLoginSession);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("TakeControl"),
                                                                       {
                                                                           QVariant::fromValue(force),
                                                                       });
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

std::tuple<int,  // fd
           bool  // inactive
           >
DLoginSession::takeDevice(uint major, uint minor)
{
    Q_D(DLoginSession);
    QDBusPendingReply<QDBusUnixFileDescriptor, bool> reply = d->m_inter->asyncCallWithArgumentList(
        QStringLiteral("TakeDevice"), {QVariant::fromValue(major), QVariant::fromValue(minor)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return std::tuple<int, bool>();
    }
    return std::make_tuple<int, bool>(reply.argumentAt<0>().fileDescriptor(), reply.argumentAt<1>());
}
void DLoginSession::terminate()
{
    Q_D(DLoginSession);
    QDBusPendingReply<> reply = d->m_inter->asyncCall(QStringLiteral("Terminate"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}
void DLoginSession::unlock()
{
    Q_D(DLoginSession);
    QDBusPendingReply<> reply = d->m_inter->asyncCall(QStringLiteral("unlocked"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}
DLOGIN_END_NAMESPACE

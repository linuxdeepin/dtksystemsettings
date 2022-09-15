// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dlogin1session.h"

#include "ddbusinterface.h"
#include "dlogin1session_p.h"
#include "dlogin1types_p.h"
#include <QDBusError>
#include <qdbuspendingreply.h>
#include <qdbusunixfiledescriptor.h>
#include <qobject.h>
#include <qvariant.h>
DLOGIN1_BEGIN_NAMESPACE

DLogin1Session::DLogin1Session(const QString &path, QObject *parent)
    : QObject(parent)
    , d_ptr(new DLogin1SessionPrivate(this))
{
    const QString &Service = QStringLiteral("org.freedesktop.login1");
    const QString &Interface = QStringLiteral("org.freedesktop.login1.Session");

    Q_D(DLogin1Session);
    SeatPath_p::registerMetaType();
    UserPath_p::registerMetaType();
    d->m_inter = new DDBusInterface(Service, path, Interface, QDBusConnection::systemBus(), this);
}

DLogin1Session::~DLogin1Session(){};

bool DLogin1Session::active() const
{
    Q_D(const DLogin1Session);
    return qvariant_cast<bool>(d->m_inter->property("Active"));
}

bool DLogin1Session::idleHint() const
{
    Q_D(const DLogin1Session);
    return qvariant_cast<bool>(d->m_inter->property("IdleHint"));
}

bool DLogin1Session::lockedHint() const
{
    Q_D(const DLogin1Session);
    return qvariant_cast<bool>(d->m_inter->property("LockedHint"));
}

bool DLogin1Session::remote() const
{
    Q_D(const DLogin1Session);
    return qvariant_cast<bool>(d->m_inter->property("Remote"));
}
QString DLogin1Session::_class() const
{
    Q_D(const DLogin1Session);
    return qvariant_cast<QString>(d->m_inter->property("Class"));
}
QString DLogin1Session::desktop() const
{
    Q_D(const DLogin1Session);
    return qvariant_cast<QString>(d->m_inter->property("Desktop"));
}
QString DLogin1Session::display() const
{
    Q_D(const DLogin1Session);
    return qvariant_cast<QString>(d->m_inter->property("Display"));
}
QString DLogin1Session::id() const
{
    Q_D(const DLogin1Session);
    return qvariant_cast<QString>(d->m_inter->property("Id"));
}
QString DLogin1Session::name() const
{
    Q_D(const DLogin1Session);
    return qvariant_cast<QString>(d->m_inter->property("Name"));
}

QString DLogin1Session::remoteHost() const
{
    Q_D(const DLogin1Session);
    return qvariant_cast<QString>(d->m_inter->property("RemoteHost"));
}
QString DLogin1Session::remoteUser() const
{
    Q_D(const DLogin1Session);
    return qvariant_cast<QString>(d->m_inter->property("RemoteUser"));
}

QString DLogin1Session::scope() const
{
    Q_D(const DLogin1Session);
    return qvariant_cast<QString>(d->m_inter->property("Scope"));
}

QString DLogin1Session::service() const
{
    Q_D(const DLogin1Session);
    return qvariant_cast<QString>(d->m_inter->property("Service"));
}

QString DLogin1Session::state() const
{
    Q_D(const DLogin1Session);
    return qvariant_cast<QString>(d->m_inter->property("State"));
}

QString DLogin1Session::tty() const
{
    Q_D(const DLogin1Session);
    return qvariant_cast<QString>(d->m_inter->property("TTY"));
}

QString DLogin1Session::type() const
{
    Q_D(const DLogin1Session);
    return qvariant_cast<QString>(d->m_inter->property("Type"));
}

SeatPath DLogin1Session::seat() const
{
    Q_D(const DLogin1Session);
    const auto &result = qvariant_cast<SeatPath_p>(d->m_inter->property("Seat"));
    SeatPath seatPath;
    seatPath.path = result.path.path();
    seatPath.seat_id = result.seat_id;
    return seatPath;
}
UserPath DLogin1Session::user() const
{
    Q_D(const DLogin1Session);
    const auto &result = qvariant_cast<UserPath_p>(d->m_inter->property("User"));
    UserPath userPath;
    userPath.path = result.path.path();
    userPath.user_id = result.user_id;
    return userPath;
}

uint DLogin1Session::audit() const
{
    Q_D(const DLogin1Session);
    return qvariant_cast<uint>(d->m_inter->property("Audit"));
}

uint DLogin1Session::leader() const
{
    Q_D(const DLogin1Session);
    return qvariant_cast<uint>(d->m_inter->property("Leader"));
}
uint DLogin1Session::vtnr() const
{
    Q_D(const DLogin1Session);
    return qvariant_cast<uint>(d->m_inter->property("VTNr"));
}

quint64 DLogin1Session::idleSinceHint() const
{
    Q_D(const DLogin1Session);
    return qvariant_cast<quint64>(d->m_inter->property("IdleSinceHint"));
}

quint64 DLogin1Session::idleSinceHintMonotonic() const
{
    Q_D(const DLogin1Session);
    return qvariant_cast<quint64>(d->m_inter->property("IdleSinceHintMonotonic"));
}

quint64 DLogin1Session::timestamp() const
{
    Q_D(const DLogin1Session);
    return qvariant_cast<quint64>(d->m_inter->property("Timestamp"));
}
quint64 DLogin1Session::timestampMonotonic() const
{
    Q_D(const DLogin1Session);
    return qvariant_cast<quint64>(d->m_inter->property("TimestampMonotonic"));
}

QString DLogin1Session::lastError() const
{
    Q_D(const DLogin1Session);
    return d->m_errorMessage;
}

void DLogin1Session::activate()
{
    Q_D(DLogin1Session);
    QDBusPendingReply<> reply = d->m_inter->asyncCall(QStringLiteral("Activate"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLogin1Session::kill(const QString who, const uint signal_number)
{
    Q_D(DLogin1Session);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("Kill"),
                                                                       {
                                                                           QVariant::fromValue(who),
                                                                           QVariant::fromValue(signal_number),
                                                                       });
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}
void DLogin1Session::lock()
{
    Q_D(DLogin1Session);
    QDBusPendingReply<> reply = d->m_inter->asyncCall(QStringLiteral("Lock"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}
void DLogin1Session::pauseDeviceComplete(const uint major, const uint minor)
{
    Q_D(DLogin1Session);
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
void DLogin1Session::releaseControl()
{
    Q_D(DLogin1Session);
    QDBusPendingReply<> reply = d->m_inter->asyncCall(QStringLiteral("ReleaseControl"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}
void DLogin1Session::releaseDevice(const uint major, const uint minor)
{
    Q_D(DLogin1Session);
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

void DLogin1Session::setBrightness(const QString &subsystem, const QString &name, const uint brightness)
{
    Q_D(DLogin1Session);
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

void DLogin1Session::setIdleHint(const bool idle)
{
    Q_D(DLogin1Session);
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
void DLogin1Session::setLockedHint(const bool locked)
{
    Q_D(DLogin1Session);
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

void DLogin1Session::setType(const QString &type)
{
    Q_D(DLogin1Session);
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

void DLogin1Session::takeControl(const bool force)
{
    Q_D(DLogin1Session);
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
DLogin1Session::takeDevice(uint manjor, uint minor)
{
    Q_D(DLogin1Session);
    QDBusPendingReply<QDBusUnixFileDescriptor, bool> reply = d->m_inter->asyncCallWithArgumentList(
        QStringLiteral("TakeDevice"), {QVariant::fromValue(manjor), QVariant::fromValue(minor)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return std::tuple<int, bool>();
    }
    return std::make_tuple<int, bool>(reply.argumentAt<0>().fileDescriptor(), reply.argumentAt<1>());
}
void DLogin1Session::terminate()
{
    Q_D(DLogin1Session);
    QDBusPendingReply<> reply = d->m_inter->asyncCall(QStringLiteral("Terminate"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}
void DLogin1Session::unlock()
{
    Q_D(DLogin1Session);
    QDBusPendingReply<> reply = d->m_inter->asyncCall(QStringLiteral("Unlock"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}
DLOGIN1_END_NAMESPACE

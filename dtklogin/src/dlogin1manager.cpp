// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dlogin1manager.h"
#include <qdbuspendingreply.h>
#include <qdbusextratypes.h>
#include <qdbusunixfiledescriptor.h>
#include <qglobal.h>
#include <qlist.h>
#include <qnamespace.h>
#include <qobjectdefs.h>
#include <qpair.h>
#include <qstringliteral.h>
#include <qvariant.h>
#include <stdexcept>
#include <sys/types.h>
#include <tuple>

#include "ddbusinterface.h"
#include "dlogin1manager_p.h"
#include "dlogin1types_p.h"
DLOGIN1_BEGIN_NAMESPACE

DLogin1Manager::DLogin1Manager(QObject *parent)
    : QObject(parent)
    , d_ptr(new DLogin1ManagerPrivate(this))
{
    const QString &Service = QStringLiteral("org.freedesktop.login1");
    const QString &Path = QStringLiteral("/org/freedesktop/login1");
    const QString &Interface = QStringLiteral("org.freedesktop.login1.Manager");

    Q_D(DLogin1Manager);
    ScheduledShutdownValue_p::registerMetaType();
    SessionProperty_p::registerMetaType();
    Inhibitor_p::registerMetaType();
    Seat_p::registerMetaType();
    Session_p::registerMetaType();
    User_p::registerMetaType();
    d->m_inter = new DDBusInterface(Service, Path, Interface, QDBusConnection::systemBus(), d);

    // init signals;
    QDBusConnection::systemBus().connect(Service, Path, Interface, "PreparingForShutdown",
                                         d, SLOT(PrepareForShutdown(const bool)));
    QDBusConnection::systemBus().connect(Service, Path, Interface, "PreparingForSleep",
                                         d, SLOT(PrepareForSleep(const bool)));
    QDBusConnection::systemBus().connect(Service, Path, Interface, "SeatNew",
                                         d, SLOT(SeatNew(const QString&, const QDBusObjectPath&)));
    QDBusConnection::systemBus().connect(Service, Path, Interface, "SeatRemoved",
                                         d, SLOT(SeatRemoved(const QString&, const QDBusObjectPath&)));
    QDBusConnection::systemBus().connect(Service, Path, Interface, "SessionNew",
                                         d, SLOT(SessionNew(const QString&, const QDBusObjectPath&)));
    QDBusConnection::systemBus().connect(Service, Path, Interface, "SessionRemoved",
                                         d, SLOT(SessionRemoved(const QString&, const QDBusObjectPath&)));
    QDBusConnection::systemBus().connect(Service, Path, Interface, "UserNew",
                                         d, SLOT(UserNew(const uint, const QDBusObjectPath&)));
    QDBusConnection::systemBus().connect(Service, Path, Interface, "UserRemoved",
                                         d, SLOT(UserRemoved(const uint, const QDBusObjectPath&)));
    connect(d, &DLogin1ManagerPrivate::PrepareForShutdown, this, &DLogin1Manager::PrepareForShutdown);
    connect(d, &DLogin1ManagerPrivate::PrepareForSleep, this, &DLogin1Manager::PrepareForSleep);
    connect(d, &DLogin1ManagerPrivate::SeatNew, this, [this] (const QString &seat_id, const QDBusObjectPath &path) {
                emit this->SeatNew(seat_id, path.path());
            });
    connect(d, &DLogin1ManagerPrivate::SeatRemoved, this, [this] (const QString &seat_id, const QDBusObjectPath &path) {
                emit this->SeatRemoved(seat_id, path.path());
            });
    connect(d, &DLogin1ManagerPrivate::SessionNew, this, [this] (const QString &session_id, const QDBusObjectPath &path) {
                emit this->SessionNew(session_id, path.path());
            });
    connect(d, &DLogin1ManagerPrivate::SessionRemoved, this, [this] (const QString &session_id, const QDBusObjectPath &path) {
                emit this->SessionRemoved(session_id, path.path());
            });
    connect(d, &DLogin1ManagerPrivate::UserNew, this, [this] (const uint uid, const QDBusObjectPath &path) {
                emit this->UserNew(uid, path.path());
            });
    connect(d, &DLogin1ManagerPrivate::UserRemoved, this, [this] (const uint uid, const QDBusObjectPath &path) {
                emit this->UserRemoved(uid, path.path());
            });
}

DLogin1Manager::~DLogin1Manager() {}

// properties

QStringList DLogin1Manager::bootLoaderEntries() const
{
    Q_D(const DLogin1Manager);
    return qdbus_cast<QStringList>(d->m_inter->property("BootLoaderEntries"));
}

QStringList DLogin1Manager::killExcludeUsers() const
{
    Q_D(const DLogin1Manager);
    return qdbus_cast<QStringList>(d->m_inter->property("KillExcludeUsers"));
}

QStringList DLogin1Manager::killOnlyUsers() const
{
    Q_D(const DLogin1Manager);
    return qdbus_cast<QStringList>(d->m_inter->property("KillOnlyUsers"));
}

bool DLogin1Manager::docked() const
{
    Q_D(const DLogin1Manager);
    return qdbus_cast<bool>(d->m_inter->property("Docked"));
}

bool DLogin1Manager::enableWallMessages() const
{
    Q_D(const DLogin1Manager);
    return qdbus_cast<bool>(d->m_inter->property("EnableWallMessages"));
}

void DLogin1Manager::setEnableWallMessages(const bool enable)
{
    Q_D(const DLogin1Manager);
    d->m_inter->setProperty("EnableWallMessages", QVariant::fromValue(enable));
}

bool DLogin1Manager::idleHint() const
{
    Q_D(const DLogin1Manager);
    return qdbus_cast<bool>(d->m_inter->property("LdleHint"));
}

bool DLogin1Manager::killUserProcesses() const
{
    Q_D(const DLogin1Manager);
    return qdbus_cast<bool>(d->m_inter->property("KillUserProcesses"));
}

bool DLogin1Manager::lidClosed() const
{
    Q_D(const DLogin1Manager);
    return qdbus_cast<bool>(d->m_inter->property("LidClosed"));
}

bool DLogin1Manager::onExternalPower() const
{
    Q_D(const DLogin1Manager);
    return qdbus_cast<bool>(d->m_inter->property("OnExternalPower"));
}

bool DLogin1Manager::preparingForShutdown() const
{
    Q_D(const DLogin1Manager);
    return qdbus_cast<bool>(d->m_inter->property("PreparingForShutdown"));
}

bool DLogin1Manager::preparingForSleep() const
{
    Q_D(const DLogin1Manager);
    return qdbus_cast<bool>(d->m_inter->property("PreparingForSleep"));
}

bool DLogin1Manager::rebootToFirmwareSetup() const
{
    Q_D(const DLogin1Manager);
    return qdbus_cast<bool>(d->m_inter->property("RebootToFirmwareSetup"));
}

bool DLogin1Manager::removeIPC() const
{
    Q_D(const DLogin1Manager);
    return qdbus_cast<bool>(d->m_inter->property("RemoveIPC"));
}

QString DLogin1Manager::blockInhibited() const
{
    Q_D(const DLogin1Manager);
    return qdbus_cast<QString>(d->m_inter->property("BlockInhibited"));
}

QString DLogin1Manager::delayInhibited() const
{
    Q_D(const DLogin1Manager);
    return qdbus_cast<QString>(d->m_inter->property("DelayInhibited"));
}

QString DLogin1Manager::handleHibernateKey() const
{
    Q_D(const DLogin1Manager);
    return qdbus_cast<QString>(d->m_inter->property("HandleHibernateKey"));
}

QString DLogin1Manager::handleLidSwitch() const
{
    Q_D(const DLogin1Manager);
    return qdbus_cast<QString>(d->m_inter->property("HandleLidSwitch"));
}

QString DLogin1Manager::handleLidSwitchDocked() const
{
    Q_D(const DLogin1Manager);
    return qdbus_cast<QString>(d->m_inter->property("HandleLidSwitchDocked"));
}

QString DLogin1Manager::handleLidSwitchExternalPower() const
{
    Q_D(const DLogin1Manager);
    return qdbus_cast<QString>(d->m_inter->property("HandleLidSwitchExternalPower"));
}

QString DLogin1Manager::handlePowerKey() const
{
    Q_D(const DLogin1Manager);
    return qdbus_cast<QString>(d->m_inter->property("HandlePowerKey"));
}

QString DLogin1Manager::handleSuspendKey() const
{
    Q_D(const DLogin1Manager);
    return qdbus_cast<QString>(d->m_inter->property("HandleSuspendKey"));
}

QString DLogin1Manager::idleAction() const
{
    Q_D(const DLogin1Manager);
    return qdbus_cast<QString>(d->m_inter->property("IdleAction"));
}

QString DLogin1Manager::rebootParameter() const
{
    Q_D(const DLogin1Manager);
    return qdbus_cast<QString>(d->m_inter->property("RebootParameter"));
}

QString DLogin1Manager::rebootToBootLoaderEntry() const
{
    Q_D(const DLogin1Manager);
    return qdbus_cast<QString>(d->m_inter->property("RebootToBootLoaderEntry"));
}

QString DLogin1Manager::wallMessage() const
{
    Q_D(const DLogin1Manager);
    return qdbus_cast<QString>(d->m_inter->property("WallMessage"));
}

ScheduledShutdownValue DLogin1Manager::scheduledShutdown() const
{
    Q_D(const DLogin1Manager);
    const auto &result = qdbus_cast<ScheduledShutdownValue_p>(d->m_inter->property("ScheduledShutdown"));
    ScheduledShutdownValue value;
    value.type = result.type;
    value.usec = result.usec;
    return value;
}

uint DLogin1Manager::nAutoVTs() const
{
    Q_D(const DLogin1Manager);
    return qdbus_cast<uint>(d->m_inter->property("NAutoVTs"));
}

quint64 DLogin1Manager::holdoffTimeoutUSec() const
{
    Q_D(const DLogin1Manager);
    return qdbus_cast<quint64>(d->m_inter->property("HoldoffTimeoutUSec"));
}

quint64 DLogin1Manager::idleActionUSec() const
{
    Q_D(const DLogin1Manager);
    return qdbus_cast<quint64>(d->m_inter->property("IdleActionUSec"));
}

quint64 DLogin1Manager::idleSinceHint() const
{
    Q_D(const DLogin1Manager);
    return qdbus_cast<quint64>(d->m_inter->property("IdleSinceHint"));
}

quint64 DLogin1Manager::idleSinceHintMonotonic() const
{
    Q_D(const DLogin1Manager);
    return qdbus_cast<quint64>(d->m_inter->property("IdleSinceHintMonotonic"));
}

quint64 DLogin1Manager::inhibitDelayMaxUSec() const
{
    Q_D(const DLogin1Manager);
    return qdbus_cast<quint64>(d->m_inter->property("InhibitDelayMaxUSec"));
}

quint64 DLogin1Manager::inhibitorsMax() const
{
    Q_D(const DLogin1Manager);
    return qdbus_cast<quint64>(d->m_inter->property("InhibitorsMax"));
}

quint64 DLogin1Manager::nCurrentInhibitors() const
{
    Q_D(const DLogin1Manager);
    return qdbus_cast<quint64>(d->m_inter->property("NCurrentInhibitors"));
}

quint64 DLogin1Manager::nCurrentSessions() const
{
    Q_D(const DLogin1Manager);
    return qdbus_cast<quint64>(d->m_inter->property("NCurrentSessions"));
}

quint64 DLogin1Manager::rebootToBootLoaderMenu() const
{
    Q_D(const DLogin1Manager);
    return qdbus_cast<quint64>(d->m_inter->property("RebootToBootLoaderMenu"));
}

quint64 DLogin1Manager::runtimeDirectoryInodesMax() const
{
    Q_D(const DLogin1Manager);
    return qdbus_cast<quint64>(d->m_inter->property("RuntimeDirectoryInodesMax"));
}

quint64 DLogin1Manager::runtimeDirectorySize() const
{
    Q_D(const DLogin1Manager);
    return qdbus_cast<quint64>(d->m_inter->property("RuntimeDirectorySize"));
}

quint64 DLogin1Manager::sessionsMax() const
{
    Q_D(const DLogin1Manager);
    return qdbus_cast<quint64>(d->m_inter->property("SessionsMax"));
}

quint64 DLogin1Manager::userStopDelayUSec() const
{
    Q_D(const DLogin1Manager);
    return qdbus_cast<quint64>(d->m_inter->property("UserStopDelayUSec"));
}

// public slots

QString DLogin1Manager::lastError() const
{
    Q_D(const DLogin1Manager);
    return d->m_errorMessage;
}

void DLogin1Manager::activateSession(const QString &session_id)
{
    Q_D(DLogin1Manager);
    QVariantList args {QVariant::fromValue(session_id)};
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList("ActivateSession", args);
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLogin1Manager::activateSessionOnSeat(const QString &session_id, const QString &seat_id)
{
    Q_D(DLogin1Manager);
    QVariantList args {QVariant::fromValue(session_id), QVariant::fromValue(seat_id)};
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList("ActivateSessionOnSeat", args);
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLogin1Manager::attachDevice(const QString &seat_id, const QString &sysfs_path, const bool interactive)
{
    Q_D(DLogin1Manager);
    QVariantList args {QVariant::fromValue(seat_id), QVariant::fromValue(sysfs_path), QVariant::fromValue(interactive)};
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList("attachDevice", {seat_id, sysfs_path, interactive});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

QString DLogin1Manager::canHalt()
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<QString> reply = d->m_inter->asyncCall(QStringLiteral("CanHalt"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return reply.value();
}

QString DLogin1Manager::canHibernate()
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<QString> reply = d->m_inter->asyncCall(QStringLiteral("CanHibernate"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return reply.value();
}

QString DLogin1Manager::canHybridSleep()
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<QString> reply = d->m_inter->asyncCall(QStringLiteral("CanHybridSleep"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return reply.value();
}

QString DLogin1Manager::canPowerOff()
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<QString> reply = d->m_inter->asyncCall(QStringLiteral("CanPowerOff"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return reply.value();
}

QString DLogin1Manager::canReboot()
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<QString> reply = d->m_inter->asyncCall(QStringLiteral("CanReboot"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return reply.value();
}

QString DLogin1Manager::canRebootParameter()
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<QString> reply = d->m_inter->asyncCall(QStringLiteral("CanRebootParameter"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return reply.value();
}

QString DLogin1Manager::canRebootToBootLoaderEntry()
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<QString> reply = d->m_inter->asyncCall(QStringLiteral("CanRebootToBootLoaderEntry"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return reply.value();
}

QString DLogin1Manager::canRebootToBootLoaderMenu()
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<QString> reply = d->m_inter->asyncCall(QStringLiteral("CanRebootToBootLoaderMenu"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return reply.value();
}

QString DLogin1Manager::canRebootToFirmwareSetup()
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<QString> reply = d->m_inter->asyncCall(QStringLiteral("CanRebootToFirmwareSetup"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return reply.value();
}

QString DLogin1Manager::canSuspend()
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<QString> reply = d->m_inter->asyncCall(QStringLiteral("CanSuspend"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return reply.value();
}

QString DLogin1Manager::canSuspendThenHibernate()
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<QString> reply = d->m_inter->asyncCall(QStringLiteral("CanSuspendThenHibernate"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return reply.value();
}

bool DLogin1Manager::cancelScheduledShutdown()
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<bool> reply = d->m_inter->asyncCall(QStringLiteral("CancelScheduledShutdown"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return false;
    }
    return reply.value();
}

std::tuple<QString,     // session_id
    QString,        // path
    QString,        // runtime_path
    int,            // fifo_fd
    uint,           // uid
    QString,        // seat_id
    uint,           // vtnr
    bool            // existing
    > DLogin1Manager::createSession(uint uid, uint pid, const QString &service, const QString &type,
        const QString &_class, const QString &desktop, const QString &seat_id,
        uint vtnr, const QString &tty, const QString &display, const QString &remote,
        const QString &remote_user, const QString &remote_host, const QList<SessionProperty> &properties)
{
    Q_D(DLogin1Manager);
    QList<SessionProperty_p> properties_p;
    for (auto && property : properties) {
        SessionProperty_p property_p;
        property_p.name = property.name;
        property_p.var.setVariant(property.var);
        properties_p.append(property_p);
    }
    QVariantList args;
    args << QVariant::fromValue(uid) << QVariant::fromValue(pid) << QVariant::fromValue(service) << QVariant::fromValue(type)
        << QVariant::fromValue(_class) << QVariant::fromValue(desktop) << QVariant::fromValue(seat_id)
        << QVariant::fromValue(vtnr) << QVariant::fromValue(tty) << QVariant::fromValue(display) << QVariant::fromValue(remote)
        << QVariant::fromValue(remote_user) << QVariant::fromValue(remote_host) << QVariant::fromValue(properties_p);
    QDBusPendingReply<QString, QDBusObjectPath, QString, QDBusUnixFileDescriptor, uint, QString, uint, bool>
        reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("CreateSession"), args);
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return std::tuple<QString, QString, QString, int, uint, QString, uint, bool>();
    }
    return std::make_tuple(reply.argumentAt<0>(), reply.argumentAt<1>().path(), reply.argumentAt<2>(),
        reply.argumentAt<3>().fileDescriptor(), reply.argumentAt<4>(), reply.argumentAt<5>(), reply.argumentAt<6>(),
        reply.argumentAt<7>());
}

void DLogin1Manager::flushDevices(const bool value)
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("flushDevices"), {QVariant::fromValue(value)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

QString DLogin1Manager::getSeat(const QString &seat_id)
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<QDBusObjectPath> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("GetSeat"),
        {QVariant::fromValue(seat_id)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return reply.value().path();
}

QString DLogin1Manager::getSession(const QString &session_id)
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<QDBusObjectPath> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("GetSession"),
        {QVariant::fromValue(session_id)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return reply.value().path();
}

QString DLogin1Manager::getSessionByPID(const uint pid)
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<QDBusObjectPath> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("GetSessionByPID"),
        {QVariant::fromValue(pid)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return reply.value().path();
}

QString DLogin1Manager::getUser(const uint uid)
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<QDBusObjectPath> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("GetUser"),
        {QVariant::fromValue(uid)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return reply.value().path();
}

QString DLogin1Manager::getUserByPID(const uint pid)
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<QDBusObjectPath> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("GetUserByPID"),
        {QVariant::fromValue(pid)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return reply.value().path();
}

void DLogin1Manager::halt(const bool interactive)
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList("Halt", {QVariant::fromValue(interactive)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLogin1Manager::haltWithFlags(const quint64 flags)
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList("HaltWithFlags", {QVariant::fromValue(flags)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLogin1Manager::hibernate(const bool interactive)
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList("Hibernate", {QVariant::fromValue(interactive)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLogin1Manager::hibernateWithFlags(const quint64 flags)
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList("HibernateWithFlags", {QVariant::fromValue(flags)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLogin1Manager::hybridSleep(const bool interactive)
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList("HybridSleep", {QVariant::fromValue(interactive)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLogin1Manager::hybridSleepWithFlags(const quint64 flags)
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList("HybridSleepWithFlags", {QVariant::fromValue(flags)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

int DLogin1Manager::inhibit(const QString &what, const QString &who, const QString &why, const QString &mode)
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<QDBusUnixFileDescriptor> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("Inhibit"),
        {QVariant::fromValue(what), QVariant::fromValue(who), QVariant::fromValue(why), QVariant::fromValue(mode)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return -1;
    }
    return reply.value().fileDescriptor();
}

void DLogin1Manager::killSession(const QString &session_id, const QString &who, const int signal_number)
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList("KillSession",
        {QVariant::fromValue(session_id), QVariant::fromValue(who), QVariant::fromValue(signal_number)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLogin1Manager::killUser(const uint uid, const int signal_number)
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("KillUser"),
        {QVariant::fromValue(uid), QVariant::fromValue(signal_number)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

QList<Inhibitor> DLogin1Manager::listInhibitors()
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<QList<Inhibitor_p>> reply = d->m_inter->asyncCall(QStringLiteral("ListInhibitors"));
    reply.waitForFinished();
    QList<Inhibitor> inhibitors;
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return inhibitors;
    }

    for (auto &&inhibitor_p : reply.value()) {
        Inhibitor inhibitor;
        inhibitor.mode = inhibitor_p.mode;
        inhibitor.pid = inhibitor_p.pid;
        inhibitor.uid = inhibitor_p.uid;
        inhibitor.what = inhibitor_p.what;
        inhibitor.who = inhibitor_p.who;
        inhibitor.why = inhibitor_p.why;
        inhibitors.append(inhibitor);
    }
    return inhibitors;
}

QList<Seat> DLogin1Manager::listSeats()
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<QList<Seat_p>> reply = d->m_inter->asyncCall(QStringLiteral("ListSeats"));
    reply.waitForFinished();
    QList<Seat> seats;
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return seats;
    }

    for (auto &&seat_p : reply.value()) {
        Seat seat;
        seat.seat_id = seat_p.seat_id;
        seat.path = seat_p.path.path();
        seats.append(seat);
    }
    return seats;
}

QList<Session> DLogin1Manager::listSessions()
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<QList<Session_p>> reply = d->m_inter->asyncCall(QStringLiteral("ListSessions"));
    reply.waitForFinished();
    QList<Session> sessions;
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return sessions;
    }

    for (auto &&session_p : reply.value()) {
        Session session;
        session.path = session_p.path.path();
        session.seat_id = session_p.seat_id;
        session.session_id = session_p.session_id;
        session.user_id = session_p.user_id;
        session.user_name = session_p.user_name;
        sessions.append(session);
    }
    return sessions;
}

QList<User> DLogin1Manager::listUsers()
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<QList<User_p>> reply = d->m_inter->asyncCall(QStringLiteral("ListUsers"));
    reply.waitForFinished();
    QList<User> users;
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return users;
    }

    for (auto &&user_p : reply.value()) {
        User user;
        user.user_name = user_p.user_name;
        user.user_id = user_p.user_id;
        user.path = user_p.path.path();
        users.append(user);
    }
    return users;
}

void DLogin1Manager::lockSession(const QString &session_id)
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("LockSession"),
        {QVariant::fromValue(session_id)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLogin1Manager::lockSessions()
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<> reply = d->m_inter->asyncCall(QStringLiteral("LockSessions"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLogin1Manager::powerOff(const bool interactive)
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("PowerOff"),
        {QVariant::fromValue(interactive)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLogin1Manager::powerOffWithFlags(const quint64 flags)
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList("PowerOffWithFlags", {QVariant::fromValue(flags)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLogin1Manager::reboot(const bool interactive)
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("Reboot"),
        {QVariant::fromValue(interactive)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLogin1Manager::rebootWithFlags(const quint64 flags)
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList("RebootWithFlags", {QVariant::fromValue(flags)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLogin1Manager::releaseSession(const QString &session_id)
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("ReleaseSession"),
        {QVariant::fromValue(session_id)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLogin1Manager::setRebootParameter(const QString &paramter)
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("SetRebootParameter"),
        {QVariant::fromValue(paramter)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLogin1Manager::scheduleShutdown(const QString &type, const quint64 usec)
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("ScheduleShutdown"),
        {QVariant::fromValue(type), QVariant::fromValue(usec)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLogin1Manager::setRebootToBootLoaderEntry(const QString &entry)
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("SetRebootToBootLoaderEntry"),
        {QVariant::fromValue(entry)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLogin1Manager::setRebootToBootLoaderMenu(const quint64 timeout)
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("SetRebootToBootLoaderMenu"),
        {QVariant::fromValue(timeout)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLogin1Manager::setRebootToFirmwareSetup(const bool enable)
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("SetRebootToFirmwareSetup"),
        {QVariant::fromValue(enable)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLogin1Manager::setUserLinger(const uint uid, const bool enable, const bool interactive)
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("SetUserLinger"),
        {QVariant::fromValue(uid), QVariant::fromValue(enable), QVariant::fromValue(interactive)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLogin1Manager::setWallMessage(const QString &message, const bool enable)
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("SetWallMessage"),
        {QVariant::fromValue(message), QVariant::fromValue(enable)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLogin1Manager::suspend(const bool interactive)
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("Suspend"),
        {QVariant::fromValue(interactive)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLogin1Manager::suspendThenHibernate(const bool interactive)
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("SuspendThenHibernate"),
        {QVariant::fromValue(interactive)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLogin1Manager::suspendThenHibernateWithFlags(const quint64 flags)
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList("SuspendThenHibernateWithFlags", {QVariant::fromValue(flags)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLogin1Manager::suspendWithFlags(const quint64 flags)
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList("SuspendWithFlags", {QVariant::fromValue(flags)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLogin1Manager::terminateSeat(const QString &seat_id)
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("TerminateSeat"),
        {QVariant::fromValue(seat_id)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLogin1Manager::terminateSession(const QString &session_id)
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("TerminateSession"),
        {QVariant::fromValue(session_id)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLogin1Manager::terminateUser(const uint uid)
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("TerminateUser"),
        {QVariant::fromValue(uid)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLogin1Manager::unlockSession(const QString &session_id)
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("UnlockSession"),
        {QVariant::fromValue(session_id)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLogin1Manager::unlockSessions()
{
    Q_D(DLogin1Manager);
    QDBusPendingReply<> reply = d->m_inter->asyncCall(QStringLiteral("UnlockSessions"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}
DLOGIN1_END_NAMESPACE

// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dloginmanager.h"
#include <qdbusextratypes.h>
#include <qdbuspendingreply.h>
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
#include "dloginmanager_p.h"
#include "dlogintypes_p.h"
DLOGIN_BEGIN_NAMESPACE

DLoginManager::DLoginManager(QObject *parent)
    : QObject(parent)
    , d_ptr(new DLoginManagerPrivate(this))
{
    const QString &Service = QStringLiteral("org.freedesktop.login1");
    const QString &Path = QStringLiteral("/org/freedesktop/login1");
    const QString &Interface = QStringLiteral("org.freedesktop.login1.Manager");

    Q_D(DLoginManager);
    ScheduledShutdownValue_p::registerMetaType();
    SessionProperty_p::registerMetaType();
    Inhibitor_p::registerMetaType();
    Seat_p::registerMetaType();
    Session_p::registerMetaType();
    User_p::registerMetaType();
    d->m_inter = new DDBusInterface(Service, Path, Interface, QDBusConnection::systemBus(), d);

    // init signals;
    QDBusConnection::systemBus().connect(Service, Path, Interface, "PreparingForShutdown",
                                         d, SLOT(prepareForShutdown(const bool)));
    QDBusConnection::systemBus().connect(Service, Path, Interface, "PreparingForSleep",
                                         d, SLOT(prepareForSleep(const bool)));
    QDBusConnection::systemBus().connect(Service, Path, Interface, "seatNew",
                                         d, SLOT(seatNew(const QString&, const QDBusObjectPath&)));
    QDBusConnection::systemBus().connect(Service, Path, Interface, "seatRemoved",
                                         d, SLOT(seatRemoved(const QString&, const QDBusObjectPath&)));
    QDBusConnection::systemBus().connect(Service, Path, Interface, "sessionNew",
                                         d, SLOT(sessionNew(const QString&, const QDBusObjectPath&)));
    QDBusConnection::systemBus().connect(Service, Path, Interface, "sessionRemoved",
                                         d, SLOT(sessionRemoved(const QString&, const QDBusObjectPath&)));
    QDBusConnection::systemBus().connect(Service, Path, Interface, "userNew",
                                         d, SLOT(userNew(const uint, const QDBusObjectPath&)));
    QDBusConnection::systemBus().connect(Service, Path, Interface, "userRemoved",
                                         d, SLOT(userRemoved(const uint, const QDBusObjectPath&)));
    connect(d, &DLoginManagerPrivate::PrepareForShutdown, this, &DLoginManager::prepareForShutdown);
    connect(d, &DLoginManagerPrivate::PrepareForSleep, this, &DLoginManager::prepareForSleep);
    connect(d, &DLoginManagerPrivate::SeatNew, this, [this] (const QString &seat_id, const QDBusObjectPath &path) {
                emit this->seatNew(seat_id, path.path());
            });
    connect(d, &DLoginManagerPrivate::SeatRemoved, this, [this] (const QString &seat_id, const QDBusObjectPath &path) {
                emit this->seatRemoved(seat_id, path.path());
            });
    connect(d, &DLoginManagerPrivate::SessionNew, this, [this] (const QString &session_id, const QDBusObjectPath &path) {
                emit this->sessionNew(session_id, path.path());
            });
    connect(d, &DLoginManagerPrivate::SessionRemoved, this, [this] (const QString &session_id, const QDBusObjectPath &path) {
                emit this->sessionRemoved(session_id, path.path());
            });
    connect(d, &DLoginManagerPrivate::UserNew, this, [this] (const uint uid, const QDBusObjectPath &path) {
                emit this->userNew(uid, path.path());
            });
    connect(d, &DLoginManagerPrivate::UserRemoved, this, [this] (const uint uid, const QDBusObjectPath &path) {
                emit this->userRemoved(uid, path.path());
            });
}

DLoginManager::~DLoginManager() {}

// properties

QStringList DLoginManager::bootLoaderEntries() const
{
    Q_D(const DLoginManager);
    return qdbus_cast<QStringList>(d->m_inter->property("BootLoaderEntries"));
}

QStringList DLoginManager::killExcludeUsers() const
{
    Q_D(const DLoginManager);
    return qdbus_cast<QStringList>(d->m_inter->property("KillExcludeUsers"));
}

QStringList DLoginManager::killOnlyUsers() const
{
    Q_D(const DLoginManager);
    return qdbus_cast<QStringList>(d->m_inter->property("KillOnlyUsers"));
}

bool DLoginManager::docked() const
{
    Q_D(const DLoginManager);
    return qdbus_cast<bool>(d->m_inter->property("Docked"));
}

bool DLoginManager::enableWallMessages() const
{
    Q_D(const DLoginManager);
    return qdbus_cast<bool>(d->m_inter->property("EnableWallMessages"));
}

void DLoginManager::setEnableWallMessages(const bool enable)
{
    Q_D(const DLoginManager);
    d->m_inter->setProperty("EnableWallMessages", QVariant::fromValue(enable));
}

bool DLoginManager::idleHint() const
{
    Q_D(const DLoginManager);
    return qdbus_cast<bool>(d->m_inter->property("LdleHint"));
}

bool DLoginManager::killUserProcesses() const
{
    Q_D(const DLoginManager);
    return qdbus_cast<bool>(d->m_inter->property("KillUserProcesses"));
}

bool DLoginManager::lidClosed() const
{
    Q_D(const DLoginManager);
    return qdbus_cast<bool>(d->m_inter->property("LidClosed"));
}

bool DLoginManager::onExternalPower() const
{
    Q_D(const DLoginManager);
    return qdbus_cast<bool>(d->m_inter->property("OnExternalPower"));
}

bool DLoginManager::preparingForShutdown() const
{
    Q_D(const DLoginManager);
    return qdbus_cast<bool>(d->m_inter->property("PreparingForShutdown"));
}

bool DLoginManager::preparingForSleep() const
{
    Q_D(const DLoginManager);
    return qdbus_cast<bool>(d->m_inter->property("PreparingForSleep"));
}

bool DLoginManager::rebootToFirmwareSetup() const
{
    Q_D(const DLoginManager);
    return qdbus_cast<bool>(d->m_inter->property("RebootToFirmwareSetup"));
}

bool DLoginManager::removeIPC() const
{
    Q_D(const DLoginManager);
    return qdbus_cast<bool>(d->m_inter->property("RemoveIPC"));
}

QString DLoginManager::blockInhibited() const
{
    Q_D(const DLoginManager);
    return qdbus_cast<QString>(d->m_inter->property("BlockInhibited"));
}

QString DLoginManager::delayInhibited() const
{
    Q_D(const DLoginManager);
    return qdbus_cast<QString>(d->m_inter->property("DelayInhibited"));
}

QString DLoginManager::handleHibernateKey() const
{
    Q_D(const DLoginManager);
    return qdbus_cast<QString>(d->m_inter->property("HandleHibernateKey"));
}

QString DLoginManager::handleLidSwitch() const
{
    Q_D(const DLoginManager);
    return qdbus_cast<QString>(d->m_inter->property("HandleLidSwitch"));
}

QString DLoginManager::handleLidSwitchDocked() const
{
    Q_D(const DLoginManager);
    return qdbus_cast<QString>(d->m_inter->property("HandleLidSwitchDocked"));
}

QString DLoginManager::handleLidSwitchExternalPower() const
{
    Q_D(const DLoginManager);
    return qdbus_cast<QString>(d->m_inter->property("HandleLidSwitchExternalPower"));
}

QString DLoginManager::handlePowerKey() const
{
    Q_D(const DLoginManager);
    return qdbus_cast<QString>(d->m_inter->property("HandlePowerKey"));
}

QString DLoginManager::handleSuspendKey() const
{
    Q_D(const DLoginManager);
    return qdbus_cast<QString>(d->m_inter->property("HandleSuspendKey"));
}

QString DLoginManager::idleAction() const
{
    Q_D(const DLoginManager);
    return qdbus_cast<QString>(d->m_inter->property("IdleAction"));
}

QString DLoginManager::rebootParameter() const
{
    Q_D(const DLoginManager);
    return qdbus_cast<QString>(d->m_inter->property("RebootParameter"));
}

QString DLoginManager::rebootToBootLoaderEntry() const
{
    Q_D(const DLoginManager);
    return qdbus_cast<QString>(d->m_inter->property("RebootToBootLoaderEntry"));
}

QString DLoginManager::wallMessage() const
{
    Q_D(const DLoginManager);
    return qdbus_cast<QString>(d->m_inter->property("WallMessage"));
}

ScheduledShutdownValue DLoginManager::scheduledShutdown() const
{
    Q_D(const DLoginManager);
    const auto &result = qdbus_cast<ScheduledShutdownValue_p>(d->m_inter->property("ScheduledShutdown"));
    ScheduledShutdownValue value;
    value.type = result.type;
    value.usec = result.usec;
    return value;
}

uint DLoginManager::nAutoVTs() const
{
    Q_D(const DLoginManager);
    return qdbus_cast<uint>(d->m_inter->property("NAutoVTs"));
}

quint64 DLoginManager::holdoffTimeoutUSec() const
{
    Q_D(const DLoginManager);
    return qdbus_cast<quint64>(d->m_inter->property("HoldoffTimeoutUSec"));
}

quint64 DLoginManager::idleActionUSec() const
{
    Q_D(const DLoginManager);
    return qdbus_cast<quint64>(d->m_inter->property("IdleActionUSec"));
}

quint64 DLoginManager::idleSinceHint() const
{
    Q_D(const DLoginManager);
    return qdbus_cast<quint64>(d->m_inter->property("IdleSinceHint"));
}

quint64 DLoginManager::idleSinceHintMonotonic() const
{
    Q_D(const DLoginManager);
    return qdbus_cast<quint64>(d->m_inter->property("IdleSinceHintMonotonic"));
}

quint64 DLoginManager::inhibitDelayMaxUSec() const
{
    Q_D(const DLoginManager);
    return qdbus_cast<quint64>(d->m_inter->property("InhibitDelayMaxUSec"));
}

quint64 DLoginManager::inhibitorsMax() const
{
    Q_D(const DLoginManager);
    return qdbus_cast<quint64>(d->m_inter->property("InhibitorsMax"));
}

quint64 DLoginManager::nCurrentInhibitors() const
{
    Q_D(const DLoginManager);
    return qdbus_cast<quint64>(d->m_inter->property("NCurrentInhibitors"));
}

quint64 DLoginManager::nCurrentSessions() const
{
    Q_D(const DLoginManager);
    return qdbus_cast<quint64>(d->m_inter->property("NCurrentSessions"));
}

quint64 DLoginManager::rebootToBootLoaderMenu() const
{
    Q_D(const DLoginManager);
    return qdbus_cast<quint64>(d->m_inter->property("RebootToBootLoaderMenu"));
}

quint64 DLoginManager::runtimeDirectoryInodesMax() const
{
    Q_D(const DLoginManager);
    return qdbus_cast<quint64>(d->m_inter->property("RuntimeDirectoryInodesMax"));
}

quint64 DLoginManager::runtimeDirectorySize() const
{
    Q_D(const DLoginManager);
    return qdbus_cast<quint64>(d->m_inter->property("RuntimeDirectorySize"));
}

quint64 DLoginManager::sessionsMax() const
{
    Q_D(const DLoginManager);
    return qdbus_cast<quint64>(d->m_inter->property("SessionsMax"));
}

quint64 DLoginManager::userStopDelayUSec() const
{
    Q_D(const DLoginManager);
    return qdbus_cast<quint64>(d->m_inter->property("UserStopDelayUSec"));
}

// public slots

QString DLoginManager::lastError() const
{
    Q_D(const DLoginManager);
    return d->m_errorMessage;
}

void DLoginManager::activateSession(const QString &sessionId)
{
    Q_D(DLoginManager);
    QVariantList args {QVariant::fromValue(sessionId)};
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList("ActivateSession", args);
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLoginManager::activateSessionOnSeat(const QString &sessionId, const QString &seatId)
{
    Q_D(DLoginManager);
    QVariantList args {QVariant::fromValue(sessionId), QVariant::fromValue(seatId)};
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList("ActivateSessionOnSeat", args);
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLoginManager::attachDevice(const QString &seatId, const QString &sysfsPath, const bool interactive)
{
    Q_D(DLoginManager);
    QVariantList args {QVariant::fromValue(seatId), QVariant::fromValue(sysfsPath), QVariant::fromValue(interactive)};
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList("attachDevice", {seatId, sysfsPath, interactive});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

QString DLoginManager::canHalt()
{
    Q_D(DLoginManager);
    QDBusPendingReply<QString> reply = d->m_inter->asyncCall(QStringLiteral("CanHalt"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return reply.value();
}

QString DLoginManager::canHibernate()
{
    Q_D(DLoginManager);
    QDBusPendingReply<QString> reply = d->m_inter->asyncCall(QStringLiteral("CanHibernate"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return reply.value();
}

QString DLoginManager::canHybridSleep()
{
    Q_D(DLoginManager);
    QDBusPendingReply<QString> reply = d->m_inter->asyncCall(QStringLiteral("CanHybridSleep"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return reply.value();
}

QString DLoginManager::canPowerOff()
{
    Q_D(DLoginManager);
    QDBusPendingReply<QString> reply = d->m_inter->asyncCall(QStringLiteral("CanPowerOff"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return reply.value();
}

QString DLoginManager::canReboot()
{
    Q_D(DLoginManager);
    QDBusPendingReply<QString> reply = d->m_inter->asyncCall(QStringLiteral("CanReboot"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return reply.value();
}

QString DLoginManager::canRebootParameter()
{
    Q_D(DLoginManager);
    QDBusPendingReply<QString> reply = d->m_inter->asyncCall(QStringLiteral("CanRebootParameter"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return reply.value();
}

QString DLoginManager::canRebootToBootLoaderEntry()
{
    Q_D(DLoginManager);
    QDBusPendingReply<QString> reply = d->m_inter->asyncCall(QStringLiteral("CanRebootToBootLoaderEntry"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return reply.value();
}

QString DLoginManager::canRebootToBootLoaderMenu()
{
    Q_D(DLoginManager);
    QDBusPendingReply<QString> reply = d->m_inter->asyncCall(QStringLiteral("CanRebootToBootLoaderMenu"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return reply.value();
}

QString DLoginManager::canRebootToFirmwareSetup()
{
    Q_D(DLoginManager);
    QDBusPendingReply<QString> reply = d->m_inter->asyncCall(QStringLiteral("CanRebootToFirmwareSetup"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return reply.value();
}

QString DLoginManager::canSuspend()
{
    Q_D(DLoginManager);
    QDBusPendingReply<QString> reply = d->m_inter->asyncCall(QStringLiteral("CanSuspend"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return reply.value();
}

QString DLoginManager::canSuspendThenHibernate()
{
    Q_D(DLoginManager);
    QDBusPendingReply<QString> reply = d->m_inter->asyncCall(QStringLiteral("CanSuspendThenHibernate"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return reply.value();
}

bool DLoginManager::cancelScheduledShutdown()
{
    Q_D(DLoginManager);
    QDBusPendingReply<bool> reply = d->m_inter->asyncCall(QStringLiteral("CancelScheduledShutdown"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return false;
    }
    return reply.value();
}

std::tuple<QString,     // sessionId
    QString,        // path
    QString,        // runtime_path
    int,            // fifo_fd
    uint,           // uid
    QString,        // seatId
    uint,           // VTNr
    bool            // existing
    > DLoginManager::createSession(uint uid, uint pid, const QString &service, const QString &type,
        const QString &_class, const QString &desktop, const QString &seatId,
        uint VTNr, const QString &TTY, const QString &display, const QString &remote,
        const QString &remoteUser, const QString &remoteHost, const QList<SessionProperty> &properties)
{
    Q_D(DLoginManager);
    QList<SessionProperty_p> properties_p;
    for (auto && property : properties) {
        SessionProperty_p property_p;
        property_p.name = property.name;
        property_p.var.setVariant(property.var);
        properties_p.append(property_p);
    }
    QVariantList args;
    args << QVariant::fromValue(uid) << QVariant::fromValue(pid) << QVariant::fromValue(service) << QVariant::fromValue(type)
        << QVariant::fromValue(_class) << QVariant::fromValue(desktop) << QVariant::fromValue(seatId)
        << QVariant::fromValue(VTNr) << QVariant::fromValue(TTY) << QVariant::fromValue(display) << QVariant::fromValue(remote)
        << QVariant::fromValue(remoteUser) << QVariant::fromValue(remoteHost) << QVariant::fromValue(properties_p);
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

void DLoginManager::flushDevices(const bool value)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("flushDevices"), {QVariant::fromValue(value)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

QString DLoginManager::getSeat(const QString &seatId)
{
    Q_D(DLoginManager);
    QDBusPendingReply<QDBusObjectPath> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("GetSeat"),
        {QVariant::fromValue(seatId)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return reply.value().path();
}

QString DLoginManager::getSession(const QString &sessionId)
{
    Q_D(DLoginManager);
    QDBusPendingReply<QDBusObjectPath> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("GetSession"),
        {QVariant::fromValue(sessionId)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return reply.value().path();
}

QString DLoginManager::getSessionByPID(const uint pid)
{
    Q_D(DLoginManager);
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

QString DLoginManager::getUser(const uint UID)
{
    Q_D(DLoginManager);
    QDBusPendingReply<QDBusObjectPath> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("GetUser"),
        {QVariant::fromValue(UID)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return QString();
    }
    return reply.value().path();
}

QString DLoginManager::getUserByPID(const uint pid)
{
    Q_D(DLoginManager);
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

void DLoginManager::halt(const bool interactive)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList("Halt", {QVariant::fromValue(interactive)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLoginManager::haltWithFlags(const quint64 flags)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList("HaltWithFlags", {QVariant::fromValue(flags)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLoginManager::hibernate(const bool interactive)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList("Hibernate", {QVariant::fromValue(interactive)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLoginManager::hibernateWithFlags(const quint64 flags)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList("HibernateWithFlags", {QVariant::fromValue(flags)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLoginManager::hybridSleep(const bool interactive)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList("HybridSleep", {QVariant::fromValue(interactive)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLoginManager::hybridSleepWithFlags(const quint64 flags)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList("HybridSleepWithFlags", {QVariant::fromValue(flags)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

int DLoginManager::inhibit(const QString &what, const QString &who, const QString &why, const QString &mode)
{
    Q_D(DLoginManager);
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

void DLoginManager::killSession(const QString &sessionId, const QString &who, const int signalNumber)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList("KillSession",
        {QVariant::fromValue(sessionId), QVariant::fromValue(who), QVariant::fromValue(signalNumber)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLoginManager::killUser(const uint uid, const int signalNumber)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("KillUser"),
        {QVariant::fromValue(uid), QVariant::fromValue(signalNumber)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

QList<Inhibitor> DLoginManager::listInhibitors()
{
    Q_D(DLoginManager);
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

QList<Seat> DLoginManager::listSeats()
{
    Q_D(DLoginManager);
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
        seat.seatId = seat_p.seatId;
        seat.path = seat_p.path.path();
        seats.append(seat);
    }
    return seats;
}

QList<Session> DLoginManager::listSessions()
{
    Q_D(DLoginManager);
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
        session.seatId = session_p.seatId;
        session.sessionId = session_p.sessionId;
        session.userId = session_p.userId;
        session.userName = session_p.userName;
        sessions.append(session);
    }
    return sessions;
}

QList<User> DLoginManager::listUsers()
{
    Q_D(DLoginManager);
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
        user.userName = user_p.userName;
        user.userId = user_p.userId;
        user.path = user_p.path.path();
        users.append(user);
    }
    return users;
}

void DLoginManager::lockSession(const QString &sessionId)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("LockSession"),
        {QVariant::fromValue(sessionId)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLoginManager::lockSessions()
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->asyncCall(QStringLiteral("LockSessions"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLoginManager::powerOff(const bool interactive)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("PowerOff"),
        {QVariant::fromValue(interactive)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLoginManager::powerOffWithFlags(const quint64 flags)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList("PowerOffWithFlags", {QVariant::fromValue(flags)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLoginManager::reboot(const bool interactive)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("Reboot"),
        {QVariant::fromValue(interactive)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLoginManager::rebootWithFlags(const quint64 flags)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList("RebootWithFlags", {QVariant::fromValue(flags)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLoginManager::releaseSession(const QString &sessionId)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("ReleaseSession"),
        {QVariant::fromValue(sessionId)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLoginManager::setRebootParameter(const QString &parameter)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("SetRebootParameter"),
        {QVariant::fromValue(parameter)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLoginManager::scheduleShutdown(const QString &type, const quint64 usec)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("ScheduleShutdown"),
        {QVariant::fromValue(type), QVariant::fromValue(usec)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLoginManager::setRebootToBootLoaderEntry(const QString &entry)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("SetRebootToBootLoaderEntry"),
        {QVariant::fromValue(entry)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLoginManager::setRebootToBootLoaderMenu(const quint64 timeout)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("SetRebootToBootLoaderMenu"),
        {QVariant::fromValue(timeout)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLoginManager::setRebootToFirmwareSetup(const bool enable)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("SetRebootToFirmwareSetup"),
        {QVariant::fromValue(enable)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLoginManager::setUserLinger(const uint UID, const bool enable, const bool interactive)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("SetUserLinger"),
        {QVariant::fromValue(UID), QVariant::fromValue(enable), QVariant::fromValue(interactive)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLoginManager::setWallMessage(const QString &message, const bool enable)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("SetWallMessage"),
        {QVariant::fromValue(message), QVariant::fromValue(enable)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLoginManager::suspend(const bool interactive)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("Suspend"),
        {QVariant::fromValue(interactive)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLoginManager::suspendThenHibernate(const bool interactive)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("SuspendThenHibernate"),
        {QVariant::fromValue(interactive)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLoginManager::suspendThenHibernateWithFlags(const quint64 flags)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList("SuspendThenHibernateWithFlags", {QVariant::fromValue(flags)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLoginManager::suspendWithFlags(const quint64 flags)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList("SuspendWithFlags", {QVariant::fromValue(flags)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLoginManager::terminateSeat(const QString &seatId)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("TerminateSeat"),
        {QVariant::fromValue(seatId)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLoginManager::terminateSession(const QString &sessionId)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("TerminateSession"),
        {QVariant::fromValue(sessionId)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLoginManager::terminateUser(const uint uid)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("TerminateUser"),
        {QVariant::fromValue(uid)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLoginManager::unlockSession(const QString &sessionId)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList(QStringLiteral("UnlockSession"),
        {QVariant::fromValue(sessionId)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

void DLoginManager::unlockSessions()
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->asyncCall(QStringLiteral("UnlockSessions"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}
DLOGIN_END_NAMESPACE

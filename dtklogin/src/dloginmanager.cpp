// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dloginmanager.h"
#include "dloginmanager_p.h"

#include <qdbusextratypes.h>
#include <qdbuspendingreply.h>
#include <qglobal.h>
#include <qlist.h>
#include <qstringliteral.h>
#include <qdebug.h>
#include <qdbusconnection.h>

#include "login1managerinterface.h"

DLOGIN_BEGIN_NAMESPACE
DLoginManager::DLoginManager(QObject *parent)
    : QObject(parent)
    , d_ptr(new DLoginManagerPrivate(this))
{
    const QString &Service   = QStringLiteral("org.freedesktop.login1");
    const QString &Path      = QStringLiteral("/org/freedesktop/login1");

    Q_D(DLoginManager);
    DBusScheduledShutdownValue::registerMetaType();
    DBusSessionProperty::registerMetaType();
    DBusInhibitor::registerMetaType();
    DBusSeat::registerMetaType();
    DBusSession::registerMetaType();
    DBusUser::registerMetaType();
    d->m_inter = new Login1ManagerInterface(Service, Path, QDBusConnection::systemBus(), d);
    connect(d->m_inter, &Login1ManagerInterface::prepareForShutdown, this, &DLoginManager::prepareForShutdown);
    connect(d->m_inter, &Login1ManagerInterface::prepareForSleep, this, &DLoginManager::prepareForSleep);
    connect(d->m_inter, &Login1ManagerInterface::seatNew, this, [=](const QString &seatId, const QString &seatPath) {
        Q_UNUSED(seatPath)
        emit this->seatNew(seatId);
    });
    connect(d->m_inter, &Login1ManagerInterface::seatRemoved, this, [=](const QString &seatId, const QString &seatPath){
        Q_UNUSED(seatPath)
        emit this->seatRemoved(seatId);
    });
    connect(d->m_inter, &Login1ManagerInterface::sessionNew, this, [=](const QString &sessionId, const QString &sessionPath) {
        Q_UNUSED(sessionPath)
        emit this->sessionNew(sessionId);
    });
    connect(d->m_inter, &Login1ManagerInterface::sessionRemoved, this, [=](const QString &sessionId, const QString &sessionPath) {
        Q_UNUSED(sessionPath)
        emit this->sessionRemoved(sessionId);
    });
    connect(d->m_inter, &Login1ManagerInterface::userNew, this, [=](const uint UID, const QString &userPath) {
        Q_UNUSED(userPath)
        emit this->userNew(UID);
    });
    connect(d->m_inter, &Login1ManagerInterface::userRemoved, this, [=](const uint UID, const QString &userPath) {
        Q_UNUSED(userPath);
        emit this->userRemoved(UID);
    });
}

DLoginManager::~DLoginManager() = default;

// properties

QStringList DLoginManager::bootLoaderEntries() const
{
    Q_D(const DLoginManager);
    return d->m_inter->bootLoaderEntries();
}

QStringList DLoginManager::killExcludeUsers() const
{
    Q_D(const DLoginManager);
    return d->m_inter->killExcludeUsers();
}

QStringList DLoginManager::killOnlyUsers() const
{
    Q_D(const DLoginManager);
    return d->m_inter->killOnlyUsers();
}

bool DLoginManager::docked() const
{
    Q_D(const DLoginManager);
    return d->m_inter->docked();
}

bool DLoginManager::enableWallMessages() const
{
    Q_D(const DLoginManager);
    return d->m_inter->enableWallMessages();
}

void DLoginManager::setEnableWallMessages(const bool enable)
{
    Q_D(const DLoginManager);
    d->m_inter->setEnableWallMessages(enable);
}

bool DLoginManager::idleHint() const
{
    Q_D(const DLoginManager);
    return d->m_inter->idleHint();
}

bool DLoginManager::killUserProcesses() const
{
    Q_D(const DLoginManager);
    return d->m_inter->killUserProcesses();
}

bool DLoginManager::lidClosed() const
{
    Q_D(const DLoginManager);
    return d->m_inter->lidClosed();
}

bool DLoginManager::onExternalPower() const
{
    Q_D(const DLoginManager);
    return d->m_inter->onExternalPower();
}

bool DLoginManager::preparingForShutdown() const
{
    Q_D(const DLoginManager);
    return d->m_inter->preparingForShutdown();
}

bool DLoginManager::preparingForSleep() const
{
    Q_D(const DLoginManager);
    return d->m_inter->preparingForSleep();
}

bool DLoginManager::rebootToFirmwareSetup() const
{
    Q_D(const DLoginManager);
    return d->m_inter->rebootToFirmwareSetup();
}

bool DLoginManager::removeIPC() const
{
    Q_D(const DLoginManager);
    return d->m_inter->removeIPC();
}

QString DLoginManager::blockInhibited() const
{
    Q_D(const DLoginManager);
    return d->m_inter->blockInhibited();
}

QString DLoginManager::delayInhibited() const
{
    Q_D(const DLoginManager);
    return d->m_inter->delayInhibited();
}

QString DLoginManager::handleHibernateKey() const
{
    Q_D(const DLoginManager);
    return d->m_inter->handleHibernateKey();
}

QString DLoginManager::handleLidSwitch() const
{
    Q_D(const DLoginManager);
    return d->m_inter->handleLidSwitch();
}

QString DLoginManager::handleLidSwitchDocked() const
{
    Q_D(const DLoginManager);
    return d->m_inter->handleLidSwitchDocked();
}

QString DLoginManager::handleLidSwitchExternalPower() const
{
    Q_D(const DLoginManager);
    return d->m_inter->handleLidSwitchExternalPower();
}

QString DLoginManager::handlePowerKey() const
{
    Q_D(const DLoginManager);
    return d->m_inter->handlePowerKey();
}

QString DLoginManager::handleSuspendKey() const
{
    Q_D(const DLoginManager);
    return d->m_inter->handleSuspendKey();
}

QString DLoginManager::idleAction() const
{
    Q_D(const DLoginManager);
    return d->m_inter->idleAction();
}

QString DLoginManager::rebootParameter() const
{
    Q_D(const DLoginManager);
    return d->m_inter->rebootParameter();
}

QString DLoginManager::rebootToBootLoaderEntry() const
{
    Q_D(const DLoginManager);
    return d->m_inter->rebootToBootLoaderEntry();
}

QString DLoginManager::wallMessage() const
{
    Q_D(const DLoginManager);
    return d->m_inter->wallMessage();
}

void DLoginManager::setWallMessage(const QString &message)
{
    Q_D(DLoginManager);
    d->m_inter->setWallMessage(message);
}

ScheduledShutdownValue DLoginManager::scheduledShutdown() const
{
    Q_D(const DLoginManager);
    const auto            &result = d->m_inter->scheduledShutdown();
    ScheduledShutdownValue value;
    value.type = result.type;
    value.usec = result.usec;
    return value;
}

quint32 DLoginManager::nAutoVTs() const
{
    Q_D(const DLoginManager);
    return d->m_inter->nAutoVTs();
}

quint64 DLoginManager::holdoffTimeoutUSec() const
{
    Q_D(const DLoginManager);
    return d->m_inter->holdoffTimeoutUSec();
}

quint64 DLoginManager::idleActionUSec() const
{
    Q_D(const DLoginManager);
    return d->m_inter->idleActionUSec();
}

quint64 DLoginManager::idleSinceHint() const
{
    Q_D(const DLoginManager);
    return d->m_inter->idleSinceHint();
}

quint64 DLoginManager::idleSinceHintMonotonic() const
{
    Q_D(const DLoginManager);
    return d->m_inter->idleSinceHintMonotonic();
}

quint64 DLoginManager::inhibitDelayMaxUSec() const
{
    Q_D(const DLoginManager);
    return d->m_inter->inhibitDelayMaxUSec();
}

quint64 DLoginManager::inhibitorsMax() const
{
    Q_D(const DLoginManager);
    return d->m_inter->inhibitorsMax();
}

quint64 DLoginManager::nCurrentInhibitors() const
{
    Q_D(const DLoginManager);
    return d->m_inter->nCurrentInhibitors();
}

quint64 DLoginManager::nCurrentSessions() const
{
    Q_D(const DLoginManager);
    return d->m_inter->nCurrentSessions();
}

quint64 DLoginManager::rebootToBootLoaderMenu() const
{
    Q_D(const DLoginManager);
    return d->m_inter->rebootToBootLoaderMenu();
}

quint64 DLoginManager::runtimeDirectoryInodesMax() const
{
    Q_D(const DLoginManager);
    return d->m_inter->runtimeDirectoryInodesMax();
}

quint64 DLoginManager::runtimeDirectorySize() const
{
    Q_D(const DLoginManager);
    return d->m_inter->runtimeDirectorySize();
}

quint64 DLoginManager::sessionsMax() const
{
    Q_D(const DLoginManager);
    return d->m_inter->sessionsMax();
}

quint64 DLoginManager::userStopDelayUSec() const
{
    Q_D(const DLoginManager);
    return d->m_inter->userStopDelayUSec();
}

// public slots

void DLoginManager::activateSession(const QString &sessionId)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->activateSession(sessionId);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DLoginManager::activateSessionOnSeat(const QString &sessionId, const QString &seatId)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->activateSessionOnSeat(sessionId, seatId);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DLoginManager::attachDevice(const QString &seatId, const QString &sysfsPath, const bool interactive)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->attachDevice(seatId, sysfsPath, interactive);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

QString DLoginManager::canHalt()
{
    Q_D(DLoginManager);
    QDBusPendingReply<QString> reply = d->m_inter->canHalt();
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return {};
    }
    return reply.value();
}

QString DLoginManager::canHibernate()
{
    Q_D(DLoginManager);
    QDBusPendingReply<QString> reply = d->m_inter->canHibernate();
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return {};
    }
    return reply.value();
}

QString DLoginManager::canHybridSleep()
{
    Q_D(DLoginManager);
    QDBusPendingReply<QString> reply = d->m_inter->canHybridSleep();
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return {};
    }
    return reply.value();
}

QString DLoginManager::canPowerOff()
{
    Q_D(DLoginManager);
    QDBusPendingReply<QString> reply = d->m_inter->canPowerOff();
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return {};
    }
    return reply.value();
}

QString DLoginManager::canReboot()
{
    Q_D(DLoginManager);
    QDBusPendingReply<QString> reply = d->m_inter->canReboot();
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return {};
    }
    return reply.value();
}

QString DLoginManager::canRebootParameter()
{
    Q_D(DLoginManager);
    QDBusPendingReply<QString> reply = d->m_inter->canRebootParameter();
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return {};
    }
    return reply.value();
}

QString DLoginManager::canRebootToBootLoaderEntry()
{
    Q_D(DLoginManager);
    QDBusPendingReply<QString> reply = d->m_inter->canRebootToBootLoaderEntry();
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return {};
    }
    return reply.value();
}

QString DLoginManager::canRebootToBootLoaderMenu()
{
    Q_D(DLoginManager);
    QDBusPendingReply<QString> reply = d->m_inter->canRebootToBootLoaderMenu();
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return {};
    }
    return reply.value();
}

QString DLoginManager::canRebootToFirmwareSetup()
{
    Q_D(DLoginManager);
    QDBusPendingReply<QString> reply = d->m_inter->canRebootToFirmwareSetup();
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return {};
    }
    return reply.value();
}

QString DLoginManager::canSuspend()
{
    Q_D(DLoginManager);
    QDBusPendingReply<QString> reply = d->m_inter->canSuspend();
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return {};
    }
    return reply.value();
}

QString DLoginManager::canSuspendThenHibernate()
{
    Q_D(DLoginManager);
    QDBusPendingReply<QString> reply = d->m_inter->canSuspendThenHibernate();
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return {};
    }
    return reply.value();
}

bool DLoginManager::cancelScheduledShutdown()
{
    Q_D(DLoginManager);
    QDBusPendingReply<bool> reply = d->m_inter->cancelScheduledShutdown();
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return false;
    }
    return reply.value();
}

void DLoginManager::flushDevices(const bool value)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply =
        d->m_inter->flushDevices(value);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

QString DLoginManager::getSeat(const QString &seatId)
{
    Q_D(DLoginManager);
    QDBusPendingReply<QDBusObjectPath> reply =
        d->m_inter->getSeat(seatId);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return {};
    }
    return reply.value().path();
}

QString DLoginManager::getSession(const QString &sessionId)
{
    Q_D(DLoginManager);
    QDBusPendingReply<QDBusObjectPath> reply =
        d->m_inter->getSession(sessionId);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return {};
    }
    return reply.value().path();
}

QString DLoginManager::getSessionByPID(const uint pid)
{
    Q_D(DLoginManager);
    QDBusPendingReply<QDBusObjectPath> reply =
        d->m_inter->getSessionByPID(pid);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return {};
    }
    return reply.value().path();
}

QString DLoginManager::getUser(const uint UID)
{
    Q_D(DLoginManager);
    QDBusPendingReply<QDBusObjectPath> reply =
        d->m_inter->getUser(UID);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return {};
    }
    return reply.value().path();
}

QString DLoginManager::getUserByPID(const uint pid)
{
    Q_D(DLoginManager);
    QDBusPendingReply<QDBusObjectPath> reply =
        d->m_inter->getUserByPID(pid);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return {};
    }
    return reply.value().path();
}

void DLoginManager::halt(const bool interactive)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->halt(interactive);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DLoginManager::haltWithFlags(const quint64 flags)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->haltWithFlags(flags);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DLoginManager::hibernate(const bool interactive)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->hibernate(interactive);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DLoginManager::hibernateWithFlags(const quint64 flags)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->hibernateWithFlags(flags);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DLoginManager::hybridSleep(const bool interactive)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->hybridSleep(interactive);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DLoginManager::hybridSleepWithFlags(const quint64 flags)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->hybridSleepWithFlags(flags);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

int DLoginManager::inhibit(const QString &what, const QString &who, const QString &why, const QString &mode)
{
    Q_D(DLoginManager);
    QDBusPendingReply<int> reply = d->m_inter->inhibit(what, who, why, mode);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return -1;
    }
    return reply.value();
}

void DLoginManager::killSession(const QString &sessionId, const QString &who, const int signalNumber)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->killSession(sessionId, who, signalNumber);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DLoginManager::killUser(const uint uid, const int signalNumber)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->killUser(uid, signalNumber);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

QList<Inhibitor> DLoginManager::listInhibitors()
{
    Q_D(DLoginManager);
    QDBusPendingReply<QList<DBusInhibitor>> reply = d->m_inter->listInhibitors();
    reply.waitForFinished();
    QList<Inhibitor> inhibitors;
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return inhibitors;
    }

    for (auto &&inhibitor_p : reply.value()) {
        Inhibitor inhibitor;
        inhibitor.mode = inhibitor_p.mode;
        inhibitor.pid  = inhibitor_p.pid;
        inhibitor.uid  = inhibitor_p.uid;
        inhibitor.what = inhibitor_p.what;
        inhibitor.who  = inhibitor_p.who;
        inhibitor.why  = inhibitor_p.why;
        inhibitors.append(inhibitor);
    }
    return inhibitors;
}

QList<QString> DLoginManager::listSeats()
{
    Q_D(DLoginManager);
    QDBusPendingReply<QList<DBusSeat>> reply = d->m_inter->listSeats();
    reply.waitForFinished();
    QList<QString> seats;
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return seats;
    }
    for (auto &&seat_p : reply.value()) {
        seats.append(seat_p.seatId);
    }
    return seats;
}

QList<QString> DLoginManager::listSessions()
{
    Q_D(DLoginManager);
    QDBusPendingReply<QList<DBusSession>> reply = d->m_inter->listSessions();
    reply.waitForFinished();
    QList<QString> sessions;
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return sessions;
    }
    for (auto &&session_p : reply.value()) {
        sessions.append(session_p.sessionId);
    }
    return sessions;
}

QList<quint32> DLoginManager::listUsers()
{
    Q_D(DLoginManager);
    QDBusPendingReply<QList<DBusUser>> reply = d->m_inter->listUsers();
    reply.waitForFinished();
    QList<quint32> users;
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return users;
    }
    for (auto &&user_p : reply.value()) {
        users.append(user_p.userId);
    }
    return users;
}

void DLoginManager::lockSession(const QString &sessionId)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply =
        d->m_inter->lockSession(sessionId);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DLoginManager::lockSessions()
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->lockSessions();
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DLoginManager::powerOff(const bool interactive)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply =
        d->m_inter->powerOff(interactive);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DLoginManager::powerOffWithFlags(const quint64 flags)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->powerOffWithFlags(flags);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DLoginManager::reboot(const bool interactive)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply =
        d->m_inter->reboot(interactive);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DLoginManager::rebootWithFlags(const quint64 flags)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->rebootWithFlags(flags);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DLoginManager::releaseSession(const QString &sessionId)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply =
        d->m_inter->releaseSession(sessionId);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DLoginManager::setRebootParameter(const QString &parameter)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply =
        d->m_inter->setRebootParameter(parameter);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DLoginManager::scheduleShutdown(const QString &type, const quint64 usec)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->scheduleShutdown(type, usec);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DLoginManager::setRebootToBootLoaderEntry(const QString &entry)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply =
        d->m_inter->setRebootToBootLoaderEntry(entry);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DLoginManager::setRebootToBootLoaderMenu(const quint64 timeout)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply =
        d->m_inter->setRebootToBootLoaderMenu(timeout);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DLoginManager::setRebootToFirmwareSetup(const bool enable)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply =
        d->m_inter->setRebootToFirmwareSetup(enable);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DLoginManager::setUserLinger(const uint UID, const bool enable, const bool interactive)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->setUserLinger(UID, enable, interactive);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}


void DLoginManager::suspend(const bool interactive)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply =
        d->m_inter->suspend(interactive);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DLoginManager::suspendThenHibernate(const bool interactive)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply =
        d->m_inter->suspendThenHibernate(interactive);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DLoginManager::suspendThenHibernateWithFlags(const quint64 flags)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply =
        d->m_inter->suspendThenHibernateWithFlags(flags);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DLoginManager::suspendWithFlags(const quint64 flags)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->suspendWithFlags(flags);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DLoginManager::terminateSeat(const QString &seatId)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply =
        d->m_inter->terminateSeat(seatId);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DLoginManager::terminateSession(const QString &sessionId)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply =
        d->m_inter->terminateSession(sessionId);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DLoginManager::terminateUser(const uint uid)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply =
        d->m_inter->terminateUser(QString::number(uid));
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DLoginManager::unlockSession(const QString &sessionId)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply =
        d->m_inter->unlockSession(sessionId);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DLoginManager::unlockSessions()
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->unlockSessions();
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}
DLOGIN_END_NAMESPACE

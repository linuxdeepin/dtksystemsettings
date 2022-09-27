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
#include <qdatetime.h>

#include "login1managerinterface.h"
#include "dloginseat.h"
#include "dloginsession.h"
#include "dloginuser.h"
#include "dloginutils.h"

DLOGIN_BEGIN_NAMESPACE
DLoginManager::DLoginManager(QObject *parent)
    : QObject(parent)
    , d_ptr(new DLoginManagerPrivate(this))
{
#if defined(USE_FAKE_INTERFACE)  // for unit test
    const QString &Service = QStringLiteral("org.freedesktop.fakelogin1");
    const QString &Path = QStringLiteral("/org/freedesktop/login1/manager");
    QDBusConnection connection = QDBusConnection::sessionBus();
#else
    const QString &Service = QStringLiteral("org.freedesktop.login1");
    const QString &Path = QStringLiteral("/org/freedesktop/login1");
    QDBusConnection connection = QDBusConnection::systemBus();
#endif
    Q_D(DLoginManager);
    DBusScheduledShutdownValue::registerMetaType();
    DBusSessionProperty::registerMetaType();
    DBusInhibitor::registerMetaType();
    DBusSeat::registerMetaType();
    DBusSession::registerMetaType();
    DBusUser::registerMetaType();
    d->m_inter = new Login1ManagerInterface(Service, Path, connection, d);
    connect(d->m_inter, &Login1ManagerInterface::prepareForShutdown, this, &DLoginManager::prepareForShutdown);
    connect(d->m_inter, &Login1ManagerInterface::prepareForSleep, this, &DLoginManager::prepareForSleep);
    connect(d->m_inter, &Login1ManagerInterface::seatNew, this, [=](const QString &seatId, const QString &seatPath) {
        Q_UNUSED(seatPath)
        emit this->seatNew(seatId);
    });
    connect(d->m_inter, &Login1ManagerInterface::seatRemoved, this, [=](const QString &seatId, const QString &seatPath) {
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
        Q_UNUSED(userPath)
        emit this->userRemoved(UID);
    });
}

DLoginManager::~DLoginManager() = default;

// properties

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

PowerAction DLoginManager::handleHibernateKey() const
{
    Q_D(const DLoginManager);
    return Utils::stringToAction(d->m_inter->handleHibernateKey());
}

PowerAction DLoginManager::handleLidSwitch() const
{
    Q_D(const DLoginManager);
    return Utils::stringToAction(d->m_inter->handleLidSwitch());
}

PowerAction DLoginManager::handleLidSwitchDocked() const
{
    Q_D(const DLoginManager);
    return Utils::stringToAction(d->m_inter->handleLidSwitchDocked());
}

PowerAction DLoginManager::handleLidSwitchExternalPower() const
{
    Q_D(const DLoginManager);
    return Utils::stringToAction(d->m_inter->handleLidSwitchExternalPower());
}

PowerAction DLoginManager::handlePowerKey() const
{
    Q_D(const DLoginManager);
    return Utils::stringToAction(d->m_inter->handlePowerKey());
}

PowerAction DLoginManager::handleSuspendKey() const
{
    Q_D(const DLoginManager);
    return Utils::stringToAction(d->m_inter->handleSuspendKey());
}

PowerAction DLoginManager::idleAction() const
{
    Q_D(const DLoginManager);
    return Utils::stringToAction(d->m_inter->idleAction());
}

ScheduledShutdownValue DLoginManager::scheduledShutdown() const
{
    Q_D(const DLoginManager);
    const auto &result = d->m_inter->scheduledShutdown();
    ScheduledShutdownValue value;
    value.type = Utils::stringToShutdownType(result.type);
    value.time = QDateTime::fromMSecsSinceEpoch(result.usec);
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

QDateTime DLoginManager::idleSinceHint() const
{
    Q_D(const DLoginManager);
    return QDateTime::fromMSecsSinceEpoch(d->m_inter->idleSinceHint());
}

QDateTime DLoginManager::idleSinceHintMonotonic() const
{
    Q_D(const DLoginManager);
    return QDateTime::fromMSecsSinceEpoch(d->m_inter->idleSinceHintMonotonic());
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

ExecuteStatus DLoginManager::canHalt()
{
    Q_D(DLoginManager);
    QDBusPendingReply<QString> reply = d->m_inter->canHalt();
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return {};
    }
    return Utils::stringToStatus(reply.value());
}

ExecuteStatus DLoginManager::canHibernate()
{
    Q_D(DLoginManager);
    QDBusPendingReply<QString> reply = d->m_inter->canHibernate();
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return {};
    }
    return Utils::stringToStatus(reply.value());
}

ExecuteStatus DLoginManager::canHybridSleep()
{
    Q_D(DLoginManager);
    QDBusPendingReply<QString> reply = d->m_inter->canHybridSleep();
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return {};
    }
    return Utils::stringToStatus(reply.value());
}

ExecuteStatus DLoginManager::canPowerOff()
{
    Q_D(DLoginManager);
    QDBusPendingReply<QString> reply = d->m_inter->canPowerOff();
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return {};
    }
    return Utils::stringToStatus(reply.value());
}

ExecuteStatus DLoginManager::canReboot()
{
    Q_D(DLoginManager);
    QDBusPendingReply<QString> reply = d->m_inter->canReboot();
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return {};
    }
    return Utils::stringToStatus(reply.value());
}

ExecuteStatus DLoginManager::canSuspend()
{
    Q_D(DLoginManager);
    QDBusPendingReply<QString> reply = d->m_inter->canSuspend();
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return {};
    }
    return Utils::stringToStatus(reply.value());
}

ExecuteStatus DLoginManager::canSuspendThenHibernate()
{
    Q_D(DLoginManager);
    QDBusPendingReply<QString> reply = d->m_inter->canSuspendThenHibernate();
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return {};
    }
    return Utils::stringToStatus(reply.value());
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

QSharedPointer<DLoginSeat> DLoginManager::findSeatById(const QString &seatId)
{
    Q_D(DLoginManager);
    QDBusPendingReply<QDBusObjectPath> reply = d->m_inter->getSeat(seatId);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return {};
    }
    return QSharedPointer<DLoginSeat>(new DLoginSeat(reply.value().path()));
}

QSharedPointer<DLoginSession> DLoginManager::findSessionById(const QString &sessionId)
{
    Q_D(DLoginManager);
    QDBusPendingReply<QDBusObjectPath> reply = d->m_inter->getSession(sessionId);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return {};
    }
    return QSharedPointer<DLoginSession>(new DLoginSession(reply.value().path()));
}

QSharedPointer<DLoginSession> DLoginManager::findSessionByPID(const quint32 PID)
{
    Q_D(DLoginManager);
    QDBusPendingReply<QDBusObjectPath> reply = d->m_inter->getSessionByPID(PID);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return {};
    }
    return QSharedPointer<DLoginSession>(new DLoginSession(reply.value().path()));
}

QSharedPointer<DLoginUser> DLoginManager::findUserById(const quint32 UID)
{
    Q_D(DLoginManager);
    QDBusPendingReply<QDBusObjectPath> reply = d->m_inter->getUser(UID);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return {};
    }
    return QSharedPointer<DLoginUser>(new DLoginUser(reply.value().path()));
}

QSharedPointer<DLoginUser> DLoginManager::findUserByPID(const quint32 PID)
{
    Q_D(DLoginManager);
    QDBusPendingReply<QDBusObjectPath> reply = d->m_inter->getUserByPID(PID);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return {};
    }
    return QSharedPointer<DLoginUser>(new DLoginUser(reply.value().path()));
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

void DLoginManager::hibernate(const bool interactive)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->hibernate(interactive);
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

int DLoginManager::inhibit(const uint what, const QString &who, const QString &why, const InhibitMode &mode)
{
    Q_D(DLoginManager);
    QDBusPendingReply<int> reply = d->m_inter->inhibit(Utils::decodeBehavior(what), who, why, Utils::modeToString(mode));
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return -1;
    }
    return reply.value();
}

void DLoginManager::killSession(const QString &sessionId, const SessionRole &who, const qint32 signalNumber)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->killSession(sessionId, Utils::sessionRoleToString(who), signalNumber);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DLoginManager::killUser(const quint32 uid, const qint32 signalNumber)
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
        inhibitors.append(Utils::inhibitorFromDBus(inhibitor_p));
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
    QDBusPendingReply<> reply = d->m_inter->lockSession(sessionId);
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
    QDBusPendingReply<> reply = d->m_inter->powerOff(interactive);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DLoginManager::reboot(const bool interactive)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->reboot(interactive);
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

void DLoginManager::setUserLinger(const quint32 UID, const bool enable, const bool interactive)
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
    QDBusPendingReply<> reply = d->m_inter->suspend(interactive);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DLoginManager::suspendThenHibernate(const bool interactive)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->suspendThenHibernate(interactive);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DLoginManager::terminateSeat(const QString &seatId)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->terminateSeat(seatId);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DLoginManager::terminateSession(const QString &sessionId)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->terminateSession(sessionId);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DLoginManager::terminateUser(const quint32 uid)
{
    Q_D(DLoginManager);
    QDBusPendingReply<> reply = d->m_inter->terminateUser(QString::number(uid));
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DLoginManager::logout()
{
    QSharedPointer<DLoginSession> session = currentSession();
    session->terminate();
}

QSharedPointer<DLoginSeat> DLoginManager::currentSeat()
{
    DLoginSeat current(QStringLiteral("/org/freedesktop/login1/seat/self"));
    return QSharedPointer<DLoginSeat>(findSeatById(current.id()));
}
QSharedPointer<DLoginSession> DLoginManager::currentSession()
{
    DLoginSession current(QStringLiteral("/org/freedesktop/login1/session/self"));
    return QSharedPointer<DLoginSession>(findSessionById(current.id()));
}
QSharedPointer<DLoginUser> DLoginManager::currentUser()
{
    DLoginUser current(QStringLiteral("/org/freedesktop/login1/user/self"));
    return QSharedPointer<DLoginUser>(findUserById(current.UID()));
}
DLOGIN_END_NAMESPACE

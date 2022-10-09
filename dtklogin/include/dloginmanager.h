// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <qobject.h>
#include <qscopedpointer.h>
#include <qsharedpointer.h>

#include "dlogintypes.h"
#include "namespace.h"

DLOGIN_BEGIN_NAMESPACE

class DLoginManagerPrivate;
class DLoginSeat;
class DLoginUser;
class DLoginSession;

class DLoginManager : public QObject
{
    Q_OBJECT
public:
    explicit DLoginManager(QObject *parent = nullptr);
    ~DLoginManager() override;

    Q_PROPERTY(QStringList killExcludeUsers READ killExcludeUsers);
    Q_PROPERTY(QStringList killOnlyUsers READ killOnlyUsers);
    Q_PROPERTY(bool docked READ docked);
    Q_PROPERTY(bool idleHint READ idleHint);
    Q_PROPERTY(bool killUserProcesses READ killUserProcesses);
    Q_PROPERTY(bool lidClosed READ lidClosed);
    Q_PROPERTY(bool preparingForShutdown READ preparingForShutdown);
    Q_PROPERTY(bool preparingForSleep READ preparingForSleep);
    Q_PROPERTY(bool removeIPC READ removeIPC);
    Q_PROPERTY(QString blockInhibited READ blockInhibited);
    Q_PROPERTY(QString delayInhibited READ delayInhibited);
    Q_PROPERTY(PowerAction handleHibernateKey READ handleHibernateKey);
    Q_PROPERTY(PowerAction handleLidSwitch READ handleLidSwitch);
    Q_PROPERTY(PowerAction handleLidSwitchDocked READ handleLidSwitchDocked);
    Q_PROPERTY(PowerAction handleLidSwitchExternalPower READ handleLidSwitchExternalPower);
    Q_PROPERTY(PowerAction handlePowerKey READ handlePowerKey);
    Q_PROPERTY(PowerAction handleSuspendKey READ handleSuspendKey);
    Q_PROPERTY(PowerAction idleAction READ idleAction);
    Q_PROPERTY(ScheduledShutdownValue scheduledShutdown READ scheduledShutdown);
    Q_PROPERTY(quint32 nAutoVTs READ nAutoVTs);
    Q_PROPERTY(quint64 holdoffTimeoutUSec READ holdoffTimeoutUSec);
    Q_PROPERTY(quint64 idleActionUSec READ idleActionUSec);
    Q_PROPERTY(QDateTime idleSinceHint READ idleSinceHint);
    Q_PROPERTY(quint64 idleSinceHintMonotonic READ idleSinceHintMonotonic);
    Q_PROPERTY(quint64 inhibitDelayMaxUSec READ inhibitDelayMaxUSec);
    Q_PROPERTY(quint64 inhibitorsMax READ inhibitorsMax);
    Q_PROPERTY(quint64 nCurrentInhibitors READ nCurrentInhibitors);
    Q_PROPERTY(quint64 nCurrentSessions READ nCurrentSessions);
    Q_PROPERTY(quint64 runtimeDirectoryInodesMax READ runtimeDirectoryInodesMax);
    Q_PROPERTY(quint64 runtimeDirectorySize READ runtimeDirectorySize);
    Q_PROPERTY(quint64 sessionsMax READ sessionsMax);
    Q_PROPERTY(quint64 userStopDelayUSec READ userStopDelayUSec);

    QStringList killExcludeUsers() const;
    QStringList killOnlyUsers() const;
    bool docked() const;
    bool idleHint() const;
    bool killUserProcesses() const;
    bool lidClosed() const;
    bool preparingForShutdown() const;
    bool preparingForSleep() const;
    bool removeIPC() const;
    QString blockInhibited() const;
    QString delayInhibited() const;
    PowerAction handleHibernateKey() const;
    PowerAction handleLidSwitch() const;
    PowerAction handleLidSwitchDocked() const;
    PowerAction handleLidSwitchExternalPower() const;
    PowerAction handlePowerKey() const;
    PowerAction handleSuspendKey() const;
    PowerAction idleAction() const;
    ScheduledShutdownValue scheduledShutdown() const;
    quint32 nAutoVTs() const;
    quint64 holdoffTimeoutUSec() const;
    quint64 idleActionUSec() const;
    QDateTime idleSinceHint() const;
    quint64 idleSinceHintMonotonic() const;
    quint64 inhibitDelayMaxUSec() const;
    quint64 inhibitorsMax() const;
    quint64 nCurrentInhibitors() const;
    quint64 nCurrentSessions() const;
    quint64 runtimeDirectoryInodesMax() const;
    quint64 runtimeDirectorySize() const;
    quint64 sessionsMax() const;
    quint64 userStopDelayUSec() const;

signals:
    void prepareForShutdown(const bool value);
    void prepareForSleep(const bool value);
    void seatNew(const QString &seatId);
    void seatRemoved(const QString &seatId);
    void sessionNew(const QString &sessionId);
    void sessionRemoved(const QString &sessionId);
    void userNew(const quint32 UID);
    void userRemoved(const quint32 UID);

public slots:
    void activateSession(const QString &sessionId);
    void activateSessionOnSeat(const QString &sessionId, const QString &seatId);
    ExecuteStatus canHalt();
    ExecuteStatus canHibernate();
    ExecuteStatus canHybridSleep();
    ExecuteStatus canPowerOff();
    ExecuteStatus canReboot();
    ExecuteStatus canSuspend();
    ExecuteStatus canSuspendThenHibernate();
    bool cancelScheduledShutdown();
    QSharedPointer<DLoginSeat> findSeatById(const QString &seatId);
    QSharedPointer<DLoginSession> findSessionById(const QString &sessionId);
    QSharedPointer<DLoginSession> findSessionByPID(const quint32 PID);
    QSharedPointer<DLoginUser> findUserById(const quint32 UID);
    QSharedPointer<DLoginUser> findUserByPID(const quint32 PID);
    void halt(const bool interactive = false);
    void hibernate(const bool interactive = false);
    void hybridSleep(const bool interactive = false);
    int inhibit(int what, const QString &who, const QString &why, const InhibitMode &mode);
    void killSession(const QString &sessionId, const SessionRole &who, const qint32 signalNumber);
    void killUser(const quint32 uid, const qint32 signalNumber);
    QList<Inhibitor> listInhibitors();
    QList<QString> listSeats();
    QList<QString> listSessions();
    QList<quint32> listUsers();
    void lockSession(const QString &sessionId);
    void lockSessions();
    void powerOff(const bool interactive = false);
    void reboot(const bool interactive = false);
    void scheduleShutdown(const ShutdownType &type, const QDateTime &usec);
    void setUserLinger(const quint32 UID, const bool enable, const bool interactive);
    void suspend(const bool interactive = false);
    void suspendThenHibernate(const bool interactive = false);
    void terminateSession(const QString &sessionId);
    void terminateUser(const quint32 uid);
    void logout();
    QSharedPointer<DLoginSeat> currentSeat();
    QSharedPointer<DLoginSession> currentSession();
    QSharedPointer<DLoginUser> currentUser();

private:
    QScopedPointer<DLoginManagerPrivate> d_ptr;
    Q_DECLARE_PRIVATE(DLoginManager)
};
DLOGIN_END_NAMESPACE

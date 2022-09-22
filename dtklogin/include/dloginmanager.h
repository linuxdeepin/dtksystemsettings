// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <qobject.h>

#include <qscopedpointer.h>

#include "dlogintypes.h"
#include "namespace.h"

DLOGIN_BEGIN_NAMESPACE

class DLoginManagerPrivate;

class DLoginManager : public QObject
{
    Q_OBJECT
public:
    explicit DLoginManager(QObject *parent = nullptr);
    ~DLoginManager() override;

    Q_PROPERTY(QStringList bootLoaderEntries READ bootLoaderEntries);
    Q_PROPERTY(QStringList killExcludeUsers READ killExcludeUsers);
    Q_PROPERTY(QStringList killOnlyUsers READ killOnlyUsers);
    Q_PROPERTY(bool docked READ docked);
    Q_PROPERTY(bool enableWallMessages READ enableWallMessages WRITE setEnableWallMessages);
    Q_PROPERTY(bool idleHint READ idleHint);
    Q_PROPERTY(bool killUserProcesses READ killUserProcesses);
    Q_PROPERTY(bool lidClosed READ lidClosed);
    Q_PROPERTY(bool onExternalPower READ onExternalPower);
    Q_PROPERTY(bool preparingForShutdown READ preparingForShutdown);
    Q_PROPERTY(bool preparingForSleep READ preparingForSleep);
    Q_PROPERTY(bool rebootToFirmwareSetup READ rebootToFirmwareSetup);
    Q_PROPERTY(bool removeIPC READ removeIPC);
    Q_PROPERTY(QString blockInhibited READ blockInhibited);
    Q_PROPERTY(QString delayInhibited READ delayInhibited);
    Q_PROPERTY(QString handleHibernateKey READ handleHibernateKey);
    Q_PROPERTY(QString handleLidSwitch READ handleLidSwitch);
    Q_PROPERTY(QString handleLidSwitchDocked READ handleLidSwitchDocked);
    Q_PROPERTY(QString handleLidSwitchExternalPower READ handleLidSwitchExternalPower);
    Q_PROPERTY(QString handlePowerKey READ handlePowerKey);
    Q_PROPERTY(QString handleSuspendKey READ handleSuspendKey);
    Q_PROPERTY(QString idleAction READ idleAction);
    Q_PROPERTY(QString rebootParameter READ rebootParameter);
    Q_PROPERTY(QString rebootToBootLoaderEntry READ rebootToBootLoaderEntry);
    Q_PROPERTY(QString wallMessage READ wallMessage WRITE setWallMessage);
    Q_PROPERTY(ScheduledShutdownValue scheduledShutdown READ scheduledShutdown);
    Q_PROPERTY(quint32 nAutoVTs READ nAutoVTs);
    Q_PROPERTY(quint64 holdoffTimeoutUSec READ holdoffTimeoutUSec);
    Q_PROPERTY(quint64 idleActionUSec READ idleActionUSec);
    Q_PROPERTY(quint64 idleSinceHint READ idleSinceHint);
    Q_PROPERTY(quint64 idleSinceHintMonotonic READ idleSinceHintMonotonic);
    Q_PROPERTY(quint64 inhibitDelayMaxUSec READ inhibitDelayMaxUSec);
    Q_PROPERTY(quint64 inhibitorsMax READ inhibitorsMax);
    Q_PROPERTY(quint64 nCurrentInhibitors READ nCurrentInhibitors);
    Q_PROPERTY(quint64 nCurrentSessions READ nCurrentSessions);
    Q_PROPERTY(quint64 rebootToBootLoaderMenu READ rebootToBootLoaderMenu);
    Q_PROPERTY(quint64 runtimeDirectoryInodesMax READ runtimeDirectoryInodesMax);
    Q_PROPERTY(quint64 runtimeDirectorySize READ runtimeDirectorySize);
    Q_PROPERTY(quint64 sessionsMax READ sessionsMax);
    Q_PROPERTY(quint64 userStopDelayUSec READ userStopDelayUSec);

    QStringList bootLoaderEntries() const;
    QStringList killExcludeUsers() const;
    QStringList killOnlyUsers() const;
    bool docked() const;
    bool enableWallMessages() const;
    void setEnableWallMessages(const bool enable);
    bool idleHint() const;
    bool killUserProcesses() const;
    bool lidClosed() const;
    bool onExternalPower() const;
    bool preparingForShutdown() const;
    bool preparingForSleep() const;
    bool rebootToFirmwareSetup() const;
    bool removeIPC() const;
    QString blockInhibited() const;
    QString delayInhibited() const;
    QString handleHibernateKey() const;
    QString handleLidSwitch() const;
    QString handleLidSwitchDocked() const;
    QString handleLidSwitchExternalPower() const;
    QString handlePowerKey() const;
    QString handleSuspendKey() const;
    QString idleAction() const;
    QString rebootParameter() const;
    QString rebootToBootLoaderEntry() const;
    QString wallMessage() const;
    void setWallMessage(const QString &message);
    ScheduledShutdownValue scheduledShutdown() const;
    quint32 nAutoVTs() const;
    quint64 holdoffTimeoutUSec() const;
    quint64 idleActionUSec() const;
    quint64 idleSinceHint() const;
    quint64 idleSinceHintMonotonic() const;
    quint64 inhibitDelayMaxUSec() const;
    quint64 inhibitorsMax() const;
    quint64 nCurrentInhibitors() const;
    quint64 nCurrentSessions() const;
    quint64 rebootToBootLoaderMenu() const;
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
    void userNew(const uint UID);
    void userRemoved(const uint UID);

public slots:
    void activateSession(const QString &sessionId);
    void activateSessionOnSeat(const QString &sessionId, const QString &seatId);
    void attachDevice(const QString &seatId, const QString &sysfsPath, const bool interactive);
    QString canHalt();
    QString canHibernate();
    QString canHybridSleep();
    QString canPowerOff();
    QString canReboot();
    QString canRebootParameter();
    QString canRebootToBootLoaderEntry();
    QString canRebootToBootLoaderMenu();
    QString canRebootToFirmwareSetup();
    QString canSuspend();
    QString canSuspendThenHibernate();
    bool cancelScheduledShutdown();
    void flushDevices(const bool value);
    QString getSeat(const QString &seatId);
    QString getSession(const QString &sessionId);
    QString getSessionByPID(const uint pid);
    QString getUser(const uint UID);
    QString getUserByPID(const uint pid);
    void halt(const bool interactive);
    void haltWithFlags(const quint64 flags);
    void hibernate(const bool interactive);
    void hibernateWithFlags(const quint64 flags);
    void hybridSleep(const bool interactive);
    void hybridSleepWithFlags(const quint64 flags);
    int inhibit(const QString &what, const QString &who, const QString &why, const QString &mode);
    void killSession(const QString &sessionId, const QString &who, const int signalNumber);
    void killUser(const uint uid, const int signalNumber);
    QList<DLOGIN_NAMESPACE::Inhibitor> listInhibitors();
    QList<QString> listSeats();
    QList<QString> listSessions();
    QList<quint32> listUsers();
    void lockSession(const QString &sessionId);
    void lockSessions();
    void powerOff(const bool interactive);
    void powerOffWithFlags(const quint64 flags);
    void reboot(const bool interactive);
    void rebootWithFlags(const quint64 flags);
    void releaseSession(const QString &sessionId);
    void setRebootParameter(const QString &parameter);
    void scheduleShutdown(const QString &type, const quint64 usec);
    void setRebootToBootLoaderEntry(const QString &entry);
    void setRebootToBootLoaderMenu(const quint64 timeout);
    void setRebootToFirmwareSetup(const bool enable);
    void setUserLinger(const uint UID, const bool enable, const bool interactive);
    void suspend(const bool interactive);
    void suspendThenHibernate(const bool interactive);
    void suspendThenHibernateWithFlags(const quint64 flags);
    void suspendWithFlags(const quint64 flags);
    void terminateSeat(const QString &seatId);
    void terminateSession(const QString &sessionId);
    void terminateUser(const uint uid);
    void unlockSession(const QString &sessionId);
    void unlockSessions();

private:
    QScopedPointer<DLoginManagerPrivate> d_ptr;
    Q_DECLARE_PRIVATE(DLoginManager)
};
DLOGIN_END_NAMESPACE

// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "login1managerservice.h"

#include <QDBusObjectPath>
#include <qdbusunixfiledescriptor.h>
#include <qmetaobject.h>
#include <qbytearray.h>
#include <qlist.h>
#include <qmap.h>
#include <qstring.h>
#include <qstringlist.h>
#include <qvariant.h>
#include <qdbusconnection.h>
#include <qdebug.h>

#include "dlogintypes_p.h"
DLOGIN_BEGIN_NAMESPACE

/*
 * Implementation of adaptor class  Login1ManagerService
 */

Login1ManagerService::Login1ManagerService(QObject *parent)
    : QObject(parent)
{
    registerService();
}

void Login1ManagerService::registerService()
{
    bool success = false;
    const QString &FakeService = QStringLiteral("org.freedesktop.fakelogin1");
    const QString &ManagerPath = QStringLiteral("/org/freedesktop/login1/manager");
    success = QDBusConnection::sessionBus().registerService(FakeService);
    if (success) {
        qDebug() << "Successfully registered fake service org.freedesktop.freelogin1";
    } else {
        qCritical() << "Can't register fake service org.freedesktop.freelogin1";
    }
    success = QDBusConnection::sessionBus().registerObject(ManagerPath, this, QDBusConnection::ExportAllContents);
    if (success) {
        qDebug() << "Successfully registered object /org/freedesktop/login1/manager";
    } else {
        qCritical() << "Can't register object /org/freedesktop/login1/manager";
    }
}

QString Login1ManagerService::blockInhibited() const
{
    return m_blockInhibited;
}

QString Login1ManagerService::delayInhibited() const
{
    return m_delayInhibited;
}

bool Login1ManagerService::docked() const
{
    return m_docked;
}

QString Login1ManagerService::handleHibernateKey() const
{
    return m_handleHibernateKey;
}

QString Login1ManagerService::handleLidSwitch() const
{
    return m_handleLidSwitch;
}

QString Login1ManagerService::handleLidSwitchDocked() const
{
    return m_handleLidSwitchDocked;
}

QString Login1ManagerService::handleLidSwitchExternalPower() const
{
    return m_handleLidSwitchExternalPower;
}

QString Login1ManagerService::handlePowerKey() const
{
    return m_handlePowerKey;
}

QString Login1ManagerService::handleSuspendKey() const
{
    return m_handleSuspendKey;
}

quint64 Login1ManagerService::holdoffTimeoutUSec() const
{
    return m_holdoffTimeoutUSec;
}

QString Login1ManagerService::idleAction() const
{
    return m_idleAction;
}

quint64 Login1ManagerService::idleActionUSec() const
{
    return m_idleActionUSec;
}

bool Login1ManagerService::idleHint() const
{
    return m_idleHint;
}

quint64 Login1ManagerService::idleSinceHint() const
{
    return m_idleSinceHint;
}

quint64 Login1ManagerService::idleSinceHintMonotonic() const
{
    return m_idleSinceHintMonotonic;
}

quint64 Login1ManagerService::inhibitDelayMaxUSec() const
{
    return m_inhibitDelayMaxUSec;
}

quint64 Login1ManagerService::inhibitorsMax() const
{
    return m_inhibitorsMax;
}

QStringList Login1ManagerService::killExcludeUsers() const
{
    return m_killExcludeUsers;
}

QStringList Login1ManagerService::killOnlyUsers() const
{
    return m_killOnlyUsers;
}

bool Login1ManagerService::killUserProcesses() const
{
    return m_killUserProcesses;
}

bool Login1ManagerService::lidClosed() const
{
    return m_lidClosed;
}

quint32 Login1ManagerService::nAutoVTs() const
{
    return m_nAutoVTs;
}

quint64 Login1ManagerService::nCurrentInhibitors() const
{
    return m_nCurrentInhibitors;
}

quint64 Login1ManagerService::nCurrentSessions() const
{
    return m_nCurrentSessions;
}

bool Login1ManagerService::preparingForShutdown() const
{
    return m_preparingForShutdown;
}

bool Login1ManagerService::preparingForSleep() const
{
    return m_preparingForSleep;
}

bool Login1ManagerService::removeIPC() const
{
    return m_removeIPC;
}

quint64 Login1ManagerService::runtimeDirectoryInodesMax() const
{
    return m_runtimeDirectoryInodesMax;
}

quint64 Login1ManagerService::runtimeDirectorySize() const
{
    return m_runtimeDirectorySize;
}

DBusScheduledShutdownValue Login1ManagerService::scheduledShutdown() const
{
    return m_scheduledShutdown;
}

quint64 Login1ManagerService::sessionsMax() const
{
    return m_sessionsMax;
}

quint64 Login1ManagerService::userStopDelayUSec() const
{
    return m_userStopDelayUSec;
}

void Login1ManagerService::ActivateSession(const QString &session_id)
{
    // handle method call org.freedesktop.login1.Manager.ActivateSession
    QMetaObject::invokeMethod(parent(), "ActivateSession", Q_ARG(QString, session_id));
}

void Login1ManagerService::ActivateSessionOnSeat(const QString &session_id, const QString &seat_id)
{
    // handle method call org.freedesktop.login1.Manager.ActivateSessionOnSeat
    QMetaObject::invokeMethod(parent(), "ActivateSessionOnSeat", Q_ARG(QString, session_id), Q_ARG(QString, seat_id));
}

QString Login1ManagerService::CanHalt()
{
    // handle method call org.freedesktop.login1.Manager.CanHalt
    QString result;
    QMetaObject::invokeMethod(parent(), "CanHalt", Q_RETURN_ARG(QString, result));
    return result;
}

QString Login1ManagerService::CanHibernate()
{
    // handle method call org.freedesktop.login1.Manager.CanHibernate
    QString result;
    QMetaObject::invokeMethod(parent(), "CanHibernate", Q_RETURN_ARG(QString, result));
    return result;
}

QString Login1ManagerService::CanHybridSleep()
{
    // handle method call org.freedesktop.login1.Manager.CanHybridSleep
    QString result;
    QMetaObject::invokeMethod(parent(), "CanHybridSleep", Q_RETURN_ARG(QString, result));
    return result;
}

QString Login1ManagerService::CanPowerOff()
{
    // handle method call org.freedesktop.login1.Manager.CanPowerOff
    QString result;
    QMetaObject::invokeMethod(parent(), "CanPowerOff", Q_RETURN_ARG(QString, result));
    return result;
}

QString Login1ManagerService::CanReboot()
{
    // handle method call org.freedesktop.login1.Manager.CanReboot
    QString result;
    QMetaObject::invokeMethod(parent(), "CanReboot", Q_RETURN_ARG(QString, result));
    return result;
}

QString Login1ManagerService::CanSuspend()
{
    // handle method call org.freedesktop.login1.Manager.CanSuspend
    QString result;
    QMetaObject::invokeMethod(parent(), "CanSuspend", Q_RETURN_ARG(QString, result));
    return result;
}

QString Login1ManagerService::CanSuspendThenHibernate()
{
    // handle method call org.freedesktop.login1.Manager.CanSuspendThenHibernate
    QString result;
    QMetaObject::invokeMethod(parent(), "CanSuspendThenHibernate", Q_RETURN_ARG(QString, result));
    return result;
}

bool Login1ManagerService::CancelScheduledShutdown()
{
    // handle method call org.freedesktop.login1.Manager.CancelScheduledShutdown
    bool cancelled;
    QMetaObject::invokeMethod(parent(), "CancelScheduledShutdown", Q_RETURN_ARG(bool, cancelled));
    return cancelled;
}

QDBusObjectPath Login1ManagerService::GetSeat(const QString &seat_id)
{
    // handle method call org.freedesktop.login1.Manager.GetSeat
    QDBusObjectPath object_path;
    QMetaObject::invokeMethod(parent(), "GetSeat", Q_RETURN_ARG(QDBusObjectPath, object_path), Q_ARG(QString, seat_id));
    return object_path;
}

QDBusObjectPath Login1ManagerService::GetSession(const QString &session_id)
{
    // handle method call org.freedesktop.login1.Manager.GetSession
    QDBusObjectPath object_path;
    QMetaObject::invokeMethod(parent(), "GetSession", Q_RETURN_ARG(QDBusObjectPath, object_path), Q_ARG(QString, session_id));
    return object_path;
}

QDBusObjectPath Login1ManagerService::GetSessionByPID(quint32 pid)
{
    // handle method call org.freedesktop.login1.Manager.GetSessionByPID
    QDBusObjectPath object_path;
    QMetaObject::invokeMethod(parent(), "GetSessionByPID", Q_RETURN_ARG(QDBusObjectPath, object_path), Q_ARG(quint32, pid));
    return object_path;
}

QDBusObjectPath Login1ManagerService::GetUser(quint32 uid)
{
    // handle method call org.freedesktop.login1.Manager.GetUser
    QDBusObjectPath object_path;
    QMetaObject::invokeMethod(parent(), "GetUser", Q_RETURN_ARG(QDBusObjectPath, object_path), Q_ARG(quint32, uid));
    return object_path;
}

QDBusObjectPath Login1ManagerService::GetUserByPID(quint32 pid)
{
    // handle method call org.freedesktop.login1.Manager.GetUserByPID
    QDBusObjectPath object_path;
    QMetaObject::invokeMethod(parent(), "GetUserByPID", Q_RETURN_ARG(QDBusObjectPath, object_path), Q_ARG(quint32, pid));
    return object_path;
}

void Login1ManagerService::Halt(bool interactive)
{
    // handle method call org.freedesktop.login1.Manager.Halt
    QMetaObject::invokeMethod(parent(), "Halt", Q_ARG(bool, interactive));
}

void Login1ManagerService::Hibernate(bool interactive)
{
    // handle method call org.freedesktop.login1.Manager.Hibernate
    QMetaObject::invokeMethod(parent(), "Hibernate", Q_ARG(bool, interactive));
}

void Login1ManagerService::HybridSleep(bool interactive)
{
    // handle method call org.freedesktop.login1.Manager.HybridSleep
    QMetaObject::invokeMethod(parent(), "HybridSleep", Q_ARG(bool, interactive));
}

QDBusUnixFileDescriptor
Login1ManagerService::Inhibit(const QString &what, const QString &who, const QString &why, const QString &mode)
{
    // handle method call org.freedesktop.login1.Manager.Inhibit
    QDBusUnixFileDescriptor pipe_fd;
    QMetaObject::invokeMethod(parent(),
                              "Inhibit",
                              Q_RETURN_ARG(QDBusUnixFileDescriptor, pipe_fd),
                              Q_ARG(QString, what),
                              Q_ARG(QString, who),
                              Q_ARG(QString, why),
                              Q_ARG(QString, mode));
    return pipe_fd;
}

void Login1ManagerService::KillSession(const QString &session_id, const QString &who, qint32 signal_number)
{
    // handle method call org.freedesktop.login1.Manager.KillSession
    QMetaObject::invokeMethod(
        parent(), "KillSession", Q_ARG(QString, session_id), Q_ARG(QString, who), Q_ARG(qint32, signal_number));
}

void Login1ManagerService::KillUser(quint32 uid, qint32 signal_number)
{
    // handle method call org.freedesktop.login1.Manager.KillUser
    QMetaObject::invokeMethod(parent(), "KillUser", Q_ARG(quint32, uid), Q_ARG(qint32, signal_number));
}

DBusInhibitor Login1ManagerService::ListInhibitors()
{
    // handle method call org.freedesktop.login1.Manager.ListInhibitors
    DBusInhibitor inhibitors;
    QMetaObject::invokeMethod(parent(), "ListInhibitors", Q_RETURN_ARG(DBusInhibitor, inhibitors));
    return inhibitors;
}

DBusSeat Login1ManagerService::ListSeats()
{
    // handle method call org.freedesktop.login1.Manager.ListSeats
    DBusSeat seats;
    QMetaObject::invokeMethod(parent(), "ListSeats", Q_RETURN_ARG(DBusSeat, seats));
    return seats;
}

DBusSession Login1ManagerService::ListSessions()
{
    // handle method call org.freedesktop.login1.Manager.ListSessions
    DBusSession sessions;
    QMetaObject::invokeMethod(parent(), "ListSessions", Q_RETURN_ARG(DBusSession, sessions));
    return sessions;
}

DBusUser Login1ManagerService::ListUsers()
{
    // handle method call org.freedesktop.login1.Manager.ListUsers
    DBusUser users;
    QMetaObject::invokeMethod(parent(), "ListUsers", Q_RETURN_ARG(DBusUser, users));
    return users;
}

void Login1ManagerService::LockSession(const QString &session_id)
{
    // handle method call org.freedesktop.login1.Manager.LockSession
    QMetaObject::invokeMethod(parent(), "LockSession", Q_ARG(QString, session_id));
}

void Login1ManagerService::LockSessions()
{
    // handle method call org.freedesktop.login1.Manager.LockSessions
    QMetaObject::invokeMethod(parent(), "LockSessions");
}

void Login1ManagerService::PowerOff(bool interactive)
{
    // handle method call org.freedesktop.login1.Manager.PowerOff
    QMetaObject::invokeMethod(parent(), "PowerOff", Q_ARG(bool, interactive));
}

void Login1ManagerService::Reboot(bool interactive)
{
    // handle method call org.freedesktop.login1.Manager.Reboot
    QMetaObject::invokeMethod(parent(), "Reboot", Q_ARG(bool, interactive));
}

void Login1ManagerService::ScheduleShutdown(const QString &type, quint64 usec)
{
    // handle method call org.freedesktop.login1.Manager.ScheduleShutdown
    QMetaObject::invokeMethod(parent(), "ScheduleShutdown", Q_ARG(QString, type), Q_ARG(quint64, usec));
}

void Login1ManagerService::SetUserLinger(quint32 uid, bool enable, bool interactive)
{
    // handle method call org.freedesktop.login1.Manager.SetUserLinger
    QMetaObject::invokeMethod(parent(), "SetUserLinger", Q_ARG(quint32, uid), Q_ARG(bool, enable), Q_ARG(bool, interactive));
}

void Login1ManagerService::Suspend(bool interactive)
{
    // handle method call org.freedesktop.login1.Manager.Suspend
    QMetaObject::invokeMethod(parent(), "Suspend", Q_ARG(bool, interactive));
}

void Login1ManagerService::SuspendThenHibernate(bool interactive)
{
    // handle method call org.freedesktop.login1.Manager.SuspendThenHibernate
    QMetaObject::invokeMethod(parent(), "SuspendThenHibernate", Q_ARG(bool, interactive));
}

void Login1ManagerService::TerminateSeat(const QString &seat_id)
{
    // handle method call org.freedesktop.login1.Manager.TerminateSeat
    QMetaObject::invokeMethod(parent(), "TerminateSeat", Q_ARG(QString, seat_id));
}

void Login1ManagerService::TerminateSession(const QString &session_id)
{
    // handle method call org.freedesktop.login1.Manager.TerminateSession
    QMetaObject::invokeMethod(parent(), "TerminateSession", Q_ARG(QString, session_id));
}

void Login1ManagerService::TerminateUser(quint32 uid)
{
    // handle method call org.freedesktop.login1.Manager.TerminateUser
    QMetaObject::invokeMethod(parent(), "TerminateUser", Q_ARG(quint32, uid));
}

void Login1ManagerService::UnlockSession(const QString &session_id)
{
    // handle method call org.freedesktop.login1.Manager.UnlockSession
    QMetaObject::invokeMethod(parent(), "UnlockSession", Q_ARG(QString, session_id));
}

void Login1ManagerService::UnlockSessions()
{
    // handle method call org.freedesktop.login1.Manager.UnlockSessions
    QMetaObject::invokeMethod(parent(), "UnlockSessions");
}
DLOGIN_END_NAMESPACE

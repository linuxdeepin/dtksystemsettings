// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <qobject.h>

#include "dlogintypes.h"
#include "namespace.h"

DLOGIN_BEGIN_NAMESPACE

class DLoginSessionPrivate;

class DLoginSession : public QObject
{
    Q_OBJECT
public:
    explicit DLoginSession(const QString &path, QObject *parent = nullptr);
    virtual ~DLoginSession();
    Q_PROPERTY(bool Active READ active)
    Q_PROPERTY(bool IdleHint READ idleHint)
    Q_PROPERTY(bool LockedHint READ lockedHint)
    Q_PROPERTY(bool Remote READ remote)
    Q_PROPERTY(QString Class READ _class)
    Q_PROPERTY(QString Desktop READ desktop)
    Q_PROPERTY(QString Display READ display)
    Q_PROPERTY(QString Id READ id)
    Q_PROPERTY(QString Name READ name)
    Q_PROPERTY(QString RemoteHost READ remoteHost)
    Q_PROPERTY(QString RemoteUser READ remoteUser)
    Q_PROPERTY(QString Scope READ scope)
    Q_PROPERTY(QString Service READ service)
    Q_PROPERTY(QString State READ state)
    // Why TTY?
    Q_PROPERTY(QString TTY READ tty)
    Q_PROPERTY(QString Type READ type)

    Q_PROPERTY(SeatPath Seat READ seat)
    Q_PROPERTY(UserPath User READ user)

    Q_PROPERTY(uint Audit READ audit)
    Q_PROPERTY(uint Leader READ leader)
    Q_PROPERTY(uint VTNr READ vtnr)

    Q_PROPERTY(quint64 IdleSinceHint READ idleSinceHint)
    Q_PROPERTY(quint64 IdleSinceHintMonotonic READ idleSinceHintMonotonic)
    Q_PROPERTY(quint64 Timestamp READ timestamp)
    Q_PROPERTY(quint64 TimestampMonotonic READ timestampMonotonic)

    bool active() const;
    bool idleHint() const;
    bool lockedHint() const;
    bool remote() const;
    QString _class() const;
    QString desktop() const;
    QString display() const;
    QString id() const;
    QString name() const;
    QString remoteHost() const;
    QString remoteUser() const;
    QString scope() const;
    QString service() const;
    QString state() const;
    QString tty() const;
    QString type() const;
    SeatPath seat() const;
    UserPath user() const;
    uint audit() const;
    uint leader() const;
    uint vtnr() const;

    quint64 idleSinceHint() const;
    quint64 idleSinceHintMonotonic() const;
    quint64 timestamp() const;
    quint64 timestampMonotonic() const;

signals:
    void Lock();
    void PauseDevice(const uint value, const uint device, const QString &location);
    void ResumeDevice(const uint value, const uint device, const int descriptor);
    void Unlock();
    void errorMessageChanged(const QString &message);

public slots:
    QString lastError() const;
    void activate();
    void kill(const QString who, const uint signal_number);
    void lock();
    void pauseDeviceComplete(const uint major, const uint minor);
    void releaseControl();
    void releaseDevice(const uint manjor, const uint minor);
    void setBrightness(const QString &subsystem, const QString &name, const uint brightness);
    void setIdleHint(const bool idle);
    void setLockedHint(const bool locked);
    void setType(const QString &type);
    void takeControl(const bool force);
    std::tuple<int,  // fd
               bool  // inactive
               >
    takeDevice(uint manjor, uint minor);
    void terminate();
    void unlock();

private:
    QScopedPointer<DLoginSessionPrivate> d_ptr;
    Q_DECLARE_PRIVATE(DLoginSession)
};
DLOGIN_END_NAMESPACE

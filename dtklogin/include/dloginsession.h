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
    Q_PROPERTY(bool active READ active)
    Q_PROPERTY(bool idleHint READ idleHint)
    Q_PROPERTY(bool lockedHint READ lockedHint)
    Q_PROPERTY(bool remote READ remote)
    Q_PROPERTY(QString _class READ _class)
    Q_PROPERTY(QString desktop READ desktop)
    Q_PROPERTY(QString display READ display)
    Q_PROPERTY(QString id READ id)
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(QString remoteHost READ remoteHost)
    Q_PROPERTY(QString remoteUser READ remoteUser)
    Q_PROPERTY(QString scope READ scope)
    Q_PROPERTY(QString service READ service)
    Q_PROPERTY(QString state READ state)
    // Why TTY?
    Q_PROPERTY(QString TTY READ TTY)
    Q_PROPERTY(QString type READ type)

    Q_PROPERTY(SeatPath seat READ seat)
    Q_PROPERTY(UserPath user READ user)

    Q_PROPERTY(uint audit READ audit)
    Q_PROPERTY(uint leader READ leader)
    Q_PROPERTY(uint VTNr READ VTNr)

    Q_PROPERTY(quint64 idleSinceHint READ idleSinceHint)
    Q_PROPERTY(quint64 idleSinceHintMonotonic READ idleSinceHintMonotonic)
    Q_PROPERTY(quint64 timestamp READ timestamp)
    Q_PROPERTY(quint64 timestampMonotonic READ timestampMonotonic)

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
    QString TTY() const;
    QString type() const;
    SeatPath seat() const;
    UserPath user() const;
    uint audit() const;
    uint leader() const;
    uint VTNr() const;

    quint64 idleSinceHint() const;
    quint64 idleSinceHintMonotonic() const;
    quint64 timestamp() const;
    quint64 timestampMonotonic() const;

signals:
    void locked();
    void pauseDevice(const uint value, const uint device, const QString &location);
    void resumeDevice(const uint value, const uint device, const int descriptor);
    void unlocked();
    void errorMessageChanged(const QString &message);

public slots:
    QString lastError() const;
    void activate();
    void kill(const QString &who, const uint signalNumber);
    void lock();
    void pauseDeviceComplete(const uint major, const uint minor);
    void releaseControl();
    void releaseDevice(const uint major, const uint minor);
    void setBrightness(const QString &subsystem, const QString &name, const uint brightness);
    void setIdleHint(const bool idle);
    void setLockedHint(const bool locked);
    void setType(const QString &type);
    void takeControl(const bool force);
    std::tuple<int,  // fd
               bool  // inactive
               >
    takeDevice(uint major, uint minor);
    void terminate();
    void unlock();

private:
    QScopedPointer<DLoginSessionPrivate> d_ptr;
    Q_DECLARE_PRIVATE(DLoginSession)
};
DLOGIN_END_NAMESPACE

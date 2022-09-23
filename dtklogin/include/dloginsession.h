// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <qobject.h>

#include "namespace.h"
#include "dlogintypes.h"

DLOGIN_BEGIN_NAMESPACE

class DLoginSessionPrivate;

class DLoginSession : public QObject
{
    Q_OBJECT

public:
    virtual ~DLoginSession();
    Q_PROPERTY(bool active READ active);
    Q_PROPERTY(bool idleHint READ idleHint);
    Q_PROPERTY(bool lockedHint READ lockedHint);
    Q_PROPERTY(bool remote READ remote);
    Q_PROPERTY(SessionClass sessionClass READ sessionClass);
    Q_PROPERTY(QString desktop READ desktop);
    Q_PROPERTY(QString display READ display);
    Q_PROPERTY(QString id READ id);
    Q_PROPERTY(QString name READ name);
    Q_PROPERTY(QString remoteHost READ remoteHost);
    Q_PROPERTY(QString remoteUser READ remoteUser);
    Q_PROPERTY(QString scope READ scope);
    Q_PROPERTY(QString service READ service);
    Q_PROPERTY(SessionState state READ state);
    // Why TTY?
    Q_PROPERTY(QString TTY READ TTY);
    Q_PROPERTY(SessionType type READ type);

    Q_PROPERTY(QString seat READ seat);
    Q_PROPERTY(quint32 user READ user);

    Q_PROPERTY(quint32 audit READ audit);
    Q_PROPERTY(quint32 leader READ leader);
    Q_PROPERTY(quint32 VTNr READ VTNr);

    Q_PROPERTY(QDateTime idleSinceHint READ idleSinceHint);
    Q_PROPERTY(QDateTime idleSinceHintMonotonic READ idleSinceHintMonotonic);
    Q_PROPERTY(QDateTime createdTime READ createdTime);
    Q_PROPERTY(QDateTime createdTimeMonotonic READ createdTimeMonotonic);

    bool active() const;
    bool idleHint() const;
    bool lockedHint() const;
    bool remote() const;
    SessionClass sessionClass() const;
    QString desktop() const;
    QString display() const;
    QString id() const;
    QString name() const;
    QString remoteHost() const;
    QString remoteUser() const;
    QString scope() const;
    QString service() const;
    SessionState state() const;
    QString TTY() const;
    SessionType type() const;
    QString seat() const;
    quint32 user() const;
    quint32 audit() const;
    quint32 leader() const;
    quint32 VTNr() const;

    QDateTime idleSinceHint() const;
    QDateTime idleSinceHintMonotonic() const;
    QDateTime createdTime() const;
    QDateTime createdTimeMonotonic() const;

signals:
    void locked();
    void pauseDevice(const quint32 value, const quint32 device, const QString &location);
    void resumeDevice(const quint32 value, const quint32 device, const int descriptor);
    void unlocked();
    void autostartAdded(const QString &fileName);
    void autostartDeleted(const QString &fileName);

public slots:
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
    // Previous StartManager interfaces
    QStringList autostartList();
    bool isAutostart(const QString &fileName);
    bool removeAutostart(const QString &fileName);
    bool enableAutostartWatch();

private:
    friend class DLoginManager;
    explicit DLoginSession(const QString &path, QObject *parent = nullptr);
    QScopedPointer<DLoginSessionPrivate> d_ptr;
    Q_DECLARE_PRIVATE(DLoginSession)
};
DLOGIN_END_NAMESPACE

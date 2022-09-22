// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <qobject.h>

#include "namespace.h"

DLOGIN_BEGIN_NAMESPACE

class DLoginSessionPrivate;

class DLoginSession : public QObject
{
    Q_OBJECT
public:
    explicit DLoginSession(const QString &path, QObject *parent = nullptr);
    virtual ~DLoginSession();
    Q_PROPERTY(bool active READ active);
    Q_PROPERTY(bool idleHint READ idleHint);
    Q_PROPERTY(bool lockedHint READ lockedHint);
    Q_PROPERTY(bool remote READ remote);
    Q_PROPERTY(QString _class READ _class);
    Q_PROPERTY(QString desktop READ desktop);
    Q_PROPERTY(QString display READ display);
    Q_PROPERTY(QString id READ id);
    Q_PROPERTY(QString name READ name);
    Q_PROPERTY(QString remoteHost READ remoteHost);
    Q_PROPERTY(QString remoteUser READ remoteUser);
    Q_PROPERTY(QString scope READ scope);
    Q_PROPERTY(QString service READ service);
    Q_PROPERTY(QString state READ state);
    // Why TTY?
    Q_PROPERTY(QString TTY READ TTY);
    Q_PROPERTY(QString type READ type);

    Q_PROPERTY(QString seat READ seat);
    Q_PROPERTY(quint32 user READ user);

    Q_PROPERTY(quint32 audit READ audit);
    Q_PROPERTY(quint32 leader READ leader);
    Q_PROPERTY(quint32 VTNr READ VTNr);

    Q_PROPERTY(quint64 idleSinceHint READ idleSinceHint);
    Q_PROPERTY(quint64 idleSinceHintMonotonic READ idleSinceHintMonotonic);
    Q_PROPERTY(quint64 timestamp READ timestamp);
    Q_PROPERTY(quint64 timestampMonotonic READ timestampMonotonic);

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
    QString seat() const;
    quint32 user() const;
    quint32 audit() const;
    quint32 leader() const;
    quint32 VTNr() const;

    quint64 idleSinceHint() const;
    quint64 idleSinceHintMonotonic() const;
    quint64 timestamp() const;
    quint64 timestampMonotonic() const;

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
    QScopedPointer<DLoginSessionPrivate> d_ptr;
    Q_DECLARE_PRIVATE(DLoginSession)
};
DLOGIN_END_NAMESPACE

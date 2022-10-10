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
    Q_PROPERTY(bool idleHint READ idleHint WRITE setIdleHint);
    Q_PROPERTY(bool locked READ locked NOTIFY lockedChanged);
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
    Q_PROPERTY(QString TTY READ TTY);
    Q_PROPERTY(SessionType type READ type WRITE setType);
    Q_PROPERTY(QString seat READ seat);
    Q_PROPERTY(quint32 user READ user);
    Q_PROPERTY(quint32 audit READ audit);
    Q_PROPERTY(quint32 leader READ leader);
    Q_PROPERTY(quint32 VTNr READ VTNr);
    Q_PROPERTY(QDateTime idleSinceHint READ idleSinceHint);
    Q_PROPERTY(quint64 idleSinceHintMonotonic READ idleSinceHintMonotonic);
    Q_PROPERTY(QDateTime createdTime READ createdTime);
    Q_PROPERTY(quint64 createdTimeMonotonic READ createdTimeMonotonic);

    bool active() const;
    bool idleHint() const;
    bool locked() const;
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
    quint64 idleSinceHintMonotonic() const;
    QDateTime createdTime() const;
    quint64 createdTimeMonotonic() const;

signals:
    void lockedChanged(bool locked);
    void autostartAdded(const QString &fileName);
    void autostartRemoved(const QString &fileName);

public slots:
    void activate();
    void kill(SessionRole who, const qint32 signalNumber);
    void lock();
    void setIdleHint(const bool idle);
    void setType(SessionType type);
    void terminate();
    QStringList autostartList();
    bool isAutostart(const QString &fileName);
    bool removeAutostart(const QString &fileName);
    bool addAutostart(const QString &fileName);

private:
    friend class DLoginManager;
    explicit DLoginSession(const QString &path, QObject *parent = nullptr);
    QScopedPointer<DLoginSessionPrivate> d_ptr;
    Q_DECLARE_PRIVATE(DLoginSession)
};
DLOGIN_END_NAMESPACE

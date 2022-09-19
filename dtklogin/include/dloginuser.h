// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <qobject.h>

#include "dlogintypes.h"
#include "namespace.h"

DLOGIN_BEGIN_NAMESPACE

class DLoginUserPrivate;

class DLoginUser : public QObject
{
    Q_OBJECT
public:
    explicit DLoginUser(const QString &path, QObject *parent = nullptr);
    virtual ~DLoginUser();

    Q_PROPERTY(QList<SessionPath> Sessions READ sessions)
    Q_PROPERTY(bool IdleHint READ idleHint)
    Q_PROPERTY(bool Linger READ linger)
    Q_PROPERTY(QString Name READ name)
    Q_PROPERTY(QString RuntimePath READ runtimePath)
    Q_PROPERTY(QString Service READ service)
    Q_PROPERTY(QString Slice READ slice)
    Q_PROPERTY(QString State READ state)
    Q_PROPERTY(SessionPath Display READ display)
    Q_PROPERTY(uint GID READ GID)
    Q_PROPERTY(uint UID READ UID)
    Q_PROPERTY(quint64 IdleSinceHint READ idleSinceHint)
    Q_PROPERTY(quint64 IdleSinceHintMonotonic READ idleSinceHintMonotonic)
    Q_PROPERTY(quint64 Timestamp READ timestamp)
    Q_PROPERTY(quint64 TimestampMonotonic READ timestampMonotonic)

    QList<SessionPath> sessions() const;
    bool idleHint() const;
    bool linger() const;
    QString name() const;
    QString runtimePath() const;
    QString service() const;
    QString slice() const;
    QString state() const;
    SessionPath display() const;
    uint GID() const;
    uint UID() const;
    quint64 idleSinceHint() const;
    quint64 idleSinceHintMonotonic() const;
    quint64 timestamp() const;
    quint64 timestampMonotonic() const;

signals:
    void errorMessageChanged(const QString &message);

public slots:
    QString lastError() const;
    void kill(const int signal_number);
    void terminate();

private:
    QScopedPointer<DLoginUserPrivate> d_ptr;
    Q_DECLARE_PRIVATE(DLoginUser)
};
DLOGIN_END_NAMESPACE

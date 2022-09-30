// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <qobject.h>

#include "namespace.h"
#include "dlogintypes.h"

DLOGIN_BEGIN_NAMESPACE

class DLoginUserPrivate;

class DLoginUser : public QObject
{
    Q_OBJECT
public:
    ~DLoginUser() override;

    Q_PROPERTY(QList<QString> sessions READ sessions);
    Q_PROPERTY(bool idleHint READ idleHint);
    Q_PROPERTY(bool linger READ linger);
    Q_PROPERTY(QString name READ name);
    Q_PROPERTY(QString runtimePath READ runtimePath);
    Q_PROPERTY(QString service READ service);
    Q_PROPERTY(QString slice READ slice);
    Q_PROPERTY(UserState state READ state);
    Q_PROPERTY(QString display READ display);
    Q_PROPERTY(quint32 GID READ GID);
    Q_PROPERTY(quint32 UID READ UID);
    Q_PROPERTY(QDateTime idleSinceHint READ idleSinceHint);
    Q_PROPERTY(quint64 idleSinceHintMonotonic READ idleSinceHintMonotonic);
    Q_PROPERTY(QDateTime loginTime READ loginTime);
    Q_PROPERTY(quint64 loginTimeMonotonic READ loginTimeMonotonic);

    QList<QString> sessions() const;
    bool idleHint() const;
    bool linger() const;
    QString name() const;
    QString runtimePath() const;
    QString service() const;
    QString slice() const;
    UserState state() const;
    QString display() const;
    quint32 GID() const;
    quint32 UID() const;
    QDateTime idleSinceHint() const;
    quint64 idleSinceHintMonotonic() const;
    QDateTime loginTime() const;
    quint64 loginTimeMonotonic() const;

public slots:
    void kill(const qint32 signalNumber);
    void terminate();

private:
    explicit DLoginUser(const QString &path, QObject *parent = nullptr);
    friend class DLoginManager;
    QScopedPointer<DLoginUserPrivate> d_ptr;
    Q_DECLARE_PRIVATE(DLoginUser)
};
DLOGIN_END_NAMESPACE

// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <qobject.h>

#include "namespace.h"
#include "dlogin1types.h"

DLOGIN1_BEGIN_NAMESPACE

class DLogin1SeatPrivate;

class DLogin1Seat : public QObject
{
    Q_OBJECT
public:
    explicit DLogin1Seat(const QString &path, QObject *parent = nullptr);
    virtual ~DLogin1Seat();

    Q_PROPERTY(QList<SessionPath> Sessions READ sessions)
    Q_PROPERTY(bool CanGraphical READ canGraphical)
    Q_PROPERTY(bool CanTTY READ canTTY)
    Q_PROPERTY(bool IdleHint READ idleHint)
    Q_PROPERTY(QString Id READ id)
    Q_PROPERTY(SessionPath ActiveSession READ activeSession)
    Q_PROPERTY(quint64 IdleSinceHint READ idleSinceHint)
    Q_PROPERTY(quint64 IdleSinceHintMonotonic READ idleSinceHintMonotonic)

    bool canGraphical() const;
    bool canTTY() const;
    bool idleHint() const;
    QList<SessionPath> sessions() const;
    QString id() const;
    SessionPath activeSession() const;
    quint64 idleSinceHint() const;
    quint64 idleSinceHintMonotonic() const;

signals:
    void errorMessageChanged(const QString &message);

public slots:
    QString lastError() const;
    void activateSession(const QString &session_id);
    void switchTo(const uint vtnr);
    void switchToNext();
    void switchToPrevious();
    void terminate();

private:
    QScopedPointer<DLogin1SeatPrivate> d_ptr;
    Q_DECLARE_PRIVATE(DLogin1Seat)
};
DLOGIN1_END_NAMESPACE

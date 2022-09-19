// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <qobject.h>

#include "dlogintypes.h"
#include "namespace.h"

DLOGIN_BEGIN_NAMESPACE

class DLoginSeatPrivate;

class DLoginSeat : public QObject
{
    Q_OBJECT
public:
    explicit DLoginSeat(const QString &path, QObject *parent = nullptr);
    virtual ~DLoginSeat();

    Q_PROPERTY(QList<SessionPath> sessions READ sessions)
    Q_PROPERTY(bool canGraphical READ canGraphical)
    Q_PROPERTY(bool canTTY READ canTTY)
    Q_PROPERTY(bool idleHint READ idleHint)
    Q_PROPERTY(QString id READ id)
    Q_PROPERTY(SessionPath activeSession READ activeSession)
    Q_PROPERTY(quint64 idleSinceHint READ idleSinceHint)
    Q_PROPERTY(quint64 idleSinceHintMonotonic READ idleSinceHintMonotonic)

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
    void activateSession(const QString &sessionId);
    void switchTo(const uint VTNr);
    void switchToNext();
    void switchToPrevious();
    void terminate();

private:
    QScopedPointer<DLoginSeatPrivate> d_ptr;
    Q_DECLARE_PRIVATE(DLoginSeat)
};
DLOGIN_END_NAMESPACE

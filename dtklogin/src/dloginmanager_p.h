// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "dloginmanager.h"
#include "namespace.h"
#include <qobject.h>

class DDBusInterface;
DLOGIN_BEGIN_NAMESPACE

class DLoginManagerPrivate : public QObject
{
    Q_OBJECT
public:
    explicit DLoginManagerPrivate(DLoginManager *parent = nullptr) : QObject(parent), q_ptr(parent) {}

signals:
    // private signals
    void PrepareForShutdown(const bool value);
    void PrepareForSleep(const bool value);
    void SeatNew(const QString &seat_id, const QDBusObjectPath &seat_path);
    void SeatRemoved(const QString &seat_id, const QDBusObjectPath &seat_path);
    void SessionNew(const QString &session_id, const QDBusObjectPath &session_path);
    void SessionRemoved(const QString &session_id, const QDBusObjectPath &session_path);
    void UserNew(const uint uid, const QDBusObjectPath &path);
    void UserRemoved(const uint uid, const QDBusObjectPath &path);

public:
    QString m_errorMessage;
    DDBusInterface *m_inter;
    DLoginManager *q_ptr;
    Q_DECLARE_PUBLIC(DLoginManager)
};

DLOGIN_END_NAMESPACE

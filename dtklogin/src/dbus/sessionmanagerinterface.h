// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "dtklogin_global.h"
#include <qobject.h>
#include <qdbuspendingreply.h>

class QDBusConnection;
class DDBusInterface;

DLOGIN_BEGIN_NAMESPACE

class SessionManagerInterface : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(bool Locked READ Locked NOTIFY LockedChanged);
    bool Locked();

    static inline const char *staticInterfaceName() { return "com.deepin.SessionManager"; }
    SessionManagerInterface(const QString &service, const QString &path, QDBusConnection connection, QObject *parent = nullptr);

Q_SIGNALS:
    void LockedChanged(bool locked);

public Q_SLOTS:
    QDBusPendingReply<> SetLocked(bool locked);

private:
    DDBusInterface *m_interface;
};

DLOGIN_END_NAMESPACE

// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once
#include "namespace.h"
#include <qobject.h>
#include <qdbuspendingreply.h>

class QDBusConnection;
class DDBusInterface;

DLOGIN_BEGIN_NAMESPACE

class StartManagerInterface : public QObject
{
    Q_OBJECT

public:
    static inline const char *staticInterfaceName() { return "com.deepin.StartManager"; }
    StartManagerInterface(const QString &service, const QString &path, QDBusConnection connection, QObject *parent = nullptr);

public slots:
    QDBusPendingReply<bool> addAutostart(const QString &fileName);
    QDBusPendingReply<bool> removeAutostart(const QString &fileName);

private:
    DDBusInterface *m_interface;
};

DLOGIN_END_NAMESPACE

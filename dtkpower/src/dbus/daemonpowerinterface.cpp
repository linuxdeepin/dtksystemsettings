// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "daemonpowerinterface.h"

DPOWER_BEGIN_NAMESPACE
DaemonPowerInterface::DaemonPowerInterface(QObject *parent)
    : QObject(parent)
{
    const QString &Service = QStringLiteral("com.deepin.daemon.Power");
    const QString &Path = QStringLiteral("/com/deepin/daemon/Power");
    const QString &Interface = QStringLiteral("com.deepin.daemon.Power");

    m_inter.reset(new DDBusInterface(Service, Path, Interface, QDBusConnection::sessionBus(), this));
}
DPOWER_END_NAMESPACE

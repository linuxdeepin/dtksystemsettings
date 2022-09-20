// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dpowermanager_interface.h"
#include "dpowertypes.h"

#include <QDBusObjectPath>
#include <QSharedPointer>
#include <cstddef>
#include <qdbusconnection.h>
#include <qdbusextratypes.h>
#include <qdbuspendingreply.h>
#include <qlist.h>
#include <qstringliteral.h>

DPOWER_BEGIN_NAMESPACE
DPowerManager_interface::DPowerManager_interface(QObject *parent)
    : QObject(parent)
{
    const QString &Service = QStringLiteral("org.freedesktop.UPower");
    const QString &Path = QStringLiteral("/org/freedesktop/UPower");
    const QString &Interface = QStringLiteral("org.freedesktop.UPower");

    m_inter.reset(new DDBusInterface(Service, Path, Interface, QDBusConnection::systemBus(), this));
}

DPowerManager_interface::~DPowerManager_interface() {}

// properties
bool DPowerManager_interface::lidlsClosed() const
{
    return qdbus_cast<bool>(m_inter->property("LidlsClosed"));
}

bool DPowerManager_interface::lidlsPresent() const
{
    return qdbus_cast<bool>(m_inter->property("LidlsPresent"));
}

bool DPowerManager_interface::onBattery() const
{
    return qdbus_cast<bool>(m_inter->property("OnBattery"));
}

QString DPowerManager_interface::daemonVersion() const
{
    return qdbus_cast<QString>(m_inter->property("DaemonVersion"));
}

// pubilc slots
QDBusPendingReply<QList<QDBusObjectPath>> DPowerManager_interface::enumerateDevices()
{
    return m_inter->asyncCall(QStringLiteral("EnumerateDevices"));
}

QDBusPendingReply<QString> DPowerManager_interface::getCriticalAction()
{
    return m_inter->asyncCall(QStringLiteral("GetCriticalAction"));
}

QDBusPendingReply<QDBusObjectPath> DPowerManager_interface::getDisplayDevice()
{
    return m_inter->asyncCall(QStringLiteral("GetDisplayDevice"));
}

DPOWER_END_NAMESPACE
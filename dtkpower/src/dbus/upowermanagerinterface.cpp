// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "upowermanagerinterface.h"
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
UPowerManagerInterface::UPowerManagerInterface(QObject *parent)
    : QObject(parent)
{
    const QString &Service = QStringLiteral("org.freedesktop.UPower");
    const QString &Path = QStringLiteral("/org/freedesktop/UPower");
    const QString &Interface = QStringLiteral("org.freedesktop.UPower");

    m_inter.reset(new DDBusInterface(Service, Path, Interface, QDBusConnection::systemBus(), this));
}

UPowerManagerInterface::~UPowerManagerInterface() {}

// properties
bool UPowerManagerInterface::lidlsClosed() const
{
    return qdbus_cast<bool>(m_inter->property("LidlsClosed"));
}

bool UPowerManagerInterface::lidlsPresent() const
{
    return qdbus_cast<bool>(m_inter->property("LidlsPresent"));
}

bool UPowerManagerInterface::onBattery() const
{
    return qdbus_cast<bool>(m_inter->property("OnBattery"));
}

QString UPowerManagerInterface::daemonVersion() const
{
    return qdbus_cast<QString>(m_inter->property("DaemonVersion"));
}

// pubilc slots
QDBusPendingReply<QList<QDBusObjectPath>> UPowerManagerInterface::enumerateDevices() const
{
    return m_inter->asyncCall(QStringLiteral("EnumerateDevices"));
}

QDBusPendingReply<QString> UPowerManagerInterface::getCriticalAction() const
{
    return m_inter->asyncCall(QStringLiteral("GetCriticalAction"));
}

QDBusPendingReply<QDBusObjectPath> UPowerManagerInterface::getDisplayDevice() const
{
    return m_inter->asyncCall(QStringLiteral("GetDisplayDevice"));
}

DPOWER_END_NAMESPACE

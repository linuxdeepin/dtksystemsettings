// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
#include "./upowermanagerinterface.h"
#include <qdbusconnection.h>
#include <qdebug.h>

UPowerManagerInterface::UPowerManagerInterface(QObject *parent)
    : QObject(parent)
    ,m_reset(false)
{
    registerService();
}

UPowerManagerInterface::~UPowerManagerInterface()
{
    unRegisterService();
}

void UPowerManagerInterface:: registerService()
{
    const QString &service = QLatin1String("com.deepin.daemon.FakePower");
    const QString &path = QLatin1String("/com/deepin/daemon/FakePower");
    QDBusConnection bus = QDBusConnection::sessionBus();
    if (!bus.registerService(service)) {
        QString errorMsg = bus.lastError().message();
        if (errorMsg.isEmpty())
            errorMsg = "maybe it's running";

        qWarning() << QString("Can't register the %1 service, %2.").arg(service).arg(errorMsg);
    }
    if (!bus.registerObject(path, this, QDBusConnection::ExportScriptableContents)) {
        qWarning() << QString("Can't register %1 the D-Bus object.").arg(path);
    }
}

void UPowerManagerInterface::unRegisterService()
{
    QDBusConnection bus = QDBusConnection::sessionBus();
    bus.unregisterObject(QLatin1String("/com/deepin/daemon/FakePower"));
    bus.unregisterService(QLatin1String("com.deepin.daemon.FakePower"));
}

QList<QDBusObjectPath> UPowerManagerInterface::EnumerateDevices() const
{
    QList<QDBusObjectPath> a ;
    QDBusObjectPath b ;
    b.setPath("/org/freedesktop/UPower/devices/battery_BAT1");
    a.append(b);
    return a;
}

QString UPowerManagerInterface::GetCriticalAction() const
{
    return QString("true");
}

QDBusObjectPath UPowerManagerInterface::GetDisplayDevice() const
{
    QDBusObjectPath path;
    path.setPath("/org/freedesktop/UPower/devices/DisplayDevice");
    return path;
}
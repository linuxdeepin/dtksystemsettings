// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "upowerdeviceinterface.h"
#include <qglobal.h>
#include <qvariant.h>
DPOWER_BEGIN_NAMESPACE
UPowerDeviceInterface::UPowerDeviceInterface(const QString &name, QObject *parent)
    : QObject(parent)
{
    const QString &Service = QStringLiteral("org.freedesktop.UPower");
    const QString &Interface = QStringLiteral("org.freedesktop.UPower.Device");
    const QString &path = "/org/freedesktop/UPower/devices/" + name;

    History_p::registerMetaType();
    Statistic_p::registerMetaType();
    devicename = name;
    m_inter.reset(new DDBusInterface(Service, path, Interface, QDBusConnection::systemBus(), this));
}

UPowerDeviceInterface::~UPowerDeviceInterface() {}

// properties
bool UPowerDeviceInterface::hasHistory() const
{
    return qdbus_cast<bool>(m_inter->property("HasHistory"));
}

bool UPowerDeviceInterface::hasStatistics() const
{
    return qdbus_cast<bool>(m_inter->property("HasStatistics"));
}

bool UPowerDeviceInterface::isRechargeable() const
{
    return qdbus_cast<bool>(m_inter->property("IsRechargeable"));
}

bool UPowerDeviceInterface::online() const
{
    return qdbus_cast<bool>(m_inter->property("Online"));
}

bool UPowerDeviceInterface::powerSupply() const
{
    return qdbus_cast<bool>(m_inter->property("PowerSupply"));
}

double UPowerDeviceInterface::capacity() const
{
    return qdbus_cast<double>(m_inter->property("Capacity"));
}

double UPowerDeviceInterface::energy() const
{
    return qdbus_cast<double>(m_inter->property("Energy"));
}

double UPowerDeviceInterface::energyEmpty() const
{
    return qdbus_cast<double>(m_inter->property("EnergyEmpty"));
}

double UPowerDeviceInterface::energyFull() const
{
    return qdbus_cast<double>(m_inter->property("EnergyFull"));
}

double UPowerDeviceInterface::energyFullDesign() const
{
    return qdbus_cast<double>(m_inter->property("EnergyFullDesign"));
}

double UPowerDeviceInterface::energyRate() const
{
    return qdbus_cast<double>(m_inter->property("EnergyRate"));
}

double UPowerDeviceInterface::luminosity() const
{
    return qdbus_cast<double>(m_inter->property("Luminosity"));
}

double UPowerDeviceInterface::percentage() const
{
    return qdbus_cast<double>(m_inter->property("Percentage"));
}

double UPowerDeviceInterface::temperature() const
{
    return qdbus_cast<double>(m_inter->property("Temperature"));
}

double UPowerDeviceInterface::voltage() const
{
    return qdbus_cast<double>(m_inter->property("Voltage"));
}

qint32 UPowerDeviceInterface::chargeCycles() const
{
    return qdbus_cast<qint32>(m_inter->property("ChargeCycles"));
}

quint64 UPowerDeviceInterface::timeToEmpty() const
{
    return qdbus_cast<quint64>(m_inter->property("TimeToEmpty"));
}

quint64 UPowerDeviceInterface::timeToFull() const
{
    return qdbus_cast<quint64>(m_inter->property("TimeToFull"));
}

QString UPowerDeviceInterface::iconName() const
{
    return qdbus_cast<QString>(m_inter->property("IconName"));
}

QString UPowerDeviceInterface::model() const
{
    return qdbus_cast<QString>(m_inter->property("Model"));
}

QString UPowerDeviceInterface::nativePath() const
{
    return qdbus_cast<QString>(m_inter->property("NativePath"));
}

QString UPowerDeviceInterface::serial() const
{
    return qdbus_cast<QString>(m_inter->property("NativePath"));
}

QString UPowerDeviceInterface::vendor() const
{
    return qdbus_cast<QString>(m_inter->property("Vendor"));
}

quint32 UPowerDeviceInterface::batteryLevel() const
{
    return qdbus_cast<quint32>(m_inter->property("BatteryLevel"));
}

quint32 UPowerDeviceInterface::state() const
{
    return qdbus_cast<quint32>(m_inter->property("State"));
}

quint32 UPowerDeviceInterface::technology() const
{
    return qdbus_cast<quint32>(m_inter->property("Technology"));
}

quint32 UPowerDeviceInterface::type() const
{
    return qdbus_cast<quint32>(m_inter->property("Type"));
}

quint32 UPowerDeviceInterface::warningLevel() const
{
    return qdbus_cast<quint32>(m_inter->property("WarningLevel"));
}

quint64 UPowerDeviceInterface::updateTime() const
{
    return qdbus_cast<quint64>(m_inter->property("UpdateTime"));
}

QString UPowerDeviceInterface::deviceName() const
{
    return devicename;
}

// pubilc slots

QDBusPendingReply<QList<History_p>>
UPowerDeviceInterface::getHistory(const QString &type, const quint32 timespan, const quint32 resolution) const
{
    return m_inter->asyncCallWithArgumentList(
        "GetHistory", {QVariant::fromValue(type), QVariant::fromValue(timespan), QVariant::fromValue(resolution)});
}

QDBusPendingReply<QList<Statistic_p>> UPowerDeviceInterface::getStatistics(const QString &type) const
{
    return m_inter->asyncCallWithArgumentList("GetHistory", {QVariant::fromValue(type)});
}

QDBusPendingReply<> UPowerDeviceInterface::refresh()
{
    return m_inter->asyncCall(QStringLiteral("Refresh"));
}

DPOWER_END_NAMESPACE

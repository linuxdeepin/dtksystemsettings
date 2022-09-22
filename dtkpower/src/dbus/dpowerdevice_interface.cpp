// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dpowerdevice_interface.h"
#include <qglobal.h>
#include <qvariant.h>
DPOWER_BEGIN_NAMESPACE
DPowerDevice_interface::DPowerDevice_interface(const QString &name, QObject *parent)
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

DPowerDevice_interface::~DPowerDevice_interface() {}

// properties
bool DPowerDevice_interface::hasHistory() const
{
    return qdbus_cast<bool>(m_inter->property("HasHistory"));
}

bool DPowerDevice_interface::hasStatistics() const
{
    return qdbus_cast<bool>(m_inter->property("HasStatistics"));
}

bool DPowerDevice_interface::isRechargeable() const
{
    return qdbus_cast<bool>(m_inter->property("IsRechargeable"));
}

bool DPowerDevice_interface::online() const
{
    return qdbus_cast<bool>(m_inter->property("Online"));
}

bool DPowerDevice_interface::powerSupply() const
{
    return qdbus_cast<bool>(m_inter->property("PowerSupply"));
}

double DPowerDevice_interface::capacity() const
{
    return qdbus_cast<double>(m_inter->property("Capacity"));
}

double DPowerDevice_interface::energy() const
{
    return qdbus_cast<double>(m_inter->property("Energy"));
}

double DPowerDevice_interface::energyEmpty() const
{
    return qdbus_cast<double>(m_inter->property("EnergyEmpty"));
}

double DPowerDevice_interface::energyFull() const
{
    return qdbus_cast<double>(m_inter->property("EnergyFull"));
}

double DPowerDevice_interface::energyFullDesign() const
{
    return qdbus_cast<double>(m_inter->property("EnergyFullDesign"));
}

double DPowerDevice_interface::energyRate() const
{
    return qdbus_cast<double>(m_inter->property("EnergyRate"));
}

double DPowerDevice_interface::luminosity() const
{
    return qdbus_cast<double>(m_inter->property("Luminosity"));
}

double DPowerDevice_interface::percentage() const
{
    return qdbus_cast<double>(m_inter->property("Percentage"));
}

double DPowerDevice_interface::temperature() const
{
    return qdbus_cast<double>(m_inter->property("Temperature"));
}

double DPowerDevice_interface::voltage() const
{
    return qdbus_cast<double>(m_inter->property("Voltage"));
}

qint32 DPowerDevice_interface::chargeCycles() const
{
    return qdbus_cast<qint32>(m_inter->property("ChargeCycles"));
}

quint64 DPowerDevice_interface::timeToEmpty() const
{
    return qdbus_cast<quint64>(m_inter->property("TimeToEmpty"));
}

quint64 DPowerDevice_interface::timeToFull() const
{
    return qdbus_cast<quint64>(m_inter->property("TimeToFull"));
}

QString DPowerDevice_interface::iconName() const
{
    return qdbus_cast<QString>(m_inter->property("IconName"));
}

QString DPowerDevice_interface::model() const
{
    return qdbus_cast<QString>(m_inter->property("Model"));
}

QString DPowerDevice_interface::nativePath() const
{
    return qdbus_cast<QString>(m_inter->property("NativePath"));
}

QString DPowerDevice_interface::serial() const
{
    return qdbus_cast<QString>(m_inter->property("NativePath"));
}

QString DPowerDevice_interface::vendor() const
{
    return qdbus_cast<QString>(m_inter->property("Vendor"));
}

quint32 DPowerDevice_interface::batteryLevel() const
{
    return qdbus_cast<quint32>(m_inter->property("BatteryLevel"));
}

quint32 DPowerDevice_interface::state() const
{
    return qdbus_cast<quint32>(m_inter->property("State"));
}

quint32 DPowerDevice_interface::technology() const
{
    return qdbus_cast<quint32>(m_inter->property("Technology"));
}

quint32 DPowerDevice_interface::type() const
{
    return qdbus_cast<quint32>(m_inter->property("Type"));
}

quint32 DPowerDevice_interface::warningLevel() const
{
    return qdbus_cast<quint32>(m_inter->property("WarningLevel"));
}

quint64 DPowerDevice_interface::updateTime() const
{
    return qdbus_cast<quint64>(m_inter->property("UpdateTime"));
}

QString DPowerDevice_interface::deviceName() const
{
    return devicename;
}

// pubilc slots

QDBusPendingReply<QList<History_p>>
DPowerDevice_interface::getHistory(const QString &type, const quint32 timespan, const quint32 resolution) const
{
    return m_inter->asyncCallWithArgumentList(
        "GetHistory", {QVariant::fromValue(type), QVariant::fromValue(timespan), QVariant::fromValue(resolution)});
}

QDBusPendingReply<QList<Statistic_p>> DPowerDevice_interface::getStatistics(const QString &type) const
{
    return m_inter->asyncCallWithArgumentList("GetHistory", {QVariant::fromValue(type)});
}

QDBusPendingReply<> DPowerDevice_interface::refresh()
{
    return m_inter->asyncCall(QStringLiteral("Refresh"));
}

DPOWER_END_NAMESPACE

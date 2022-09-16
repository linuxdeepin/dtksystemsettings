// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dpowerdevice.h"
#include <qdbusconnection.h>
#include <qdbuspendingreply.h>
#include <qglobal.h>
#include <qlist.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qobjectdefs.h>
#include <qpair.h>
#include <qstringliteral.h>
#include <qvariant.h>
#include <stdexcept>
#include <sys/types.h>
#include <tuple>

#include "ddbusinterface.h"
#include "dpowerdevice_p.h"
#include "dpowertypes.h"
#include "dpowertypes_p.h"
DPOWER_BEGIN_NAMESPACE
DPowerDevice::DPowerDevice(const QString & name, QObject *parent)
    : QObject(parent)
    , d_ptr(new DPowerDevicePrivate(this))
{
    const QString &Service = QStringLiteral("org.freedesktop.UPower");
    const QString &Interface = QStringLiteral("org.freedesktop.UPower.Device");
    const QString &path = "/org/freedesktop/UPower/devices/"+name;
    Q_D(DPowerDevice);
    History_p::registerMetaType();
    Statistic_p::registerMetaType();
    devicename = name ; 
    d->m_inter = new DDBusInterface(Service, path, Interface, QDBusConnection::systemBus(), d);
}

DPowerDevice::~DPowerDevice() {}

// properties

bool DPowerDevice::hasHistory() const
{
    Q_D(const DPowerDevice);
    return qdbus_cast<bool>(d->m_inter->property("HasHistory"));
}

bool DPowerDevice::hasStatistics() const
{
    Q_D(const DPowerDevice);
    return qdbus_cast<bool>(d->m_inter->property("HasStatistics"));
}

bool DPowerDevice::isRechargeable() const
{
    Q_D(const DPowerDevice);
    return qdbus_cast<bool>(d->m_inter->property("IsRechargeable"));
}

bool DPowerDevice::online() const
{
    Q_D(const DPowerDevice);
    return qdbus_cast<bool>(d->m_inter->property("Online"));
}

bool DPowerDevice::powerSupply() const
{
    Q_D(const DPowerDevice);
    return qdbus_cast<bool>(d->m_inter->property("PowerSupply"));
}

double DPowerDevice::capacity() const
{
    Q_D(const DPowerDevice);
    return qdbus_cast<double>(d->m_inter->property("Capacity"));
}

double DPowerDevice::energy() const
{
    Q_D(const DPowerDevice);
    return qdbus_cast<double>(d->m_inter->property("Energy"));
}

double DPowerDevice::energyEmpty() const
{
    Q_D(const DPowerDevice);
    return qdbus_cast<double>(d->m_inter->property("EnergyEmpty"));
}

double DPowerDevice::energyFull() const
{
    Q_D(const DPowerDevice);
    return qdbus_cast<double>(d->m_inter->property("EnergyFull"));
}

double DPowerDevice::energyFullDesign() const
{
    Q_D(const DPowerDevice);
    return qdbus_cast<double>(d->m_inter->property("EnergyFullDesign"));
}

double DPowerDevice::energyRate() const
{
    Q_D(const DPowerDevice);
    return qdbus_cast<double>(d->m_inter->property("EnergyRate"));
}

double DPowerDevice::luminosity() const
{
    Q_D(const DPowerDevice);
    return qdbus_cast<double>(d->m_inter->property("Luminosity"));
}

double DPowerDevice::percentage() const
{
    Q_D(const DPowerDevice);
    return qdbus_cast<double>(d->m_inter->property("Percentage"));
}

double DPowerDevice::temperature() const
{
    Q_D(const DPowerDevice);
    return qdbus_cast<double>(d->m_inter->property("Temperature"));
}

double DPowerDevice::voltage() const
{
    Q_D(const DPowerDevice);
    return qdbus_cast<double>(d->m_inter->property("Voltage"));
}

int DPowerDevice::chargeCycles() const
{
    Q_D(const DPowerDevice);
    return qdbus_cast<uint>(d->m_inter->property("ChargeCycles"));
}

quint64 DPowerDevice::timeToEmpty() const
{
    Q_D(const DPowerDevice);
    return qdbus_cast<uint>(d->m_inter->property("TimeToEmpty"));
}

quint64 DPowerDevice::timeToFull() const
{
    Q_D(const DPowerDevice);
    return qdbus_cast<uint>(d->m_inter->property("TimeToFull"));
}

QString DPowerDevice::iconName() const
{
    Q_D(const DPowerDevice);
    return qdbus_cast<QString>(d->m_inter->property("IconName"));
}

QString DPowerDevice::model() const
{
    Q_D(const DPowerDevice);
    return qdbus_cast<QString>(d->m_inter->property("Model"));
}

QString DPowerDevice::nativePath() const
{
    Q_D(const DPowerDevice);
    return qdbus_cast<QString>(d->m_inter->property("NativePath"));
}

QString DPowerDevice::serial() const
{
    Q_D(const DPowerDevice);
    return qdbus_cast<QString>(d->m_inter->property("NativePath"));
}

QString DPowerDevice::vendor() const
{
    Q_D(const DPowerDevice);
    return qdbus_cast<QString>(d->m_inter->property("Vendor"));
}

uint DPowerDevice::batteryLevel() const
{
    Q_D(const DPowerDevice);
    return qdbus_cast<uint>(d->m_inter->property("BatteryLevel"));
}

uint DPowerDevice::state() const
{
    Q_D(const DPowerDevice);
    return qdbus_cast<uint>(d->m_inter->property("State"));
}

uint DPowerDevice::technology() const
{
    Q_D(const DPowerDevice);
    return qdbus_cast<uint>(d->m_inter->property("Technology"));
}

uint DPowerDevice::type() const
{
    Q_D(const DPowerDevice);
    return qdbus_cast<uint>(d->m_inter->property("Type"));
}

uint DPowerDevice::warningLevel() const
{
    Q_D(const DPowerDevice);
    return qdbus_cast<uint>(d->m_inter->property("WarningLevel"));
}

quint64 DPowerDevice::updateTime() const
{
    Q_D(const DPowerDevice);
    return qdbus_cast<quint64>(d->m_inter->property("UpdateTime"));
}

QString DPowerDevice::deviceName()const
{
    return devicename;
}

// pubilc slots
QString DPowerDevice::lastError() const
{
    Q_D(const DPowerDevice);
    return d->m_errorMessage;
}

QList<History> DPowerDevice::getHistory(const QString &type, const uint timespan, const uint resolution)
{
    Q_D(DPowerDevice);
    QDBusPendingReply<QList<History_p>> reply = d->m_inter->asyncCallWithArgumentList(
        "GetHistory", {QVariant::fromValue(type), QVariant::fromValue(timespan), QVariant::fromValue(resolution)});
    reply.waitForFinished();
    QList<History> historys;
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return historys;
    }

    for (auto &&history_p : reply.value()) {
        History history;
        history.value = history_p.value;
        history.state = history_p.state;
        history.time = history_p.time;
        historys.append(history);
    }
    return historys;
}

QList<Statistic> DPowerDevice::getStatistics(const QString &type)
{
    Q_D(DPowerDevice);
    QDBusPendingReply<QList<Statistic_p>> reply = d->m_inter->asyncCallWithArgumentList(
        "GetHistory", {QVariant::fromValue(type)});
    reply.waitForFinished();
    QList<Statistic> statistics;
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return statistics;
    }

    for (auto &&statistic_p : reply.value()) {
        Statistic statistic;
        statistic.value = statistic_p.value;
        statistic.accuracy = statistic_p.accuracy;
        
        statistics.append(statistic);
    }
    return statistics;
}


void DPowerDevice::refresh()
{
    Q_D(DPowerDevice);
    QDBusPendingReply<> reply = d->m_inter->asyncCall(QStringLiteral("Refresh"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

DPOWER_END_NAMESPACE

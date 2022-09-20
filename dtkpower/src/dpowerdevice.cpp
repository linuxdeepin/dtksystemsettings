// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dpowerdevice.h"
#include "dpowerdevice_p.h"
#include "dpowertypes.h"
#include <qdbusargument.h>
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

DPOWER_BEGIN_NAMESPACE

DPowerDevice::DPowerDevice(const QString &name, QObject *parent)
    : QObject(parent)
    , d_ptr(new DPowerDevicePrivate(name, this))
{
    d_ptr->devicename = name;
}

DPowerDevice::~DPowerDevice() {}

// properties

bool DPowerDevice::hasHistory() const
{
    return d_ptr->m_device_inter->hasHistory();
}

bool DPowerDevice::hasStatistics() const
{
    return d_ptr->m_device_inter->hasStatistics();
}

bool DPowerDevice::isRechargeable() const
{
    return d_ptr->m_device_inter->isRechargeable();
}

bool DPowerDevice::online() const
{
    return d_ptr->m_device_inter->online();
}

bool DPowerDevice::powerSupply() const
{
    return d_ptr->m_device_inter->powerSupply();
}

double DPowerDevice::capacity() const
{
    return d_ptr->m_device_inter->capacity();
}

double DPowerDevice::energy() const
{
    return d_ptr->m_device_inter->energy();
}

double DPowerDevice::energyEmpty() const
{
    return d_ptr->m_device_inter->energyEmpty();
}

double DPowerDevice::energyFull() const
{
    return d_ptr->m_device_inter->energyFull();
}

double DPowerDevice::energyFullDesign() const
{
    return d_ptr->m_device_inter->energyFullDesign();
}

double DPowerDevice::energyRate() const
{
    return d_ptr->m_device_inter->energyRate();
}

double DPowerDevice::luminosity() const
{
    return d_ptr->m_device_inter->luminosity();
}

double DPowerDevice::percentage() const
{
    return d_ptr->m_device_inter->percentage();
}

double DPowerDevice::temperature() const
{
    return d_ptr->m_device_inter->temperature();
}

double DPowerDevice::voltage() const
{
    return d_ptr->m_device_inter->voltage();
}

qint32 DPowerDevice::chargeCycles() const
{
    return d_ptr->m_device_inter->chargeCycles();
}

quint64 DPowerDevice::timeToEmpty() const
{
    return d_ptr->m_device_inter->timeToEmpty();
}

quint64 DPowerDevice::timeToFull() const
{
    return d_ptr->m_device_inter->timeToFull();
}

QString DPowerDevice::iconName() const
{
    return d_ptr->m_device_inter->iconName();
}

QString DPowerDevice::model() const
{
    return d_ptr->m_device_inter->model();
}

QString DPowerDevice::nativePath() const
{
    return d_ptr->m_device_inter->nativePath();
}

QString DPowerDevice::serial() const
{
    return d_ptr->m_device_inter->serial();
}

QString DPowerDevice::vendor() const
{
    return d_ptr->m_device_inter->vendor();
}

quint32 DPowerDevice::batteryLevel() const
{
    return d_ptr->m_device_inter->batteryLevel();
}

quint32 DPowerDevice::state() const
{
    return d_ptr->m_device_inter->state();
}

quint32 DPowerDevice::technology() const
{
    return d_ptr->m_device_inter->technology();
}

quint32 DPowerDevice::type() const
{
    return d_ptr->m_device_inter->type();
}

quint32 DPowerDevice::warningLevel() const
{
    return d_ptr->m_device_inter->warningLevel();
}

quint64 DPowerDevice::updateTime() const
{
    return d_ptr->m_device_inter->updateTime();
}

QString DPowerDevice::deviceName() const
{
    return d_ptr->devicename;
}

// pubilc slots
QString DPowerDevice::lastError() const
{
    return d_ptr->m_errorMessage;
}

QList<History> DPowerDevice::getHistory(const QString &type, const uint timespan, const uint resolution)
{
    QDBusPendingReply<QList<History_p>> reply = d_ptr->m_device_inter->getHistory(type, timespan, resolution);
    reply.waitForFinished();
    QList<History> historys;
    if (!reply.isValid()) {
        d_ptr->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d_ptr->m_errorMessage);
        return historys;
    }

    for (auto &&history_p : reply.value()) {
        History history;
        history.value = history_p.value;
        history.state = history_p.state;
        history.time = history_p.time;
        historys.append(history);
    }  // TODO:修改此处，需要简化
    return historys;
}

QList<Statistic> DPowerDevice::getStatistics(const QString &type)
{
    QDBusPendingReply<QList<Statistic_p>> reply = d_ptr->m_device_inter->getStatistics(type);
    reply.waitForFinished();
    QList<Statistic> statistics;
    if (!reply.isValid()) {
        d_ptr->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d_ptr->m_errorMessage);
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
    QDBusPendingReply<> reply = d_ptr->m_device_inter->refresh();
    reply.waitForFinished();
    if (!reply.isValid()) {
        d_ptr->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d_ptr->m_errorMessage);
    }
}

DPOWER_END_NAMESPACE

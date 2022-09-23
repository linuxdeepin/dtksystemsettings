// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <qglobal.h>
#include <qobject.h>
#include <qdbuspendingreply.h>
#include <qdbusconnection.h>
#include <qvariant.h>

#include "namespace.h"
#include "ddbusinterface.h"
#include "upowertypes_p.h"
DPOWER_BEGIN_NAMESPACE


class UPowerDeviceInterface : public QObject
{
    Q_OBJECT
public:
    explicit UPowerDeviceInterface(const QString &name, QObject *parent = nullptr);

    virtual ~UPowerDeviceInterface();

    Q_PROPERTY(bool HasHistory READ hasHistory)
    Q_PROPERTY(bool HasStatistics READ hasStatistics)
    Q_PROPERTY(bool IsPresent READ isPresent)
    Q_PROPERTY(bool IsRechargeable READ isRechargeable)
    Q_PROPERTY(bool Online READ online)
    Q_PROPERTY(bool PowerSupply READ powerSupply)
    Q_PROPERTY(double Capacity READ capacity)
    Q_PROPERTY(double Energy READ energy NOTIFY EnergyChanged)
    Q_PROPERTY(double EnergyEmpty READ energyEmpty)
    Q_PROPERTY(double EnergyFull READ energyFull)
    Q_PROPERTY(double EnergyFullDesign READ energyFullDesign)
    Q_PROPERTY(double EnergyRate READ energyRate NOTIFY EnergyRateChanged)
    Q_PROPERTY(double Luminosity READ luminosity)
    Q_PROPERTY(double Percentage READ percentage NOTIFY PercentageChanged)
    Q_PROPERTY(double Temperature READ temperature)
    Q_PROPERTY(double Voltage READ voltage)
    Q_PROPERTY(quint32 ChargeCycles READ chargeCycles)
    Q_PROPERTY(quint64 TimeToEmpty READ timeToEmpty NOTIFY TimeToEmptyChanged)
    Q_PROPERTY(quint64 TimeToFull READ timeToFull NOTIFY TimeToFullChanged)
    Q_PROPERTY(QString IconName READ iconName NOTIFY IconNameChanged)
    Q_PROPERTY(QString Model READ model)
    Q_PROPERTY(QString NativePath READ nativePath)
    Q_PROPERTY(QString Serial READ serial)
    Q_PROPERTY(QString Vendor READ vendor)
    Q_PROPERTY(quint32 BatteryLevel READ batteryLevel)
    Q_PROPERTY(quint32 State READ state)
    Q_PROPERTY(quint32 Technology READ technology)
    Q_PROPERTY(quint32 Type READ type)
    Q_PROPERTY(quint32 WarningLevel READ warningLevel)
    Q_PROPERTY(quint64 UpdateTime READ updateTime NOTIFY UpdateTimeChanged)
    Q_PROPERTY(QString DeviceName READ deviceName )


    bool hasHistory() const;
    bool hasStatistics() const;
    bool isPresent() const;
    bool isRechargeable() const;
    bool online() const;
    bool powerSupply() const;
    double capacity() const;
    double energy() const;
    double energyEmpty() const;
    double energyFull() const;
    double energyFullDesign() const;
    double energyRate() const;
    double luminosity() const;
    double percentage() const;
    double temperature() const;
    double voltage() const;
    qint32 chargeCycles() const;
    quint64 timeToEmpty() const;
    quint64 timeToFull() const;
    QString iconName() const;
    QString model() const;
    QString nativePath() const;
    QString serial() const;
    QString vendor() const;
    quint32 batteryLevel() const;
    quint32 state() const;
    quint32 technology() const;
    quint32 type() const;
    quint32 warningLevel() const;
    quint64 updateTime() const;//TODO:更换为qdatetime
    QString deviceName() const;

signals:
    void UpdateTimeChanged(const quint64 value);
    void PercentageChanged(const double value);
    void TimeToEmptyChanged(const quint64 value);
    void TimeToFullChanged(const quint64 value);
    void EnergyRateChanged(const double value);
    void EnergyChanged(const double value);
    void IconNameChanged(const QString &value);


public slots:
    QDBusPendingReply<QList<History_p>> getHistory(const QString &type, const uint timespan, const uint resolution) const;
    QDBusPendingReply<QList<Statistic_p>> getStatistics(const QString &type) const;
    QDBusPendingReply<> refresh();

private:
    QScopedPointer<DDBusInterface> m_inter;
    QString devicename ;
};
DPOWER_END_NAMESPACE

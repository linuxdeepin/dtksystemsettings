// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <qglobal.h>
#include <qlist.h>
#include <qobject.h>

#include <qscopedpointer.h>

#include "dpowermanager.h"
#include "dpowertypes.h"
#include "namespace.h"

DPOWER_BEGIN_NAMESPACE

class DPowerDevicePrivate;

class DPowerDevice : public QObject
{
    Q_OBJECT
private:
    explicit DPowerDevice(const QString &name, QObject *parent = nullptr);
public:
    virtual ~DPowerDevice();

    Q_PROPERTY(bool HasHistory READ hasHistory)
    Q_PROPERTY(bool HasStatistics READ hasStatistics)
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
    Q_PROPERTY(uint ChargeCycles READ chargeCycles)
    Q_PROPERTY(quint64 TimeToEmpty READ timeToEmpty NOTIFY TimeToEmptyChanged)
    Q_PROPERTY(quint64 TimeToFull READ timeToFull NOTIFY TimeToFullChanged)
    Q_PROPERTY(QString IconName READ iconName NOTIFY IconNameChanged)
    Q_PROPERTY(QString Model READ model)
    Q_PROPERTY(QString NativePath READ nativePath)
    Q_PROPERTY(QString Serial READ serial)
    Q_PROPERTY(QString Vendor READ vendor)
    Q_PROPERTY(uint BatteryLevel READ batteryLevel)
    Q_PROPERTY(uint State READ state)
    Q_PROPERTY(uint Technology READ technology)
    Q_PROPERTY(uint Type READ type)
    Q_PROPERTY(uint WarningLevel READ warningLevel)
    Q_PROPERTY(quint64 UpdateTime READ updateTime NOTIFY UpdateTimeChanged)
    Q_PROPERTY(QString DeviceName READ deviceName )


    bool hasHistory() const;
    bool hasStatistics() const;
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
    int chargeCycles() const;
    quint64 timeToEmpty() const;
    quint64 timeToFull() const;
    QString iconName() const;
    QString model() const;
    QString nativePath() const;
    QString serial() const;
    QString vendor() const;
    uint batteryLevel() const;
    uint state() const;
    uint technology() const;
    uint type() const;
    uint warningLevel() const;
    quint64 updateTime() const;//TODO:更换为qdatetime
    QString deviceName() const;

signals:
    void errorMessageChanged(const QString &message);

    void UpdateTimeChanged(const quint64 value);
    void PercentageChanged(const double value);
    void TimeToEmptyChanged(const quint64 value);
    void TimeToFullChanged(const quint64 value);
    void EnergyRateChanged(const double value);
    void EnergyChanged(const double value);
    void IconNameChanged(const QString &value);


public slots:
    QString lastError() const;
    QList<History> getHistory(const QString &type, const uint timespan, const uint resolution);
    QList<Statistic> getStatistics(const QString &type);
    void refresh(); 
    
private:
    QScopedPointer<DPowerDevicePrivate> d_ptr;
    Q_DECLARE_PRIVATE(DPowerDevice)
    //TODO： 把构造的时候传入的name保存为一个属性
    QString devicename ;

    friend QSharedPointer<DPowerDevice> DPowerManager::getDisplayDevice(); 
    friend QSharedPointer<DPowerDevice> DPowerManager::getDeviceByName(const QString &name); 
};
DPOWER_END_NAMESPACE
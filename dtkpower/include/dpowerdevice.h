// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <qscopedpointer.h>

#include "dpowermanager.h"
#include "dpowertypes.h"
#include "namespace.h"

DPOWER_BEGIN_NAMESPACE

class DPowerDevicePrivate;

class DPowerDevice : public QObject
{
    Q_OBJECT
public:
    virtual ~DPowerDevice();

    Q_PROPERTY(bool hasHistory READ hasHistory)
    Q_PROPERTY(bool hasStatistics READ hasStatistics)
    Q_PROPERTY(bool isRechargeable READ isRechargeable)
    Q_PROPERTY(bool online READ online)
    Q_PROPERTY(bool powerSupply READ powerSupply)
    Q_PROPERTY(double capacity READ capacity)
    Q_PROPERTY(double energy READ energy NOTIFY EnergyChanged)
    Q_PROPERTY(double energyEmpty READ energyEmpty)
    Q_PROPERTY(double energyFull READ energyFull)
    Q_PROPERTY(double energyFullDesign READ energyFullDesign)
    Q_PROPERTY(double energyRate READ energyRate NOTIFY EnergyRateChanged)
    Q_PROPERTY(double luminosity READ luminosity)
    Q_PROPERTY(double percentage READ percentage NOTIFY PercentageChanged)
    Q_PROPERTY(double temperature READ temperature)
    Q_PROPERTY(double voltage READ voltage)
    Q_PROPERTY(uint chargeCycles READ chargeCycles)
    Q_PROPERTY(quint64 timeToEmpty READ timeToEmpty NOTIFY TimeToEmptyChanged)
    Q_PROPERTY(quint64 timeToFull READ timeToFull NOTIFY TimeToFullChanged)
    Q_PROPERTY(QString iconName READ iconName NOTIFY IconNameChanged)
    Q_PROPERTY(QString model READ model)
    Q_PROPERTY(QString nativePath READ nativePath)
    Q_PROPERTY(QString serial READ serial)
    Q_PROPERTY(QString vendor READ vendor)
    Q_PROPERTY(uint batteryLevel READ batteryLevel)
    Q_PROPERTY(uint state READ state)
    Q_PROPERTY(uint technology READ technology)
    Q_PROPERTY(uint type READ type)
    Q_PROPERTY(uint warningLevel READ warningLevel)
    Q_PROPERTY(quint64 updateTime READ updateTime NOTIFY UpdateTimeChanged)
    Q_PROPERTY(QString deviceName READ deviceName)

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
    quint64 updateTime() const;  // TODO:更换为qdatetime
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
    QList<History> getHistory(const QString &type, const uint timespan, const uint resolution) const;
    QList<Statistic> getStatistics(const QString &type) const;
    void refresh();

private:
    QScopedPointer<DPowerDevicePrivate> d_ptr;
    Q_DECLARE_PRIVATE(DPowerDevice)

    explicit DPowerDevice(const QString &name, QObject *parent = nullptr);
    Q_DISABLE_COPY(DPowerDevice)

    friend QSharedPointer<DPowerDevice> DPowerManager::getDisplayDevice() const;
    friend QSharedPointer<DPowerDevice> DPowerManager::getDeviceByName(const QString &name) const;
};
DPOWER_END_NAMESPACE

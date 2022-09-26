// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "ddbusinterface.h"
#include "namespace.h"
#include <qdbuspendingreply.h>
#include <qscopedpointer.h>

DPOWER_BEGIN_NAMESPACE

class SystemPowerInterface : public QObject
{
    Q_OBJECT
public:
    explicit SystemPowerInterface(QObject *parent = nullptr);
    virtual ~SystemPowerInterface() {}

    Q_PROPERTY(QString CpuGovernor READ cpuGovernor NOTIFY CpuGovernorChanged);
    Q_PROPERTY(QString Mode READ mode NOTIFY ModeChanged);
    Q_PROPERTY(bool PowerSavingModeAuto READ powerSavingModeAuto WRITE setPowerSavingModeAuto NOTIFY PowerSavingModeAutoChanged);
    Q_PROPERTY(bool PowerSavingModeAutoWhenBatteryLow READ powerSavingModeAutoWhenBatteryLow WRITE
                   setPowerSavingModeAutoWhenBatteryLow NOTIFY PowerSavingModeAutoWhenBatteryLowChanged);
    Q_PROPERTY(quint32 PowerSavingModeBrightnessDropPercent READ powerSavingModeBrightnessDropPercent WRITE
                   setPowerSavingModeBrightnessDropPercent NOTIFY PowerSavingModeBrightnessDropPercentChanged);
    inline QString cpuGovernor() const { return qdbus_cast<QString>(m_inter->property("CpuGovernor")); }
    inline QString mode() const { return qdbus_cast<QString>(m_inter->property("Mode")); }
    inline bool powerSavingModeAuto() const { return qdbus_cast<bool>(m_inter->property("PowerSavingModeAuto")); }
    inline void setPowerSavingModeAuto(const bool value) {
        m_inter->setProperty("PowerSavingModeAuto", QVariant::fromValue(value));
    }
    inline bool powerSavingModeAutoWhenBatteryLow() const { return qdbus_cast<bool>(m_inter->property("PowerSavingModeAutoWhenBatteryLow")); }
    inline void setPowerSavingModeAutoWhenBatteryLow(const bool value) {
        m_inter->setProperty("PowerSavingModeAutWhenBatteryLow", QVariant::fromValue(value));
    }
    inline quint32 powerSavingModeBrightnessDropPercent() const { return qdbus_cast<quint32>(m_inter->property("PowerSavingModeBrightnessDropPercent")); }
    inline void setPowerSavingModeBrightnessDropPercent(const quint32 &value) {
        m_inter->setProperty("PowerSavingModeBrightnessDropPercent", QVariant::fromValue(value));
    }

signals:
    void CpuGovernorChanged(const QString &value);
    void ModeChanged(const QString &value);
    void PowerSavingModeAutoChanged(const bool value);
    void PowerSavingModeAutoWhenBatteryLowChanged(const bool value);
    void PowerSavingModeBrightnessDropPercentChanged(const quint32 value);

public slots:
    QDBusPendingReply<> setMode(const QString &mode) {
        return m_inter->asyncCallWithArgumentList("SetMode", {QVariant::fromValue(mode)});
    }

private:
    QScopedPointer<DDBusInterface> m_inter;
};

DPOWER_END_NAMESPACE

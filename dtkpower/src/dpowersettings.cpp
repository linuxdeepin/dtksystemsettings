// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dpowersettings_p.h"
#include "dpowersettings.h"

#include <qsharedpointer.h>
#include <qdebug.h>

#include "dbus/systempowerinterface.h"
#include "dbus/daemonpowerinterface.h"
#include "dpowertypes.h"

DPOWER_BEGIN_NAMESPACE

void DPowerSettingsPrivate::connectDBusSignal()
{
    Q_Q(DPowerSettings);
    connect(m_systemPowerInter, &SystemPowerInterface::CpuGovernorChanged, q, &DPowerSettings::cpuGovernorChanged);
    connect(m_systemPowerInter,
            &SystemPowerInterface::PowerSavingModeAutoChanged,
            q,
            &DPowerSettings::autoPowerSavingOnBatteryChanged);
    connect(m_systemPowerInter,
            &SystemPowerInterface::PowerSavingModeAutoWhenBatteryLowChanged,
            q,
            &DPowerSettings::autoPowerSavingWhenBatteryLowChanged);
    connect(m_systemPowerInter,
            &SystemPowerInterface::PowerSavingModeBrightnessDropPercentChanged,
            q,
            &DPowerSettings::powerSavingBrightnessDropPercentChanged);
    connect(m_daemonPowerInter,
            &DaemonPowerInterface::BatteryLidClosedActionChanged,
            q,
            &DPowerSettings::batteryLidClosedActionChanged);
    connect(m_daemonPowerInter,
            &DaemonPowerInterface::BatteryLockDelayChanged,
            q,
            &DPowerSettings::batteryLockDelayChanged);
    connect(m_daemonPowerInter,
            &DaemonPowerInterface::BatteryPressPowerBtnActionChanged,
            q,
            &DPowerSettings::batteryPressPowerBtnActionChanged);
    connect(m_daemonPowerInter,
            &DaemonPowerInterface::BatteryScreenBlackDelayChanged,
            q,
            &DPowerSettings::batteryScreenBlackDelayChanged);
    connect(m_daemonPowerInter,
            &DaemonPowerInterface::BatteryScreensaverDelayChanged,
            q,
            &DPowerSettings::batteryScreensaverDelayChanged);
    connect(m_daemonPowerInter,
            &DaemonPowerInterface::BatterySleepDelayChanged,
            q,
            &DPowerSettings::batterySleepDelayChanged);
    connect(m_daemonPowerInter,
            &DaemonPowerInterface::LinePowerLidClosedActionChanged,
            q,
            &DPowerSettings::linePowerLidClosedActionChanged);
    connect(m_daemonPowerInter,
            &DaemonPowerInterface::LinePowerLockDelayChanged,
            q,
            &DPowerSettings::linePowerLockDelayChanged);
    connect(m_daemonPowerInter,
            &DaemonPowerInterface::LinePowerPressPowerBtnActionChanged,
            q,
            &DPowerSettings::linePowerPressPowerBtnActionChanged);
    connect(m_daemonPowerInter,
            &DaemonPowerInterface::LinePowerScreenBlackDelayChanged,
            q,
            &DPowerSettings::linePowerScreenBlackDelayChanged);
    connect(m_daemonPowerInter,
            &DaemonPowerInterface::LinePowerScreensaverDelayChanged,
            q,
            &DPowerSettings::linePowerScreensaverDelayChanged);
    connect(m_daemonPowerInter,
            &DaemonPowerInterface::LinePowerSleepDelayChanged,
            q,
            &DPowerSettings::linePowerSleepDelayChanged);
    connect(m_daemonPowerInter,
            &DaemonPowerInterface::LowPowerAutoSleepThresholdChanged,
            q,
            &DPowerSettings::lowPowerAutoSleepThresholdChanged);
    connect(m_daemonPowerInter,
            &DaemonPowerInterface::LowPowerNotifyEnableChanged,
            q,
            &DPowerSettings::lowPowerNotifyEnableChanged);
    connect(m_daemonPowerInter,
            &DaemonPowerInterface::LowPowerNotifyThresholdChanged,
            q,
            &DPowerSettings::lowPowerNotifyThresholdChanged);
    connect(m_daemonPowerInter,
            &DaemonPowerInterface::ScreenBlackLockChanged,
            q,
            &DPowerSettings::screenBlackLockChanged);
    connect(m_daemonPowerInter,
            &DaemonPowerInterface::SleepLockChanged,
            q,
            &DPowerSettings::sleepLockChanged);
}

DPowerSettings::DPowerSettings(QObject *parent)
    : QObject(parent)
    , d_ptr(new DPowerSettingsPrivate(this))
{
    Q_D(DPowerSettings);
    d->m_systemPowerInter = new SystemPowerInterface(this);
    d->m_daemonPowerInter = new DaemonPowerInterface(this);
    d->connectDBusSignal();
}

DPowerSettings::~DPowerSettings() {}

QString DPowerSettings::cpuGovernor() const
{
    Q_D(const DPowerSettings);
    return d->m_systemPowerInter->cpuGovernor();
}

PowerMode DPowerSettings::powerMode() const
{
    Q_D(const DPowerSettings);
    QMap<QString, PowerMode> modeMap;
    modeMap["performance"] = PowerMode::Performance;
    modeMap["balance"] = PowerMode::Balance;
    modeMap["powersave"] = PowerMode::Powersave;
    auto mode = d->m_systemPowerInter->mode();
    PowerMode realMode;
    if (modeMap.contains(mode))
        realMode = modeMap[mode];
    else
        realMode = PowerMode::Unknown;

    return realMode;
}

void DPowerSettings::setPowerMode(const PowerMode &mode)
{
    Q_D(DPowerSettings);
    if (mode == PowerMode::Unknown)
        return;
    QMap<PowerMode, QString> modeMap;
    modeMap[PowerMode::Performance] = "performance";
    modeMap[PowerMode::Balance] = "balance";
    modeMap[PowerMode::Powersave] = "powersave";
    d->m_systemPowerInter->setMode(modeMap[mode]);
}

bool DPowerSettings::autoPowerSavingOnBattery() const
{
    Q_D(const DPowerSettings);
    return d->m_systemPowerInter->powerSavingModeAuto();
}

void DPowerSettings::setAutoPowerSavingOnBattery(const bool enabled)
{
    Q_D(DPowerSettings);
    d->m_systemPowerInter->setPowerSavingModeAuto(enabled);
}

bool DPowerSettings::autoPowerSavingWhenBatteryLow() const
{
    Q_D(const DPowerSettings);
    return d->m_systemPowerInter->powerSavingModeAutoWhenBatteryLow();
}

void DPowerSettings::setAutoPowerSavingWhenBatteryLow(const bool enabled)
{
    Q_D(DPowerSettings);
    d->m_systemPowerInter->setPowerSavingModeAutoWhenBatteryLow(enabled);
}

quint32 DPowerSettings::powerSavingBrightnessDropPercent() const
{
    Q_D(const DPowerSettings);
    return d->m_systemPowerInter->powerSavingModeBrightnessDropPercent();
}

void DPowerSettings::setPowerSavingBrightnessDropPercent(const quint32 value)
{
    Q_D(DPowerSettings);
    d->m_systemPowerInter->setPowerSavingModeBrightnessDropPercent(value);
}

LidClosedAction DPowerSettings::batteryLidClosedAction() const
{
    Q_D(const DPowerSettings);
    auto action = d->m_daemonPowerInter->batteryLidClosedAction();
    if (action < 1 || action > 4)
        return LidClosedAction::Unknown;
    return static_cast<LidClosedAction>(action);
}

void DPowerSettings::setBatteryLidClosedAction(const LidClosedAction &value)
{
    Q_D(DPowerSettings);
    if (value == LidClosedAction::Unknown)
        return;

    d->m_daemonPowerInter->setBatteryLidClosedAction(static_cast<qint32>(value));
}

qint32 DPowerSettings::batteryLockDelay() const
{
    Q_D(const DPowerSettings);
    return d->m_daemonPowerInter->batteryLockDelay();
}

void DPowerSettings::setBatteryLockDelay(const qint32 value)
{
    Q_D(DPowerSettings);
    d->m_daemonPowerInter->setBatteryLockDelay(value);
}

PowerBtnAction DPowerSettings::batteryPressPowerBtnAction() const
{
    Q_D(const DPowerSettings);
    auto action = d->m_daemonPowerInter->batteryPressPowerBtnAction();
    if (action < 0 || action > 4)
        return PowerBtnAction::Unknown;
    return static_cast<PowerBtnAction>(action);
}

void DPowerSettings::setBatteryPressPowerBtnAction(const PowerBtnAction &value)
{
    Q_D(DPowerSettings);
    if (value == PowerBtnAction::Unknown)
        return;
    d->m_daemonPowerInter->setBatteryPressPowerBtnAction(static_cast<qint32>(value));
}

qint32 DPowerSettings::batteryScreenBlackDelay() const
{
    Q_D(const DPowerSettings);
    return d->m_daemonPowerInter->batteryScreenBlackDelay();
}

void DPowerSettings::setBatteryScreenBlackDelay(const qint32 value)
{
    Q_D(DPowerSettings);
    d->m_daemonPowerInter->setBatteryScreenBlackDelay(value);
}

qint32 DPowerSettings::batteryScreensaverDelay() const
{
    Q_D(const DPowerSettings);
    return d->m_daemonPowerInter->batteryScreensaverDelay();
}

void DPowerSettings::setBatteryScreensaverDelay(const qint32 value)
{
    Q_D(DPowerSettings);
    d->m_daemonPowerInter->setBatteryScreensaverDelay(value);
}

qint32 DPowerSettings::batterySleepDelay() const
{
    Q_D(const DPowerSettings);
    return d->m_daemonPowerInter->batterySleepDelay();
}

void DPowerSettings::setBatterySleepDelay(const qint32 value)
{
    Q_D(DPowerSettings);
    d->m_daemonPowerInter->setBatterySleepDelay(value);
}

LidClosedAction DPowerSettings::linePowerLidClosedAction() const
{
    Q_D(const DPowerSettings);
    auto action = d->m_daemonPowerInter->linePowerLidClosedAction();
    if (action < 1 || action > 4)
        return LidClosedAction::Unknown;
    return static_cast<LidClosedAction>(action);
}

void DPowerSettings::setLinePowerLidClosedAction(const LidClosedAction &value)
{
    Q_D(DPowerSettings);
    if (value == LidClosedAction::Unknown)
        return;
    d->m_daemonPowerInter->setLinePowerLidClosedAction(static_cast<qint32>(value));
}

qint32 DPowerSettings::linePowerLockDelay() const
{
    Q_D(const DPowerSettings);
    return d->m_daemonPowerInter->linePowerLockDelay();
}

void DPowerSettings::setLinePowerLockDelay(const qint32 value)
{
    Q_D(DPowerSettings);
    d->m_daemonPowerInter->setLinePowerLockDelay(value);
}

PowerBtnAction DPowerSettings::linePowerPressPowerBtnAction() const
{
    Q_D(const DPowerSettings);
    auto action = d->m_daemonPowerInter->linePowerPressPowerBtnAction();
    if (action < 0 || action > 4)
        return PowerBtnAction::Unknown;
    return static_cast<PowerBtnAction>(action);
}

void DPowerSettings::setLinePowerPressPowerBtnAction(const PowerBtnAction &value)
{
    Q_D(DPowerSettings);
    if (value == PowerBtnAction::Unknown)
        return;
    d->m_daemonPowerInter->setLinePowerPressPowerBtnAction(static_cast<qint32>(value));
}

qint32 DPowerSettings::linePowerScreenBlackDelay() const
{
    Q_D(const DPowerSettings);
    return d->m_daemonPowerInter->linePowerScreenBlackDelay();
}

void DPowerSettings::setLinePowerScreenBlackDelay(const qint32 value)
{
    Q_D(DPowerSettings);
    d->m_daemonPowerInter->setLinePowerScreenBlackDelay(value);
}

qint32 DPowerSettings::linePowerScreensaverDelay() const
{
    Q_D(const DPowerSettings);
    return d->m_daemonPowerInter->linePowerScreensaverDelay();
}

void DPowerSettings::setLinePowerScreensaverDelay(const qint32 value)
{
    Q_D(DPowerSettings);
    d->m_daemonPowerInter->setLinePowerScreensaverDelay(value);
}

qint32 DPowerSettings::linePowerSleepDelay() const
{
    Q_D(const DPowerSettings);
    return d->m_daemonPowerInter->linePowerSleepDelay();
}

void DPowerSettings::setLinePowerSleepDelay(const qint32 value)
{
    Q_D(DPowerSettings);
    d->m_daemonPowerInter->setLinePowerSleepDelay(value);
}

qint32 DPowerSettings::lowPowerAutoSleepThreshold() const
{
    Q_D(const DPowerSettings);
    return d->m_daemonPowerInter->lowPowerAutoSleepThreshold();
}

void DPowerSettings::setLowPowerAutoSleepThreshold(const qint32 value)
{
    Q_D(DPowerSettings);
    d->m_daemonPowerInter->setLowPowerAutoSleepThreshold(value);
}

bool DPowerSettings::lowPowerNotifyEnable() const
{
    Q_D(const DPowerSettings);
    return d->m_daemonPowerInter->lowPowerNotifyEnable();
}

void DPowerSettings::setLowPowerNotifyEnable(const bool value)
{
    Q_D(const DPowerSettings);
    d->m_daemonPowerInter->setLowPowerNotifyEnable(value);
}

qint32 DPowerSettings::lowPowerNotifyThreshold() const
{
    Q_D(const DPowerSettings);
    return d->m_daemonPowerInter->lowPowerNotifyThreshold();
}

void DPowerSettings::setLowPowerNotifyThreshold(const qint32 value)
{
    Q_D(DPowerSettings);
    d->m_daemonPowerInter->setLowPowerNotifyThreshold(value);
}

bool DPowerSettings::screenBlackLock() const
{
    Q_D(const DPowerSettings);
    return d->m_daemonPowerInter->screenBlackLock();
}

void DPowerSettings::setScreenBlackLock(const bool value)
{
    Q_D(DPowerSettings);
    d->m_daemonPowerInter->setScreenBlackLock(value);
}

bool DPowerSettings::sleepLock() const
{
    Q_D(const DPowerSettings);
    return d->m_daemonPowerInter->sleepLock();
}

void DPowerSettings::setSleepLock(const bool value)
{
    Q_D(DPowerSettings);
    d->m_daemonPowerInter->setSleepLock(value);
}

void DPowerSettings::reset()
{
    Q_D(DPowerSettings);
    auto reply = d->m_daemonPowerInter->reset();
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}
DPOWER_END_NAMESPACE

// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "powerdemo.h"
#include <qdebug.h>
#include <iostream>
#include <string>
#include "dlogintypes.h"

PowerDemo::PowerDemo(QObject *parent)
    : Demo(parent)
    , m_manager(new DLoginManager)
{
}

int PowerDemo::run()
{
    m_manager->inhibit(InhibitBehavior::Sleep, "demo", "block reboot", InhibitMode::Block);
    m_manager->inhibit(InhibitBehavior::Shutdown, "demo", "delay shutdown", InhibitMode::Delay);
    qDebug() << m_manager->listInhibitors();
    qDebug() << m_manager->canSuspend();
    qDebug() << m_manager->canPowerOff();
    auto time = QDateTime::currentDateTime();
    m_manager->scheduleShutdown(ShutdownType::Reboot, time.addSecs(1000));
    qDebug() << m_manager->scheduledShutdown();
    m_manager->cancelScheduledShutdown();
    qDebug() << m_manager->scheduledShutdown();
    std::string str;
    getline(std::cin, str);
    m_manager->powerOff(false);
    return 0;
}

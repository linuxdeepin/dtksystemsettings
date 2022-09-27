// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <gtest/gtest.h>

#include "dpowersettings.h"
#include "dbus/fakedaemonpowerinterface.h"
#include <QDBusMessage>
#include <QDBusConnection>
#include <QDBusReply>

DPOWER_USE_NAMESPACE

class TestDPowerSettings : public testing::Test {
public:
    // 在测试套件的第一个测试用例开始前，SetUpTestCase 函数会被调用
    static void SetUpTestCase() {
        m_fakeInterface = new FakeDaemonPowerInterface();
        m_dpowerSettings = new DPowerSettings();
    }
    // 在测试套件中的最后一个测试用例运行结束后，TearDownTestCase 函数会被调用
    static void TearDownTestCase() {
        delete m_fakeInterface;
        delete m_dpowerSettings;
        m_fakeInterface = nullptr;
        m_dpowerSettings = nullptr;
    }

    // 每个测试用例开始前，SetUp 函数都会被被调用
    void SetUp() override {}
    // 每个测试用例运行结束后，TearDown 函数都会被被调用
    void TearDown() override {}

    static FakeDaemonPowerInterface *m_fakeInterface;
    static DPowerSettings *m_dpowerSettings;
};

FakeDaemonPowerInterface *TestDPowerSettings::m_fakeInterface = nullptr;
DPowerSettings *TestDPowerSettings::m_dpowerSettings = nullptr;

TEST_F(TestDPowerSettings, reset)
{
    EXPECT_EQ(false, m_fakeInterface->m_reset);

    m_dpowerSettings->reset();

    EXPECT_EQ(true, m_fakeInterface->m_reset);
}

TEST_F(TestDPowerSettings, daemonProperty)
{
    m_dpowerSettings->setBatteryLidClosedAction(3);
    EXPECT_EQ(3, m_fakeInterface->m_batteryLidClosedAction);
    EXPECT_EQ(3, m_dpowerSettings->batteryLidClosedAction());
    m_fakeInterface->setBatteryLidClosedAction(3);
    EXPECT_EQ(3, m_fakeInterface->m_batteryLidClosedAction);
    EXPECT_EQ(3, m_dpowerSettings->batteryLidClosedAction());
    m_dpowerSettings->setSleepLock(true);
}

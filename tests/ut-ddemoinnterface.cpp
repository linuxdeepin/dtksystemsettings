// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <gtest/gtest.h>
#include <QDebug>
#include <QDBusObjectPath>

#include "ddemointerface.h"
#include "dfakeinterface.h"

class ut_DDemoInterface : public testing::Test {
public:
    // 在测试套件的第一个测试用例开始前，SetUpTestCase 函数会被调用
    static void SetUpTestCase() {
        m_demoInterface = new DDemoInterface ();
        m_fakeInterface = new DFakeInterface();
    }
    // 在测试套件中的最后一个测试用例运行结束后，TearDownTestCase 函数会被调用
    static void TearDownTestCase() {
        delete m_fakeInterface;
        delete m_demoInterface;
        m_fakeInterface = nullptr;
        m_demoInterface = nullptr;
    }

    // 每个测试用例开始前，SetUp 函数都会被被调用
    void SetUp() override {}
    // 每个测试用例运行结束后，TearDown 函数都会被被调用
    void TearDown() override {}

    static DFakeInterface *m_fakeInterface;
    static DDemoInterface *m_demoInterface;
};

DFakeInterface *ut_DDemoInterface::m_fakeInterface = nullptr;
DDemoInterface *ut_DDemoInterface::m_demoInterface = nullptr;

TEST_F(ut_DDemoInterface, DockedProperty)
{
    EXPECT_EQ(false, m_demoInterface->Docked());

    m_fakeInterface->setProperty("Docked", true);

    EXPECT_EQ(true, m_demoInterface->Docked());
}

TEST_F(ut_DDemoInterface, ListUsers)
{
    UserPathList list;
    EXPECT_EQ(list, m_demoInterface->ListUsers());

    list.push_back({1000, QDBusObjectPath("/org/freedesktop/login1/user/_1000")});

    m_fakeInterface->setListUsers(list);

    EXPECT_EQ(list, m_demoInterface->ListUsers());
}

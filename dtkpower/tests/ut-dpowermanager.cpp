// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <gtest/gtest.h>
#include "3rdparty/cpp-stub/src/stub.h"
#include "dpowermanager.h"

DPOWER_USE_NAMESPACE
class ut_DPowerManager:public  testing::Test
{
public:
    void SetUp() override
    {
        m_manager = new DPowerManager;
    }
    void TearDown() override
    {
        delete m_manager;
        m_manager = nullptr;
    }

public:
    DPowerManager *m_manager = nullptr;
};


bool lidlsClosed_stub()
{
    return true;
}


TEST_F(ut_DPowerManager,DPowerManager)
{
    Stub stub;
    stub.set(ADDR(DPowerManager,lidlsClosed),lidlsClosed_stub);
    EXPECT_TRUE(m_manager->lidlsClosed());
}


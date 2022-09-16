// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <gtest/gtest.h>
#include "3rdparty/cpp-stub/src/stub.h"
#include "dkbdbacklight.h"

DPOWER_USE_NAMESPACE
class ut_DKdbBacklight:public  testing::Test
{
public:
    void SetUp() override { m_backlight = new DKbdBacklight; }
    void TearDown() override
    {
        delete m_backlight;
        m_backlight = nullptr;
    }

public:
    DKbdBacklight *m_backlight = nullptr;
};

uint getBrightness_stub()
{
    return 1;
}

TEST_F(ut_DKdbBacklight,getBrightness)
{
    Stub stub;
    stub.set(ADDR(DKbdBacklight,getBrightness),getBrightness_stub);
    EXPECT_EQ(m_backlight->getBrightness(),1);
}

uint getMaxBrightness_stub()
{
    return 1;
}

TEST_F(ut_DKdbBacklight,getMaxBrightness_stub)
{
    Stub stub;
    stub.set(ADDR(DKbdBacklight,getMaxBrightness),getMaxBrightness_stub);
    EXPECT_EQ(m_backlight->getMaxBrightness(),1);
}

int a = 0;
void setBrightness_stub(uint value)
{
    a=1;
}

TEST_F(ut_DKdbBacklight,setBrightness_stub)
{
    Stub stub;
    stub.set(ADDR(DKbdBacklight,setBrightness),setBrightness_stub);
    m_backlight->setBrightness(1);
    EXPECT_EQ(a,1);
}

// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "gtest/gtest.h"
#include "include/demo.h"

DDEMO_USE_NAMESPACE

class ut_Demo : public testing::Test
{
public:
    void SetUp() override
    {
        m_demo = new Demo;
    }
    void TearDown() override
    {
        delete m_demo;
        m_demo = nullptr;
    }
public:
    Demo *m_demo = nullptr;
};

TEST_F(ut_Demo, add)
{
    EXPECT_EQ(3, m_demo->add(1, 2));
}

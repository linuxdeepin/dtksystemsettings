// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <gtest/gtest.h>
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



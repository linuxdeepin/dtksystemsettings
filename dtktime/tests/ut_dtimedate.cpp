// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
#include <gtest/gtest.h>

#include "dtimedate.h"
#include "fakedbus/timedate1service.h"
#include <QDBusConnection>
#include <qdebug.h>
DTIME_USE_NAMESPACE

class TestDTimeDate : public testing::Test
{
public:
    static void SetUpTestCase()
    {
        m_fakeInterface = new TimeDate1Service();
        m_dtimedate = new DTimeDate();
    }

    static void TearDownTestCase()
    {
        delete m_fakeInterface;
        delete m_dtimedate;
        m_fakeInterface = nullptr;
        m_dtimedate = nullptr;
    }

    void SetUp() override {}
    void TearDown() override {}

    static TimeDate1Service *m_fakeInterface;
    static DTimeDate *m_dtimedate;
};

TimeDate1Service *TestDTimeDate::m_fakeInterface = nullptr;
DTimeDate *TestDTimeDate::m_dtimedate = nullptr;

QT_BEGIN_NAMESPACE  // for QString support
    inline void
    PrintTo(const QString &qString, ::std::ostream *os)
{
    *os << qUtf8Printable(qString);
}
QT_END_NAMESPACE

TEST_F(TestDTimeDate, canNTP)  // return true
{
    ASSERT_TRUE(m_fakeInterface->canNTP());
    EXPECT_TRUE(m_dtimedate->canNTP());
}

TEST_F(TestDTimeDate, localRTC)  // return true
{
    ASSERT_TRUE(m_fakeInterface->localRTC());
    EXPECT_TRUE(m_dtimedate->localRTC());
}

TEST_F(TestDTimeDate, NTP)  // return true
{
    ASSERT_TRUE(m_fakeInterface->NTP());
    EXPECT_TRUE(m_dtimedate->NTP());
}

TEST_F(TestDTimeDate, NTPSynchronized)  // return true
{
    ASSERT_TRUE(m_fakeInterface->NTPSynchronized());
    EXPECT_TRUE(m_dtimedate->NTPSynchronized());
}

TEST_F(TestDTimeDate, timezone)  // return Asia/Tokyo
{
    ASSERT_EQ("Asia/Tokyo", m_fakeInterface->timeZone());
    EXPECT_EQ("Asia/Tokyo", m_dtimedate->timeZone());
}

TEST_F(TestDTimeDate, RTCTimeUSec)  // return 42
{
    ASSERT_EQ(42, m_fakeInterface->RTCTimeUSec());
    EXPECT_EQ(42, m_dtimedate->RTCTimeUSec());
}

TEST_F(TestDTimeDate, timeUSec)  // return 24
{
    ASSERT_EQ(24, m_fakeInterface->timeUSec());
    EXPECT_EQ(24, m_dtimedate->timeUSec());
}

TEST_F(TestDTimeDate, ListTimeZones)  // return {"Asia/Tokyo", "Asia/Shanghai", "Asia/Hongkong", "Asia/Korea"}
{
    ASSERT_EQ("Asia/Hongkong", m_fakeInterface->ListTimeZones()[2]);
    EXPECT_EQ("Asia/Korea", m_dtimedate->listTimeZones()[3]);
}

TEST_F(TestDTimeDate, SetLocalRTC)  // focus local_rtc
{
    m_fakeInterface->SetLocalRTC(true, false, false);
    ASSERT_TRUE(m_fakeInterface->setLocalRTC_sig);
    m_dtimedate->setLocalRTC(false, false, false);
    EXPECT_FALSE(m_fakeInterface->setLocalRTC_sig);
}

TEST_F(TestDTimeDate, SetLocalTime)  // focus use_NTP
{
    m_fakeInterface->SetLocalTime(true, false);
    ASSERT_TRUE(m_fakeInterface->setLocalTime_sig);
    m_dtimedate->setLocalTime(false, false);
    EXPECT_FALSE(m_fakeInterface->setLocalTime_sig);
}

TEST_F(TestDTimeDate, SetTime)  // focus usec_utc
{
    m_fakeInterface->SetTime(42, false, false);
    ASSERT_EQ(42, m_fakeInterface->setTime_sig);
    m_dtimedate->setTime(24, false, false);
    EXPECT_EQ(24, m_fakeInterface->setTime_sig);
}

TEST_F(TestDTimeDate, SetTimeZone)  // focus timezone
{
    m_fakeInterface->SetTimeZone("Asia/Shanghai", true);
    ASSERT_EQ("Asia/Shanghai", m_fakeInterface->setTimeZone_sig);
    m_dtimedate->setTimeZone("Asia/Tokyo", true);
    EXPECT_EQ("Asia/Tokyo", m_fakeInterface->setTimeZone_sig);
}

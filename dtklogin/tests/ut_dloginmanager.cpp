// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dloginmanager.h"
#include "login1managerservice.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

DLOGIN_USE_NAMESPACE
class TestDLoginManager : public testing::Test
{
public:
    TestDLoginManager()
        : m_fakeService(new Login1ManagerService)
        , m_dLoginManager(new DLoginManager)
    {
    }

    ~TestDLoginManager()
    {
        delete m_fakeService;
        delete m_dLoginManager;
    }

protected:
    Login1ManagerService *m_fakeService;
    DLoginManager *m_dLoginManager;
};

TEST_F(TestDLoginManager, testKillExcludeUsers)
{
    m_fakeService->m_killExcludeUsers.clear();
    ASSERT_THAT(m_fakeService->m_killExcludeUsers, testing::IsEmpty());
    m_fakeService->m_killExcludeUsers << "User1000";
    ASSERT_THAT(m_fakeService->m_killExcludeUsers, testing::SizeIs(1));
    auto users = m_dLoginManager->killExcludeUsers();
    ASSERT_THAT(users, testing::SizeIs(1));
    EXPECT_EQ(users.front(), "User1000");
    m_fakeService->m_killExcludeUsers << "User1001";
    users = m_dLoginManager->killExcludeUsers();
    ASSERT_THAT(users, testing::SizeIs(2));
    EXPECT_EQ(users[1], "User1001");
}
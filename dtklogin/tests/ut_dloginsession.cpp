// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dloginsession.h"
#include "dloginsession_p.h"
#include "login1sessionservice.h"
#include "login1sessioninterface.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ddbusinterface.h"
#include "namespace.h"
#include "sessionmanagerservice.h"

DLOGIN_USE_NAMESPACE

class TestDLoginSession : public testing::Test
{
public:
    TestDLoginSession()
        : m_fakeService(new Login1SessionService)
        , m_sessionManagerService(new SessionManagerService)
        , m_dLoginSession(new DLoginSession("/org/freedesktop/login1/session"))
    {
        m_dLoginSession->d_ptr->m_inter->m_interface->setTimeout(INT_MAX);
    }

    virtual ~TestDLoginSession()
    {
        delete m_dLoginSession;
        delete m_fakeService;
        delete m_sessionManagerService;
    }

protected:
    Login1SessionService *m_fakeService;
    SessionManagerService *m_sessionManagerService;
    DLoginSession *m_dLoginSession;
    static const QString Service;
};
const QString TestDLoginSession::Service = QStringLiteral("org.freedesktop.fakelogin1");

TEST_F(TestDLoginSession, propertyActive)
{
    m_fakeService->m_active = false;
    ASSERT_FALSE(m_fakeService->active());
    EXPECT_FALSE(m_dLoginSession->active());
    m_fakeService->m_active = true;
    ASSERT_TRUE(m_fakeService->active());
    EXPECT_TRUE(m_dLoginSession->active());
}

TEST_F(TestDLoginSession, propertyIdleHint)
{
    m_fakeService->m_idleHint = false;
    ASSERT_FALSE(m_fakeService->idleHint());
    EXPECT_FALSE(m_dLoginSession->idleHint());
    m_fakeService->m_idleHint = true;
    ASSERT_TRUE(m_fakeService->idleHint());
    EXPECT_TRUE(m_dLoginSession->idleHint());
}

TEST_F(TestDLoginSession, propertyLocked)
{
    m_sessionManagerService->m_locked = false;
    ASSERT_FALSE(m_sessionManagerService->Locked());
    EXPECT_FALSE(m_dLoginSession->locked());
    m_sessionManagerService->m_locked = true;
    ASSERT_TRUE(m_sessionManagerService->Locked());
    EXPECT_TRUE(m_dLoginSession->locked());
}

TEST_F(TestDLoginSession, propertyRemote)
{
    m_fakeService->m_remote = false;
    ASSERT_FALSE(m_fakeService->remote());
    EXPECT_FALSE(m_dLoginSession->remote());
    m_fakeService->m_remote = true;
    ASSERT_TRUE(m_fakeService->remote());
    EXPECT_TRUE(m_dLoginSession->remote());
}

struct SessionClassParam
{
    QString strClass;
    SessionClass enumClass;
};

class TestSessionClass : public TestDLoginSession, public testing::WithParamInterface<SessionClassParam>
{
public:
    TestSessionClass()
        : TestDLoginSession()
    {
    }
    ~TestSessionClass() override = default;
};

TEST_P(TestSessionClass, sessionClass)
{
    auto params = GetParam();
    m_fakeService->m_sessionClass = params.strClass;
    ASSERT_EQ(params.strClass, m_fakeService->sessionClass());
    EXPECT_EQ(params.enumClass, m_dLoginSession->sessionClass());
}

INSTANTIATE_TEST_CASE_P(Default,
                        TestSessionClass,
                        testing::Values(SessionClassParam{"greeter", SessionClass::Greeter},
                                        SessionClassParam{"lock-screen", SessionClass::LockScreen},
                                        SessionClassParam{"user", SessionClass::User},
                                        SessionClassParam{"", SessionClass::Unknown}));

TEST_F(TestDLoginSession, propertyDesktop)
{
    m_fakeService->m_desktop = "test string";
    ASSERT_EQ("test string", m_fakeService->desktop());
    EXPECT_EQ("test string", m_dLoginSession->desktop());
}

TEST_F(TestDLoginSession, propertyDisplay)
{
    m_fakeService->m_display = "test string";
    ASSERT_EQ("test string", m_fakeService->display());
    EXPECT_EQ("test string", m_dLoginSession->display());
}

TEST_F(TestDLoginSession, propertyId)
{
    m_fakeService->m_id = "test string";
    ASSERT_EQ("test string", m_fakeService->id());
    EXPECT_EQ("test string", m_dLoginSession->id());
}

TEST_F(TestDLoginSession, propertyName)
{
    m_fakeService->m_name = "test string";
    ASSERT_EQ("test string", m_fakeService->name());
    EXPECT_EQ("test string", m_dLoginSession->name());
}

TEST_F(TestDLoginSession, propertyRemoteHost)
{
    m_fakeService->m_remoteHost = "test string";
    ASSERT_EQ("test string", m_fakeService->remoteHost());
    EXPECT_EQ("test string", m_dLoginSession->remoteHost());
}

TEST_F(TestDLoginSession, propertyRemoteUser)
{
    m_fakeService->m_remoteUser = "test string";
    ASSERT_EQ("test string", m_fakeService->remoteUser());
    EXPECT_EQ("test string", m_dLoginSession->remoteUser());
}

TEST_F(TestDLoginSession, propertyScope)
{
    m_fakeService->m_scope = "test string";
    ASSERT_EQ("test string", m_fakeService->scope());
    EXPECT_EQ("test string", m_dLoginSession->scope());
}

TEST_F(TestDLoginSession, propertyService)
{
    m_fakeService->m_applicationService = "test string";
    ASSERT_EQ("test string", m_fakeService->service());
    EXPECT_EQ("test string", m_dLoginSession->service());
}

struct SessionStateParam
{
    QString strState;
    SessionState enumState;
};

class TestSessionState : public TestDLoginSession, public testing::WithParamInterface<SessionStateParam>
{
public:
    TestSessionState()
        : TestDLoginSession()
    {
    }
    ~TestSessionState() override = default;
};

TEST_P(TestSessionState, state)
{
    auto params = GetParam();
    m_fakeService->m_state = params.strState;
    ASSERT_EQ(params.strState, m_fakeService->state());
    EXPECT_EQ(params.enumState, m_dLoginSession->state());
}

INSTANTIATE_TEST_CASE_P(Default,
                        TestSessionState,
                        testing::Values(SessionStateParam{"active", SessionState::Active},
                                        SessionStateParam{"closing", SessionState::Closing},
                                        SessionStateParam{"online", SessionState::Online},
                                        SessionStateParam{"", SessionState::Unknown}));

struct SessionTypeParam
{
    QString strType;
    SessionType enumType;
};

class TestSessionType : public TestDLoginSession, public testing::WithParamInterface<SessionTypeParam>
{
public:
    TestSessionType()
        : TestDLoginSession()
    {
    }
    ~TestSessionType() override = default;
};

TEST_P(TestSessionType, type)
{
    auto params = GetParam();
    m_fakeService->m_type = params.strType;
    ASSERT_EQ(params.strType, m_fakeService->type());
    EXPECT_EQ(params.enumType, m_dLoginSession->type());
}

INSTANTIATE_TEST_CASE_P(Default,
                        TestSessionType,
                        testing::Values(SessionTypeParam{"x11", SessionType::X11},
                                        SessionTypeParam{"wayland", SessionType::Wayland},
                                        SessionTypeParam{"tty", SessionType::TTY},
                                        SessionTypeParam{"mir", SessionType::Mir},
                                        SessionTypeParam{"unspecified", SessionType::Unspecified}));

TEST_F(TestDLoginSession, propertyTTY)
{
    m_fakeService->m_TTY = "test string";
    ASSERT_EQ("test string", m_fakeService->TTY());
    EXPECT_EQ("test string", m_dLoginSession->TTY());
}

TEST_F(TestDLoginSession, seat)
{
    m_fakeService->m_seat.seatId = "seat0";
    m_fakeService->m_seat.path = QDBusObjectPath("/org/freedesktop/login1/seat");
    ASSERT_EQ("seat0", m_fakeService->seat().seatId);
    EXPECT_EQ("seat0", m_dLoginSession->seat());
}

TEST_F(TestDLoginSession, user)
{
    m_fakeService->m_user.userId = 1000;
    m_fakeService->m_user.path = QDBusObjectPath("/org/freedesktop/login1/user");
    ASSERT_EQ(1000, m_fakeService->user().userId);
    EXPECT_EQ(1000, m_dLoginSession->user());
}

TEST_F(TestDLoginSession, propertyAudit)
{
    m_fakeService->m_audit = 1024;
    ASSERT_EQ(1024, m_fakeService->audit());
    EXPECT_EQ(1024, m_dLoginSession->audit());
    m_fakeService->m_audit = 2048;
    ASSERT_EQ(2048, m_fakeService->audit());
    EXPECT_EQ(2048, m_dLoginSession->audit());
}

TEST_F(TestDLoginSession, propertyLeader)
{
    m_fakeService->m_leader = 1024;
    ASSERT_EQ(1024, m_fakeService->leader());
    EXPECT_EQ(1024, m_dLoginSession->leader());
    m_fakeService->m_leader = 2048;
    ASSERT_EQ(2048, m_fakeService->leader());
    EXPECT_EQ(2048, m_dLoginSession->leader());
}

TEST_F(TestDLoginSession, propertyVTNr)
{
    m_fakeService->m_VTNr = 1024;
    ASSERT_EQ(1024, m_fakeService->VTNr());
    EXPECT_EQ(1024, m_dLoginSession->VTNr());
    m_fakeService->m_VTNr = 2048;
    ASSERT_EQ(2048, m_fakeService->VTNr());
    EXPECT_EQ(2048, m_dLoginSession->VTNr());
}
TEST_F(TestDLoginSession, propertyIdleSinceHint)
{
    m_fakeService->m_idleSinceHint = 1500;
    ASSERT_EQ(1500, m_fakeService->idleSinceHint());
    EXPECT_EQ(1500, m_dLoginSession->idleSinceHint().toMSecsSinceEpoch());
}
TEST_F(TestDLoginSession, propertyIdleSinceHintMonotonic)
{
    m_fakeService->m_idleSinceHintMonotonic = 1024;
    ASSERT_EQ(1024, m_fakeService->idleSinceHintMonotonic());
    EXPECT_EQ(1024, m_dLoginSession->idleSinceHintMonotonic());
    m_fakeService->m_idleSinceHintMonotonic = 2048;
    ASSERT_EQ(2048, m_fakeService->idleSinceHintMonotonic());
    EXPECT_EQ(2048, m_dLoginSession->idleSinceHintMonotonic());
}

TEST_F(TestDLoginSession, propertyCreatedTime)
{
    m_fakeService->m_timestamp = 1500;
    ASSERT_EQ(1500, m_fakeService->timestamp());
    EXPECT_EQ(1500, m_dLoginSession->createdTime().toMSecsSinceEpoch());
}

TEST_F(TestDLoginSession, propertyCreatedTimeMonotonic)
{
    m_fakeService->m_timestampMonotonic = 1024;
    ASSERT_EQ(1024, m_fakeService->timestampMonotonic());
    EXPECT_EQ(1024, m_dLoginSession->createdTimeMonotonic());
    m_fakeService->m_timestampMonotonic = 2048;
    ASSERT_EQ(2048, m_fakeService->timestampMonotonic());
    EXPECT_EQ(2048, m_dLoginSession->createdTimeMonotonic());
}

TEST_F(TestDLoginSession, activate)
{
    m_fakeService->m_active = false;
    m_dLoginSession->activate();
    EXPECT_TRUE(m_fakeService->m_active);
}

TEST_F(TestDLoginSession, kill)
{
    m_fakeService->m_who = "";
    m_fakeService->m_signalNumber = -1;
    m_dLoginSession->kill("uos", 8);
    EXPECT_EQ("uos", m_fakeService->m_who);
    EXPECT_EQ(8, m_fakeService->m_signalNumber);
}

TEST_F(TestDLoginSession, lock)
{
    m_fakeService->m_lockedHint = false;
    m_dLoginSession->lock();
    EXPECT_TRUE(m_fakeService->m_lockedHint);
}

TEST_F(TestDLoginSession, setIdleHint)
{
    m_fakeService->m_idleHint = false;
    m_dLoginSession->setIdleHint(true);
    EXPECT_TRUE(m_fakeService->m_idleHint);
}

TEST_F(TestDLoginSession, setLocked)
{
    m_sessionManagerService->m_locked = false;
    m_dLoginSession->setLocked(true);
    EXPECT_TRUE(m_sessionManagerService->m_locked);
}

TEST_P(TestSessionType, setType)
{
    auto params = GetParam();
    m_fakeService->m_type = "";
    m_dLoginSession->setType(params.enumType);
    EXPECT_EQ(params.strType, m_fakeService->m_type);
}

TEST_F(TestDLoginSession, terminate)
{
    m_fakeService->m_terminated = false;
    m_dLoginSession->terminate();
    EXPECT_TRUE(m_fakeService->m_terminated);
}

// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "namespace.h"
#include <qobject.h>
#include <qvariant.h>
#include <qdatetime.h>

DLOGIN_BEGIN_NAMESPACE
// Do not use any unknown enum
enum class ShutdownType { PowerOff, DryPowerOff, Reboot, DryReboot, Halt, DryHalt, Unknown };
struct ScheduledShutdownValue
{
    ShutdownType type;
    QDateTime time;
};
namespace InhibitBehavior {
constexpr uint Shutdown = 1 << 0;
constexpr uint Sleep = 1 << 1;
constexpr uint Idle = 1 << 2;
constexpr uint HandlePowerKey = 1 << 3;
constexpr uint HandleSuspendKey = 1 << 4;
constexpr uint HandleHibernateKey = 1 << 5;
constexpr uint HandleLidSwitch = 1 << 6;
};  // namespace InhibitBehavior

enum class PowerAction {
    PowerOff,
    Reboot,
    Halt,
    KExec,
    Suspend,
    Hibernate,
    HybridSleep,
    SuspendThenHibernate,
    Lock,
    FactoryReset,
    Ignore,
    Unknown
};
enum class ExecuteStatus { Yes, No, Challenge, Na, Unknown };
enum class SessionRole { Leader, All, Unknown };
enum class InhibitMode { Block, Delay, Unknown };
enum class SessionState { Online, Active, Closing, Unknown };
enum class SessionType { TTY, X11, Mir, Wayland, Unspecified };
enum class SessionClass { User, Greeter, LockScreen, Unknown };
enum class UserState { Offline, Lingering, Online, Active, Closing, Unknown };

struct Inhibitor
{
    quint32 what;
    QString who;
    QString why;
    InhibitMode mode;
    quint32 UID;
    quint32 PID;
};

DLOGIN_END_NAMESPACE

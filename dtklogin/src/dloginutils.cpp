// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dloginutils.h"
#include <qmap.h>
#include <qdebug.h>
DLOGIN_BEGIN_NAMESPACE

namespace Utils {
using namespace InhibitBehavior;
QString decodeBehavior(uint behavior)
{
    static const QMap<uint, QString> behaviorMap = {{Shutdown, "shutdown"},
                                                    {Sleep, "sleep"},
                                                    {Idle, "idle"},
                                                    {HandlePowerKey, "handle-power-key"},
                                                    {HandleSuspendKey, "handle-suspend-key"},
                                                    {HandleHibernateKey, "handle-hibernate-key"},
                                                    {HandleLidSwitch, "handle-lid-switch"}};
    QString decoded;
    for (auto it = behaviorMap.begin(); it != behaviorMap.end(); it++) {
        if (behavior & it.key()) {
            decoded += it.value();
            decoded += ":";
        }
    }
    if (!decoded.isEmpty()) {
        decoded.chop(1);
    }
    return decoded;
}
uint encodeBehavior(const QString &behavior)
{
    static const QMap<QString, uint> behaviorMap = {{"shutdown", Shutdown},
                                                    {"sleep", Sleep},
                                                    {"idle", Idle},
                                                    {"handle-power-key", HandlePowerKey},
                                                    {"handle-suspend-key", HandleSuspendKey},
                                                    {"handle-hibernate-key", HandleHibernateKey},
                                                    {"handle-lid-switch", HandleLidSwitch}};
    uint result = 0;
    QStringList behaviors = behavior.split(":");
    foreach (const QString &strBehavior, behaviors) {
        if (behaviorMap.contains(strBehavior)) {
            result |= behaviorMap[strBehavior];
        }
    }
    return result;
}
QString modeToString(const InhibitMode &mode)
{
    static const QMap<InhibitMode, QString> modeMap = {{InhibitMode::Block, "block"}, {InhibitMode::Delay, "delay"}};
    return modeMap[mode];
}
InhibitMode stringToMode(const QString &strMode)
{
    if (strMode == "block") {
        return InhibitMode::Block;
    } else {
        return InhibitMode::Delay;
    }
}
DBusInhibitor inhibitorToDBus(const Inhibitor &inhibitor)
{
    DBusInhibitor dBusInhibitor;
    dBusInhibitor.what = decodeBehavior(inhibitor.what);
    dBusInhibitor.who = inhibitor.who;
    dBusInhibitor.why = inhibitor.why;
    dBusInhibitor.mode = modeToString(inhibitor.mode);
    dBusInhibitor.PID = inhibitor.PID;
    dBusInhibitor.UID = inhibitor.UID;
    return dBusInhibitor;
}
Inhibitor inhibitorFromDBus(const DBusInhibitor &inhibitorDBus)
{
    Inhibitor inhibitor;
    inhibitor.what = encodeBehavior(inhibitorDBus.what);
    inhibitor.who = inhibitorDBus.who;
    inhibitor.why = inhibitorDBus.why;
    inhibitor.mode = stringToMode(inhibitorDBus.mode);
    inhibitor.PID = inhibitorDBus.PID;
    inhibitor.UID = inhibitorDBus.UID;
    return inhibitor;
}
QString statusToString(const ExecuteStatus &status)
{
    switch (status) {
        case ExecuteStatus::Yes:
            return "yes";
        case ExecuteStatus::No:
            return "no";
        case ExecuteStatus::Challenge:
            return "challenge";
        case ExecuteStatus::Na:
            return "na";
        default:
            qWarning() << "Not supported status";
            return "";
    }
}
ExecuteStatus stringToStatus(const QString &strStatus)
{
    if (strStatus == "yes") {
        return ExecuteStatus::Yes;
    } else if (strStatus == "no") {
        return ExecuteStatus::No;
    } else if (strStatus == "challenge") {
        return ExecuteStatus::Challenge;
    } else {
        return ExecuteStatus::Na;
    }
}
QString sessionRoleToString(const SessionRole &sessionRole)
{
    switch (sessionRole) {
        case SessionRole::Leader:
            return "leader";
        case SessionRole::All:
            return "all";
        default:
            qWarning() << "Not supported session role.";
            return "";
    }
}
SessionRole stringToSessionRole(const QString &strSessionRole)
{
    if (strSessionRole == "leader") {
        return SessionRole::Leader;
    } else {
        return SessionRole::All;
    }
}
PowerOffAction stringToAction(const QString &strAction)
{
    static const QMap<QString, PowerOffAction> actionMap = {{"poweroff", PowerOffAction::PowerOff},
                                                            {"reboot", PowerOffAction::Reboot},
                                                            {"halt", PowerOffAction::Halt},
                                                            {"kexec", PowerOffAction::KExec},
                                                            {"suspend", PowerOffAction::Suspend},
                                                            {"hibernate", PowerOffAction::Hibernate},
                                                            {"hybrid-sleep", PowerOffAction::HybridSleep},
                                                            {"suspend-then-hibernate", PowerOffAction::SuspendThenHibernate},
                                                            {"lock", PowerOffAction::Lock},
                                                            {"ignore", PowerOffAction::Ignore}};
    if (actionMap.contains(strAction)) {
        return actionMap[strAction];
    } else {
        qWarning() << "Not supported action.";
        return PowerOffAction::Ignore;
    }
}
QString actionToString(const PowerOffAction &action)
{
    static const QMap<PowerOffAction, QString> actionMap = {{PowerOffAction::PowerOff, "poweroff"},
                                                            {PowerOffAction::Reboot, "reboot"},
                                                            {PowerOffAction::Halt, "halt"},
                                                            {PowerOffAction::KExec, "kexec"},
                                                            {PowerOffAction::Suspend, "suspend"},
                                                            {PowerOffAction::Hibernate, "hibernate"},
                                                            {PowerOffAction::HybridSleep, "hybrid-sleep"},
                                                            {PowerOffAction::SuspendThenHibernate, "suspend-then-hibernate"},
                                                            {PowerOffAction::FactoryReset, "factory-reset"},
                                                            {PowerOffAction::Lock, "lock"},
                                                            {PowerOffAction::Ignore, "ignore"},
                                                            {PowerOffAction::Unknown, ""}};
    return actionMap[action];
}
QString shutdownTypeToString(const ShutdownType &type)
{
    static const QMap<ShutdownType, QString> typeMap = {{ShutdownType::PowerOff, "poweroff"},
                                                        {ShutdownType::DryPowerOff, "dry-poweroff"},
                                                        {ShutdownType::Reboot, "reboot"},
                                                        {ShutdownType::DryReboot, "dry-reboot"},
                                                        {ShutdownType::Halt, "halt"},
                                                        {ShutdownType::DryHalt, "dry-halt"},
                                                        {ShutdownType::Unknown, ""}};
    return typeMap[type];
}
ShutdownType stringToShutdownType(const QString &strType)
{
    static const QMap<QString, ShutdownType> typeMap = {{"poweroff", ShutdownType::PowerOff},
                                                        {"dry-poweroff", ShutdownType::DryPowerOff},
                                                        {"reboot", ShutdownType::Reboot},
                                                        {"dry-reboot", ShutdownType::DryReboot},
                                                        {"halt", ShutdownType::Halt},
                                                        {"dry-halt", ShutdownType::DryHalt}};
    if (typeMap.contains(strType)) {
        return typeMap[strType];
    } else {
        qWarning() << "Not supported shutdown type.";
        return ShutdownType::Unknown;
    }
}

QString sessionClassToString(const SessionClass &sessionClass)
{
    static const QMap<SessionClass, QString> classMap = {{SessionClass::User, "user"},
                                                         {SessionClass::Greeter, "greeter"},
                                                         {SessionClass::LockScreen, "lock-screen"},
                                                         {SessionClass::Unknown, ""}};
    return classMap[sessionClass];
}

SessionClass stringToSessionClass(const QString &strClass)
{
    if (strClass == "user") {
        return SessionClass::User;
    } else if (strClass == "greeter") {
        return SessionClass::Greeter;
    } else if (strClass == "lock-screen") {
        return SessionClass::LockScreen;
    } else {
        qWarning() << "Not supported session class.";
        return SessionClass::Unknown;
    }
}

QString sessionTypeToString(const SessionType &sessionType)
{
    static const QMap<SessionType, QString> sessionMap = {{SessionType::TTY, "tty"},
                                                          {SessionType::X11, "x11"},
                                                          {SessionType::Mir, "mir"},
                                                          {SessionType::Wayland, "wayland"},
                                                          {SessionType::Unspecified, "unspecified"}};
    return sessionMap[sessionType];
}
SessionType stringToSessionType(const QString &strType)
{
    static const QMap<QString, SessionType> sessionMap = {{"tty", SessionType::TTY},
                                                          {"x11", SessionType::X11},
                                                          {"mir", SessionType::Mir},
                                                          {"wayland", SessionType::Wayland},
                                                          {"unspecified", SessionType::Unspecified}};
    if (sessionMap.contains(strType)) {
        return sessionMap[strType];
    } else {
        qWarning() << "Not supported session type.";
        return SessionType::Unspecified;
    }
}
QString sessionStateToString(const SessionState &sessionState)
{
    static const QMap<SessionState, QString> stateMap = {{SessionState::Online, "online"},
                                                         {SessionState::Active, "active"},
                                                         {SessionState::Closing, "closing"},
                                                         {SessionState::Unknown, ""}};
    return stateMap[sessionState];
}
SessionState stringToSessionState(const QString &strState)
{
    if (strState == "online") {
        return SessionState::Online;
    } else if (strState == "active") {
        return SessionState::Active;
    } else if (strState == "closing") {
        return SessionState::Closing;
    } else {
        qWarning() << "Not supported session state.";
        return SessionState::Unknown;
    }
}
QString userStateToString(const UserState &userState)
{
    static const QMap<UserState, QString> stateMap = {{UserState::Offline, "offline"},
                                                      {UserState::Lingering, "lingering"},
                                                      {UserState::Online, "online"},
                                                      {UserState::Active, "active"},
                                                      {UserState::Closing, "closing"},
                                                      {UserState::Unknown, ""}};
    return stateMap[userState];
}
UserState stringToUserState(const QString &strState)
{
    static const QMap<QString, UserState> stateMap = {{"offline", UserState::Offline},
                                                      {"lingering", UserState::Lingering},
                                                      {"online", UserState::Online},
                                                      {"active", UserState::Active},
                                                      {"closing", UserState::Closing}};
    if (stateMap.contains(strState)) {
        return stateMap[strState];
    } else {
        qWarning() << "Not supported user state.";
        return UserState::Unknown;
    }
}
}  // namespace Utils

DLOGIN_END_NAMESPACE

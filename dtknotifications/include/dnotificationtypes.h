// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <QSharedPointer>
#include <QDebugStateSaver>
#include "dtknotification_global.h"

DNOTIFICATIONS_BEGIN_NAMESPACE
struct DNotificationData
{
    QString appName;
    QString id;
    QString appIcon;
    QString summary;
    QString body;
    QStringList actions;
    QVariantMap hints;
    QString ctime;
    uint replacesId;
    QString timeout;
};
typedef QSharedPointer<DNotificationData> DNotificationDataPtr;

enum class ClosedReason {
    Expired = 1,
    Dismissed,
    Closed,
    Unknown
};

enum AppNotificationConfigItem {
    AppName,
    AppIcon,
    EnableNotification,
    EnablePreview,
    EnableSound,
    ShowInNotificationCenter,
    LockScreenShowNofitication
};

enum DNDModeNotificaitonConfigItem {
    DNDMode,
    LockScreenOpenDNDMode,
    OpenByTimeInterval,
    StartTime,
    EndTime,
    ShowIcon
};

struct ServerInformation {
    QString name;
    QString vendor;
    QString version;
    QString spec_version;
};

QDebug operator<<(QDebug debug, const DNotificationData &nofitication);
QDebug operator<<(QDebug debug, const ServerInformation &serverInformation);

DNOTIFICATIONS_END_NAMESPACE

Q_DECLARE_METATYPE(DNOTIFICATIONS_NAMESPACE::ClosedReason)
Q_DECLARE_METATYPE(DNOTIFICATIONS_NAMESPACE::ServerInformation)
Q_DECLARE_METATYPE(DNOTIFICATIONS_NAMESPACE::AppNotificationConfigItem)
Q_DECLARE_METATYPE(DNOTIFICATIONS_NAMESPACE::DNDModeNotificaitonConfigItem)

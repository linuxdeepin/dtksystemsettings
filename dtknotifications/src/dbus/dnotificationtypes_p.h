// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <qdbusmetatype.h>
#include "dtknotification_global.h"

DNOTIFICATION_BEGIN_NAMESPACE

struct DBusServerInformation {
    QString name;
    QString vendor;
    QString version;
    QString spec_version;
};
QDBusArgument &operator<<(QDBusArgument &arg, const DBusServerInformation &serverInformation);
const QDBusArgument &operator>>(const QDBusArgument &arg, DBusServerInformation &serverInformation);

DNOTIFICATION_END_NAMESPACE

Q_DECLARE_METATYPE(DNOTIFICATION_NAMESPACE::DBusServerInformation)


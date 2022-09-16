// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "daccountstypes.h"
#include "namespace.h"
#include <qdbusargument.h>
#include <qglobal.h>
#include <qmap.h>
#include <qvariant.h>

DACCOUNTS_BEGIN_NAMESPACE

struct LoginHistory_p
{
    qint64 login_time;
    qint64 logout_time;
    QMap<QString, QVariant> session_info;
    static void registerMetaType();
};

const QDBusArgument &operator>>(const QDBusArgument &arg, LoginHistory_p &history);
QDBusArgument &operator<<(QDBusArgument &arg, const LoginHistory_p &history);
DACCOUNTS_END_NAMESPACE

Q_DECLARE_METATYPE(DACCOUNTS_NAMESPACE::LoginHistory_p)

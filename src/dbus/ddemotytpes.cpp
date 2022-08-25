// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "ddemotypes.h"
#include <QDBusMetaType>

QDBusArgument &operator<< (QDBusArgument &arg, const UserPath &path)
{
    arg.beginStructure();
    arg << path.user_id;
    arg << path.path;
    arg.endStructure();
    return arg;
}

const QDBusArgument &operator>> (const QDBusArgument &arg, UserPath &path)
{
    arg.beginStructure();
    arg >> path.user_id;
    arg >> path.path;
    arg.endStructure();
    return arg;
}

void UserPath::registerMetaType()
{
    qRegisterMetaType<UserPath>("UserPath");
    qRegisterMetaType<UserPathList>("UserPathList");
    qDBusRegisterMetaType<UserPath>();
    qDBusRegisterMetaType<UserPathList>();
}


// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <QDBusArgument>

struct UserPath
{
    uint user_id;
    QDBusObjectPath path;
    static void registerMetaType();
    bool operator ==(const UserPath &up) const {
        return up.user_id == user_id && up.path == path;
    }
};

typedef QList<UserPath> UserPathList;

QDBusArgument &operator<<(QDBusArgument &arg, const UserPath &path);
const QDBusArgument &operator>>(const QDBusArgument &arg, UserPath &path);

Q_DECLARE_METATYPE(UserPath)

/*
struct UserPath
{
    uint user_id;
    QDBusObjectPath path;
};

typedef QList<UserPath> UserPathList;

UserPath ==> (uo) ==> struct of { uint, QDBusObjectPath}
UserPathList ==> a(uo) ==> Array of [struct of { uint, QDBusObjectPath}]

+---------------------------------------------------------------------+
|   xml    |      D-Bus Type                   | Qt DBUS Type         |
+---------------------------------------------------------------------+
|   y      |        BYTE                       |  uchar               |
+---------------------------------------------------------------------+
|   b      |        BOOLEAN                    |  bool                |
+---------------------------------------------------------------------+
|   n      |        INT16                      |  short               |
+---------------------------------------------------------------------+
|   q      |        UINT16                     |  ushort              |
+---------------------------------------------------------------------+
|   i      |        INT32                      |  int                 |
+---------------------------------------------------------------------+
|   u      |        UINT32                     |  uint                |
+---------------------------------------------------------------------+
|   x      |        INT64                      |  qlonglong           |
+---------------------------------------------------------------------+
|   t      |        UINT64                     |  qulonglong          |
+---------------------------------------------------------------------+
|   d      |        DOUBLE                     |  double              |
+---------------------------------------------------------------------+
|   s      |        STRING                     |  QString             |
+---------------------------------------------------------------------+
|   v      |        VARIANT                    |  QDBusVariant        |
+---------------------------------------------------------------------+
|   o      |        OBJECT_PATH                |  QDBusObjectPath     |
+---------------------------------------------------------------------+
|   g      |        SIGNATURE                  |  QDBusSignature      |
+---------------------------------------------------------------------+
|   as     |        Array of [string]          |  QStringList         |
+---------------------------------------------------------------------+
|   ai     |        Array of [int32]           |  QList<int>          |
+---------------------------------------------------------------------+
|   ay     |        Array of [BYTE]            |  QByteArray          |
+---------------------------------------------------------------------+
|   {sv}   |        Dict of {String,Variant}   |  QMap<string,Variant>|
+---------------------------------------------------------------------+
|   a      |        Array                      |  QList               |
+---------------------------------------------------------------------+
|   ()     |        struct of { }              |  QVariant            |
+---------------------------------------------------------------------+
|   {}     |        Dict                       |  QMap                |
+---------------------------------------------------------------------+

refs: https://blog.csdn.net/arv002/article/details/119784854
*/

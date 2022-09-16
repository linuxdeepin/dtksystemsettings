// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "passwd.h"
#include "namespace.h"
#include "daccountstypes.h"
#include <QString>
#include <QDir>
#include <QMimeDatabase>
#include <QList>
#include <QTextStream>
#include <QRegularExpression>

DACCOUNTS_BEGIN_NAMESPACE

struct Dutils{
    static QString encryptPassword(const QString& password);
    static QList<QByteArray> getImageFromDir(const QDir& dir);
    static QString getUserConfigValue(const QByteArray& username, keyType key);
    static QString getUserConfigKey(keyType type);
    static int64_t setUserConfigValue(const QByteArray& username, keyType key, const QByteArray& value);
};

DACCOUNTS_END_NAMESPACE

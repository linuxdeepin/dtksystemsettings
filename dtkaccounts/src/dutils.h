// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "namespace.h"
#include "daccountstypes.h"

DACCOUNTS_BEGIN_NAMESPACE

struct Dutils
{
    static QString encryptPassword(const QString &password);
    static QString getUserConfigValue(const QByteArray &username, keyType key);
    static QString getUserConfigKey(keyType type);
    static qint64 setUserConfigValue(const QByteArray &username, keyType key, const QByteArray &value);
};

DACCOUNTS_END_NAMESPACE

// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "userddeinterface.h"

DACCOUNTS_BEGIN_NAMESPACE

DUserDDEInterface::DUserDDEInterface(const QString &path, QObject *parent)
    : QObject(parent)
{
    const QString &Service = QStringLiteral("com.deepin.daemon.Accounts");
    const QString &Interface = QStringLiteral("com.deepin.daemon.Accounts.User");
    m_inter.reset(new DDBusInterface(Service, path, Interface, QDBusConnection::systemBus(), this));
};

DACCOUNTS_END_NAMESPACE

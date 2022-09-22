// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "accountsddeinterface.h"

DACCOUNTS_BEGIN_NAMESPACE

DAccountsDDEInterface::DAccountsDDEInterface(QObject *parent)
    : QObject(parent)
{
    const QString &Service = QStringLiteral("com.deepin.daemon.Accounts");
    const QString &Path = QStringLiteral("/com/deepin/daemon/Accounts");
    const QString &Interface = QStringLiteral("com.deepin.daemon.Accounts");
    m_inter.reset(new DDBusInterface(Service, Path, Interface, QDBusConnection::systemBus(), this));
};

DACCOUNTS_END_NAMESPACE

// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "dbus/userinterface.h"
#include "dbus/userddeinterface.h"

DACCOUNTS_BEGIN_NAMESPACE

class DAccountsUser;

class DAccountsUserPrivate : public QObject
{
    Q_OBJECT
public:
    explicit DAccountsUserPrivate(const QString &path, DAccountsUser *parent = nullptr);
    virtual ~DAccountsUserPrivate();

    DAccountsUser *q_ptr;
    DUserInterface *m_dUserInter;
    Q_DECLARE_PUBLIC(DAccountsUser)
};

DACCOUNTS_END_NAMESPACE

// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "daccountsuser_p.h"

DACCOUNTS_BEGIN_NAMESPACE

DAccountsUserPrivate::DAccountsUserPrivate(const QString& path, DAccountsUser *parent): 
    q_ptr(parent),u(new DUser(path,this))
{

}

DAccountsUserPrivate::~DAccountsUserPrivate()
{
    delete u;
}

DACCOUNTS_END_NAMESPACE

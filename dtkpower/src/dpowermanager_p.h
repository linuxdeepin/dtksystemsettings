// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "dbus/dpowermanager_interface.h"
#include "dpowermanager.h"

DPOWER_BEGIN_NAMESPACE

class DPowerManager;
class DPowerManagerPrivate : public QObject
{
    Q_OBJECT
public:
    DPowerManagerPrivate(DPowerManager *parent = nullptr)
        : q_ptr(parent)
        , m_manager_inter(new DPowerManager_interface(this)){};
    virtual ~DPowerManagerPrivate();

public:
    DPowerManager *q_ptr;
    QString m_errorMessage;
    DPowerManager_interface *m_manager_inter;
    Q_DECLARE_PUBLIC(DPowerManager)
};

DPOWER_END_NAMESPACE
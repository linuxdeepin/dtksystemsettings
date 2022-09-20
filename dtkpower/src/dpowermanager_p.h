// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "dpowermanager.h"

DPOWER_BEGIN_NAMESPACE

class DPowerManager_interface;

class DPowerManagerPrivate : public QObject
{
    Q_OBJECT
public:
    DPowerManagerPrivate(DPowerManager *parent = nullptr)
        : q_ptr(parent){};
    virtual ~DPowerManagerPrivate() {}
    void connectDBusSignal();

public:
    DPowerManager_interface *m_manager_inter;
    DPowerManager           *q_ptr;
    Q_DECLARE_PUBLIC(DPowerManager)
};

DPOWER_END_NAMESPACE

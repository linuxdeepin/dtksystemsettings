// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "namespace.h"
#include "dpowerdevice.h"
#include <qobject.h>

class DDBusInterface;
DPOWER_BEGIN_NAMESPACE

class DPowerDevicePrivate : public QObject
{
    Q_OBJECT
public:
    explicit DPowerDevicePrivate(DPowerDevice *parent = nullptr) : QObject(parent),q_ptr(parent){}

public:
    QString m_errorMessage;
    DDBusInterface *m_inter;
    DPowerDevice *q_ptr;
    Q_DECLARE_PUBLIC(DPowerDevice)

};

DPOWER_END_NAMESPACE
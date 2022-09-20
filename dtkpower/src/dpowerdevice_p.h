// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "dbus/dpowerdevice_interface.h"
#include "dpowerdevice.h"
#include "namespace.h"
#include <QString>
#include <qobject.h>

class DDBusInterface;
DPOWER_BEGIN_NAMESPACE

class DPowerDevice_interface;

class DPowerDevicePrivate : public QObject
{
    Q_OBJECT
public:
    explicit DPowerDevicePrivate(const QString &name, DPowerDevice *parent)
        : q_ptr(parent)
        , m_device_inter(new DPowerDevice_interface(name, this))
    {
    }
    virtual ~DPowerDevicePrivate();

public:
    DPowerDevice *q_ptr;
    DPowerDevice_interface *m_device_inter;
    QString m_errorMessage;
    QString devicename;
    Q_DECLARE_PUBLIC(DPowerDevice)
};

DPOWER_END_NAMESPACE
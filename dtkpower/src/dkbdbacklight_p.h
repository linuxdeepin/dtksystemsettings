// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "dbus/dkbdbacklight_interface.h"
#include "dkbdbacklight.h"
#include "namespace.h"
#include <qobject.h>

class DDBusInterface;
DPOWER_BEGIN_NAMESPACE

class DKbdBacklightPrivate : public QObject
{
    Q_OBJECT
public:
    explicit DKbdBacklightPrivate(DKbdBacklight *parent = nullptr)
        : QObject(parent)
        , q_ptr(parent)
    {
    }

public:
    QString m_errorMessage;
    DKbdBacklight_interface m_kb_inter;
    DKbdBacklight *q_ptr;
    Q_DECLARE_PUBLIC(DKbdBacklight)
};

DPOWER_END_NAMESPACE
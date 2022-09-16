// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "namespace.h"
#include "dkbdbacklight.h"
#include <qobject.h>

class DDBusInterface;
DPOWER_BEGIN_NAMESPACE

class DKbdBacklightPrivate : public QObject
{
    Q_OBJECT
public:
    explicit DKbdBacklightPrivate(DKbdBacklight *parent = nullptr) : QObject(parent),q_ptr(parent){}

public:
    QString m_errorMessage;
    DDBusInterface *m_inter;
    DKbdBacklight *q_ptr;
    Q_DECLARE_PUBLIC(DKbdBacklight)

};

DPOWER_END_NAMESPACE
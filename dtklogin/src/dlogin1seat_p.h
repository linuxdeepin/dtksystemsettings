// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "namespace.h"
#include <qobject.h>

class DDBusInterface;
DLOGIN1_BEGIN_NAMESPACE
class DLogin1Seat;

class DLogin1SeatPrivate : public QObject
{
    Q_OBJECT
public:
    explicit DLogin1SeatPrivate(DLogin1Seat *parent = nullptr) : q_ptr(parent) {}

    QString m_errorMessage;
    DDBusInterface *m_inter;
    DLogin1Seat *q_ptr;
    Q_DECLARE_PUBLIC(DLogin1Seat)
};

DLOGIN1_END_NAMESPACE

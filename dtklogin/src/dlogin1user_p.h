// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "namespace.h"
#include <qobject.h>

class DDBusInterface;
DLOGIN1_BEGIN_NAMESPACE
class DLogin1User;

class DLogin1UserPrivate : public QObject
{
    Q_OBJECT
public:
    explicit DLogin1UserPrivate(DLogin1User *parent = nullptr) : q_ptr(parent) {}

    QString m_errorMessage;
    DDBusInterface *m_inter;
    DLogin1User *q_ptr;
    Q_DECLARE_PUBLIC(DLogin1User)
};

DLOGIN1_END_NAMESPACE

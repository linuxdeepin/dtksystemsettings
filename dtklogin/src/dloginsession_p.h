// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "namespace.h"
#include <qobject.h>


class DDBusInterface;
DLOGIN_BEGIN_NAMESPACE
class DLoginSession;

class DLoginSessionPrivate : public QObject
{
    Q_OBJECT
public:
    explicit DLoginSessionPrivate(DLoginSession *parent = nullptr)
        : q_ptr(parent)
    {
    }

    QString m_errorMessage;
    DDBusInterface *m_inter;
    DLoginSession *q_ptr;
    Q_DECLARE_PUBLIC(DLoginSession)
};

DLOGIN_END_NAMESPACE

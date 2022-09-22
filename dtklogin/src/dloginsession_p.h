// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "namespace.h"
#include <qobject.h>

#define MAIN_SECTION        "Desktop Entry"
#define KEY_HIDDEN          "Hidden"
#define KEY_ONLY_SHOW_IN    "OnlyShowIn"
#define KEY_NOT_SHOW_IN     "NotShowIn"

class DDBusInterface;
DLOGIN_BEGIN_NAMESPACE
class DLoginSession;
class Login1SessionInterface;

class DLoginSessionPrivate : public QObject
{
    Q_OBJECT
public:
    explicit DLoginSessionPrivate(DLoginSession *parent = nullptr)
        : q_ptr(parent)
    {
    }

    Login1SessionInterface *m_inter;
    DLoginSession *q_ptr;
    Q_DECLARE_PUBLIC(DLoginSession)
};

DLOGIN_END_NAMESPACE

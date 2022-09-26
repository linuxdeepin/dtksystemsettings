// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "namespace.h"
#include <qobject.h>

class DDBusInterface;
class QFileSystemWatcher;
DLOGIN_BEGIN_NAMESPACE
class DLoginSession;
class Login1SessionInterface;
class StartManagerInterface;
class SessionManagerInterface;

class DLoginSessionPrivate : public QObject
{
    Q_OBJECT
public:
    explicit DLoginSessionPrivate(DLoginSession *parent = nullptr)
        : q_ptr(parent)
    {
    }

    bool enableAutostartWatch();

private:
    Login1SessionInterface *m_inter;
    StartManagerInterface *m_startManagerInter;
    SessionManagerInterface *m_sessionManagerInter;
    DLoginSession *q_ptr;
    QFileSystemWatcher *m_fileWatcher;
    Q_DECLARE_PUBLIC(DLoginSession)
};

DLOGIN_END_NAMESPACE

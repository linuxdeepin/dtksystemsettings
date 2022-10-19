// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "drfmanager.h"
#include <QObject>

DRFMGR_USE_NAMESPACE

class Demo : public QObject
{
    Q_OBJECT
public:
    Demo();
    void run();

private:
    DRfmanager *m_rfMgr = nullptr;
};

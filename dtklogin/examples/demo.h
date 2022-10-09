// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once
#include <qobject.h>

class Demo : public QObject
{
public:
    Demo(QObject *parent = nullptr);
    virtual int run() = 0;
};
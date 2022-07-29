// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-only

#pragma once

#include "namespace.h"
#include <qobject.h>

DEMO_BEGIN_NAMESPACE
class Demo : public QObject {
    Q_OBJECT
  public:
    Demo(QObject *parent = nullptr);
    ~Demo();
    int add(const int a, const int b);
};
DEMO_END_NAMESPACE

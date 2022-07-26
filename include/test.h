// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-only

#pragma once

#include <qobject.h>

namespace Test {
class Test : public QObject {
    Q_OBJECT
  public:
    Test(QObject *parent = nullptr);
    ~Test();
    int add(const int a, const int b);
};
} // namespace Test

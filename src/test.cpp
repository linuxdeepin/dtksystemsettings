// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-only

#include "include/test.h"

namespace Test {
Test::Test(QObject *parent) : QObject(parent) {}

Test::~Test() {}

int Test::add(const int a, const int b) { return a + b; }
} // namespace Test

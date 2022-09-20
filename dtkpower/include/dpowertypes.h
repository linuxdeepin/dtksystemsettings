// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "namespace.h"
#include <qobject.h>

DPOWER_BEGIN_NAMESPACE
struct History
{
    uint time;
    double value;
    uint state;
};

struct Statistic
{
    double value;
    double accuracy;
};

DPOWER_END_NAMESPACE

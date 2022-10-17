// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "dtkpower_global.h"
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

enum class KbdSource { Internal, External, Unknown };

enum class PowerMode { Performance, Balance, PowerSave, Unknown };

enum class LidClosedAction : qint32 { Suspend = 1, Hibernate, TurnoffScreen, DoNothing, Unknown };

enum class PowerBtnAction : qint32 { Shutdown = 0, Suspend, Hibernate, TurnoffScreen, DoNothing, Unknown };

DPOWER_END_NAMESPACE

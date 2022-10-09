// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
#include "dpowermanager.h"
#include "dkbdbacklight.h"
#include <QCoreApplication>
#include <iostream>
#include <qdebug.h>

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    Dtk::Power::DPowerManager manager;
    auto kb = manager.kbdBacklight();
    qDebug() << kb->brightness();
    qDebug() << "*************************************************";
    kb->setBrightness(1);
    return 0;
}
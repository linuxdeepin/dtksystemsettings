// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
#include "dpowersettings.h"
#include <QCoreApplication>
#include <qdebug.h>

int main(int argc, char **argv)
{
    QCoreApplication a(argc, argv);
    Dtk::Power::DPowerSettings settings;
    qDebug() << settings.cpuGovernor();
    return 0;
}
// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
#include "dpowermanager.h"
#include "dpowerdevice.h"
#include <QCoreApplication>
#include <qdebug.h>

int main(int argc, char **argv)
{
    QCoreApplication a(argc, argv);
    Dtk::Power::DPowerManager manager;
    auto device = manager.displayDevice();
    qDebug() << device->energyFullDesign();
    return 0;
}
// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
#include "dsystemtime.h"
#include <QCoreApplication>
#include <iostream>
#include <qdebug.h>
#include <qobject.h>
#include <qeventloop.h>
DSYSTEMTIME_USE_NAMESPACE
int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    Dtk::SystemTime::DSystemTime systemTime;
    qDebug() << systemTime.serverName();
    qDebug() << systemTime.fallbackNTPServers()[1];
    qDebug() << systemTime.systemNTPServers().isEmpty();
    qDebug() << systemTime.canNTP();
    qDebug() << systemTime.timeDate();
}
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <qcoreapplication.h>
#include <qdebug.h>
#include <qglobal.h>

#include "dloginmanager.h"

int main (int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    Dtk::Login::DLoginManager manager;
    auto seats = manager.listSeats();
    if (!seats.isEmpty()) {
        qDebug() << "seat0's path:" << seats[0];
        return -1;
    }
    return app.exec();
}

// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <QCoreApplication>
#include "demo.h"
#include "signaldemo.h"
#include "propertydemo.h"

DLOGIN_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QList<Demo *> demos = {new SignalDemo(&app), new PropertyDemo(&app)};
    foreach (const auto demo, demos) {
        demo->run();
    }
    return app.exec();
}
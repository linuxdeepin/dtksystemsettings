// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
#include "dpowermanager.h"
#include "dkbdbacklight.h"
#include <QCoreApplication>
#include <iostream>
#include <qdebug.h>
#include <qobject.h>
#include <qeventloop.h>
DPOWER_USE_NAMESPACE
int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    Dtk::Power::DPowerManager manager;
    auto kb = manager.kbdBacklight();
    qDebug() << kb->brightness();
    qDebug() << "*************************************************";
    kb->setBrightness(1);
    QObject::connect(kb.data(), &Dtk::Power::DKbdBacklight::brightnessChanged, &app, [=](const qint32 value) {
        qDebug() << "brightness:" << value;
    });
    QObject::connect(
        kb.data(),
        &Dtk::Power::DKbdBacklight::brightnessChangedWithSource,
        &app,
        [=](const qint32 value, const KbdSource &source) { qDebug() << "brightness:" << value << static_cast<int>(source); });
    return app.exec();
}
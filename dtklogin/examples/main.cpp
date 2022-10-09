// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <QCoreApplication>
#include "demo.h"
#include "signaldemo.h"

DLOGIN_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QList<Demo *> demos = {new SignalDemo(&app)};
    foreach (const auto demo, demos) {
        demo->run();
    }
    // const QMetaObject *mo = manager.metaObject();
    // for (int i = 0; i < mo->propertyCount(); i++) {
    //     QMetaProperty mp = mo->property(i);
    //     qDebug() << "Property:" << mp.name() << ", type:" << mp.typeName() << ", readable:" << mp.isReadable()
    //              << ", writable:" << mp.isWritable() << ", value:" << mp.read(&manager);
    // }
    // qDebug() << manager.listUsers();
    // qDebug() << manager.listInhibitors();
    // qDebug() << manager.listSessions();
    // qDebug() << manager.listSeats();
    // auto session = manager.currentSession();

    // session->lock();
    // session->activate();
    // session->setLocked(true);
    // session->terminate();
    // manager.logout();
    return app.exec();
}
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "propertydemo.h"
#include <qdebug.h>
#include <QMetaObject>
#include <QMetaProperty>
#include "dloginuser.h"
#include "dloginseat.h"

PropertyDemo::PropertyDemo(QObject *parent)
    : Demo(parent)
    , m_manager(new DLoginManager)
    , m_currentSession(m_manager->currentSession())
{
}

int PropertyDemo::run()
{
    const QMetaObject *mo = m_manager->metaObject();
    for (int i = 0; i < mo->propertyCount(); i++) {
        QMetaProperty mp = mo->property(i);
        qDebug() << "Property:" << mp.name() << ", type:" << mp.typeName() << ", readable:" << mp.isReadable()
                 << ", writable:" << mp.isWritable() << ", value:" << mp.read(m_manager);
    }
    qDebug() << m_manager->scheduledShutdown();
    auto user = m_manager->findUserById(1000);
    mo = user->metaObject();
    for (int i = 0; i < mo->propertyCount(); i++) {
        QMetaProperty mp = mo->property(i);
        qDebug() << "Property:" << mp.name() << ", type:" << mp.typeName() << ", readable:" << mp.isReadable()
                 << ", writable:" << mp.isWritable() << ", value:" << mp.read(user.data());
    }
    qDebug() << user->UID();
    auto session = m_manager->findSessionById(m_currentSession->id());
    mo = session->metaObject();
    for (int i = 0; i < mo->propertyCount(); i++) {
        QMetaProperty mp = mo->property(i);
        qDebug() << "Property:" << mp.name() << ", type:" << mp.typeName() << ", readable:" << mp.isReadable()
                 << ", writable:" << mp.isWritable() << ", value:" << mp.read(session.data());
    }
    qDebug() << session->id();
    auto seat = m_manager->currentSeat();
    mo = seat->metaObject();
    for (int i = 0; i < mo->propertyCount(); i++) {
        QMetaProperty mp = mo->property(i);
        qDebug() << "Property:" << mp.name() << ", type:" << mp.typeName() << ", readable:" << mp.isReadable()
                 << ", writable:" << mp.isWritable() << ", value:" << mp.read(seat.data());
    }
    qDebug() << seat->id();
    return 0;
}
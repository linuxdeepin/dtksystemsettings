// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "propertydemo.h"
#include <qdebug.h>
#include <QMetaObject>
#include <QMetaProperty>

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
    qDebug() << m_manager->listUsers();
    qDebug() << m_manager->listInhibitors();
    qDebug() << m_manager->listSessions();
    qDebug() << m_manager->listSeats();
    return 0;
}
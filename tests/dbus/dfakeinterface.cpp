// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dfakeinterface.h"
#include "dfakeinterface_adaptor.h"

#include <QDBusMessage>
#include <QDBusConnection>
#include <QDBusConnectionInterface>
#include <QDebug>

DFakeInterface::DFakeInterface(QObject *parent) : QObject(parent)
{
    registerService();
}

DFakeInterface::~DFakeInterface()
{

}

bool DFakeInterface::registerService()
{
    // 编写 DFakeInterface 头文件，qdbuscpp2xml -A dfakeinterface.h -o xxx.xml
    // 添加自定义类型的函数，ListUsers / setListUsers
    // DFakeInterfaceAdaptor 由 qt5_add_dbus_adaptor 中调用 qdbusxml2cpp 自动生成
    Q_UNUSED(new DFakeInterfaceAdaptor(this));

    QDBusConnection bus = QDBusConnection::sessionBus();
    if (!bus.registerService(FAKE_SERVICE)) {
        QString errorMsg = bus.lastError().message();
        if (errorMsg.isEmpty())
            errorMsg = "maybe it's running";

        qWarning() << QString("Can't register the %1 service, %2.").arg(FAKE_SERVICE).arg(errorMsg);
        return false;
    }
    if (!bus.registerObject(FAKE_PATH, this)) {
        qWarning() << QString("Can't register %1 the D-Bus object.").arg(FAKE_PATH);
        return false;
    }

    return true;
}

bool DFakeInterface::Docked() const
{
    return m_docked;
}

void DFakeInterface::setDocked(bool docked)
{
    if (docked == m_docked)
        return;

    m_docked = docked;
    Q_EMIT DockedChanged(docked);
}

UserPathList DFakeInterface::ListUsers()
{
    return m_users;
}

void DFakeInterface::setListUsers(const UserPathList &list)
{
    if (list == m_users)
        return;

    for (auto user : list) {
        if (m_users.indexOf(user) < 0)
            Q_EMIT UserNew(user.user_id, user.path);
    }

    m_users = list;
}


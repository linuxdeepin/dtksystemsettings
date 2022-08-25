// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "ddemointerface.h"
#include "ddbusinterface.h"
#include "ddemotypes.h"

#include <QDBusPendingReply>
#include <qobjectdefs.h>

#ifdef USE_FAKE_INTERFACE
static const QString &Service = QStringLiteral(FAKE_SERVICE);
static const QString &Path = QStringLiteral(FAKE_PATH);
static const QString &Interface = QStringLiteral(FAKE_INTERFACE);
#define DBUS_CON QDBusConnection::sessionBus()
#else
static const QString &Service = QStringLiteral("org.freedesktop.login1");
static const QString &Path = QStringLiteral("/org/freedesktop/login1");
static const QString &Interface = QStringLiteral("org.freedesktop.login1.Manager");
#define DBUS_CON QDBusConnection::systemBus()
#endif

DDemoInterface::DDemoInterface(QObject *parent)
    : QObject(parent)
    , m_interface(new DDBusInterface(Service, Path, Interface, DBUS_CON, this))
{
    // 自定义类型必须进行元对象类型注册才能正常使用。
    UserPath::registerMetaType();

    // 连接DBus 对象已存在的对象。
    DBUS_CON.connect(Service, Path, Interface, "UserNew", this, SLOT(UserNew(const uint, const QDBusObjectPath &)));
}

DDemoInterface::~DDemoInterface() {}

bool DDemoInterface::Docked() const
{
    // 注意这里必须使用qdbus_cast，否则自定义类型无法进行转换。
    return qdbus_cast<bool>(m_interface->property("Docked"));
}

// 此处演示了使用自定义类型的DBus方法，属性也是一样
UserPathList DDemoInterface::ListUsers()
{
    QDBusPendingReply<UserPathList> reply = m_interface->asyncCall(QStringLiteral("ListUsers"));
    reply.waitForFinished();
    if (reply.isValid()) {
        return reply.value();
    } else {
        m_errorMessage = reply.error().message();
        Q_EMIT errorMessageChanged(m_errorMessage);
    }
    return UserPathList();
}

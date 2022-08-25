// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "ddemotypes.h"
#include <qobject.h>

class QDbusObjectPath;
class DDBusInterface;

class DDemoInterface : public QObject
{
    Q_OBJECT
public:
    explicit DDemoInterface(QObject *parent =nullptr);
    ~DDemoInterface();

    // DBus的属性声明应放在这里。
    Q_PROPERTY(bool Docked READ Docked NOTIFY DockedChanged)

    bool Docked() const;

public Q_SLOTS:
    // DBus的方法调用应该放在这里。
    UserPathList ListUsers();

    // 最好有错误信息获取，当dbus调用失败时，保存错误信息。
    inline QString lastError() const { return m_errorMessage; }

Q_SIGNALS:
    // 使用DDBusInterface（m_interface)，并且其父对象指定为this，就可以自动使用属性Changed信号。
    // 需要注意的是，可能存在某些DBus接口属性改变不会发生Changed信号的情况，所以应提前做好测试。
    void DockedChanged(const bool value);

    // 此处是DBus接口声明的信号，在此进行声明，在构造函数进行连接。
    void UserNew(const uint uid, const QDBusObjectPath &path);

    void errorMessageChanged(const QString &message);

private:
    QScopedPointer<DDBusInterface> m_interface;
    QString m_errorMessage;
};

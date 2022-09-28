// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <QDebug>
#include <QList>
#include <QScopedPointer>
#include <QDBusObjectPath>

class FakeAccountsManagerInterface : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("Fake D-Bus Interface", "com.deepin.daemon.FakeAccounts/org.freedesktop.FakeAccounts")

public:
    explicit FakeAccountsManagerInterface(QObject *parent = nullptr);
    virtual ~FakeAccountsManagerInterface();

    bool m_createUserTrigger{false};
    bool m_deleteUserTrigger{false};
    bool m_userListTrigger{false};
    bool m_findUserByIdTrigger{false};
    bool m_findUserByNameTrigger{false};
    bool m_groupsTrigger{false};
    bool m_presetGroupsTrigger{false};
    bool m_isPasswordValidTrigger{false};
    bool m_isUsernameTrigger{false};

signals:
    Q_SCRIPTABLE void UserAdded(QString user);
    Q_SCRIPTABLE void UserDeleted(QString user);

public slots:
    Q_SCRIPTABLE QList<QDBusObjectPath> ListCachedUsers()
    {
        m_userListTrigger = true;
        return {};
    }

    Q_SCRIPTABLE QDBusObjectPath CreateUser(QString name, QString fullName, quint32 type)
    {
        Q_UNUSED(name)
        Q_UNUSED(fullName)
        Q_UNUSED(type)
        m_createUserTrigger = true;
        return QDBusObjectPath{"/com/deepin/daemon/FakeAccounts/User1000"};
    }

    Q_SCRIPTABLE void DeleteUser(QString name, bool rmFiles)
    {
        Q_UNUSED(name)
        Q_UNUSED(rmFiles)
        m_deleteUserTrigger = false;
    }

    Q_SCRIPTABLE QString FindUserById(QString uid)
    {
        Q_UNUSED(uid)
        m_findUserByIdTrigger = true;
        return QString{"/com/deepin/daemon/FakeAccounts/User1000"};
    }

    Q_SCRIPTABLE QString FindUserByName(QString name)
    {
        Q_UNUSED(name)
        m_findUserByNameTrigger = true;
        return QString{"/com/deepin/daemon/FakeAccounts/User1000"};
    }

    Q_SCRIPTABLE QStringList Groups() { return {"sudo", "root", "test"}; }
    Q_SCRIPTABLE QStringList PresetGroups() { return {"preset", "printer"}; }
    Q_SCRIPTABLE bool IsPasswordValid(const QString &password, QString &msg, int &code)
    {
        Q_UNUSED(password)
        Q_UNUSED(msg)
        Q_UNUSED(code)
        return true;
    }
    Q_SCRIPTABLE bool IsUsernameValid(const QString &username, QString &msg, int &code)
    {
        Q_UNUSED(username)
        Q_UNUSED(msg)
        Q_UNUSED(code)
        return true;
    }

private:
    void registerService();
    void unregisterService();
};

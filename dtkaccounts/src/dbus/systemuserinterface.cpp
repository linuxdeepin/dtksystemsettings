// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "systemuserinterface.h"

DACCOUNTS_BEGIN_NAMESPACE

DUserSystemInterface::DUserSystemInterface(const QString &path, QObject *parent)
    : QObject(parent)
{
    const QString &Service = QStringLiteral("com.deepin.daemon.Accounts");
    const QString &Interface = QStringLiteral("com.deepin.daemon.Accounts.User");
    m_inter.reset(new DDBusInterface(Service, path, Interface, QDBusConnection::systemBus(), this));
};

bool DUserSystemInterface::automaticLogin() const
{
    return qdbus_cast<bool>(m_inter->property("AutomaticLogin"));
}

bool DUserSystemInterface::noPasswdLogin() const
{
    return qdbus_cast<bool>(m_inter->property("NoPasswdLogin"));
}

qint32 DUserSystemInterface::accountType() const
{
    return qdbus_cast<qint32>(m_inter->property("AccountType"));
}

qint32 DUserSystemInterface::maxPasswordAge() const
{
    return qdbus_cast<qint32>(m_inter->property("MaxPasswordAge"));
}

QStringList DUserSystemInterface::iconList() const
{
    return qdbus_cast<QStringList>(m_inter->property("IconList"));
}

QStringList DUserSystemInterface::historyLayout() const
{
    return qdbus_cast<QStringList>(m_inter->property("HistoryLayout"));
}

QStringList DUserSystemInterface::groups() const
{
    return qdbus_cast<QStringList>(m_inter->property("Groups"));
}

QString DUserSystemInterface::iconFile() const
{
    return qdbus_cast<QString>(m_inter->property("IconFile"));
}

QString DUserSystemInterface::layout() const
{
    return qdbus_cast<QString>(m_inter->property("Layout"));
}

QString DUserSystemInterface::locale() const
{
    return qdbus_cast<QString>(m_inter->property("Locale"));
}

QString DUserSystemInterface::passwordHint() const
{
    return qdbus_cast<QString>(m_inter->property("PasswordHint"));
}

QDBusPendingReply<ReminderInfo_p> DUserSystemInterface::getReminderInfo() const
{
    return m_inter->asyncCall("GetReminderinfo");
}

QDBusPendingReply<QList<qint32>> DUserSystemInterface::getSecretQuestions() const
{
    return m_inter->asyncCall("GetSecretQuestions");
}

QDBusPendingReply<void> DUserSystemInterface::addGroup(const QString &group)
{
    return m_inter->asyncCallWithArgumentList("AddGroup", {QVariant::fromValue(group)});
}

QDBusPendingReply<void> DUserSystemInterface::deleteGroup(const QString &group)
{
    return m_inter->asyncCallWithArgumentList("DeleteGroup", {QVariant::fromValue(group)});
}

QDBusPendingReply<void> DUserSystemInterface::deleteIconFile(const QString &icon)
{
    return m_inter->asyncCallWithArgumentList("DeleteIconFile", {QVariant::fromValue(icon)});
}

QDBusPendingReply<void> DUserSystemInterface::enableNoPasswdLogin(const bool enabled)
{
    return m_inter->asyncCallWithArgumentList("EnableNoPasswdLogin", {QVariant::fromValue(enabled)});
}

QDBusPendingReply<void> DUserSystemInterface::setAutomaticLogin(const bool enabled)
{
    return m_inter->asyncCallWithArgumentList("SetAutomaticLogin", {QVariant::fromValue(enabled)});
}

QDBusPendingReply<void> DUserSystemInterface::setHistoryLayout(const QStringList &list)
{
    return m_inter->asyncCallWithArgumentList("SetHistoryLayout", {QVariant::fromValue(list)});
}

QDBusPendingReply<void> DUserSystemInterface::setIconFile(const QString &iconURI)
{
    return m_inter->asyncCallWithArgumentList("SetIconFile", {QVariant::fromValue(iconURI)});
}

QDBusPendingReply<void> DUserSystemInterface::setLayout(const QString &layout)
{
    return m_inter->asyncCallWithArgumentList("SetLayout", {QVariant::fromValue(layout)});
}

QDBusPendingReply<void> DUserSystemInterface::setGroups(const QStringList &groups)
{
    return m_inter->asyncCallWithArgumentList("SetGroups", {QVariant::fromValue(groups)});
}

QDBusPendingReply<void> DUserSystemInterface::setLocale(const QString &locale)
{
    return m_inter->asyncCallWithArgumentList("SetLocale", {QVariant::fromValue(locale)});
}

QDBusPendingReply<void> DUserSystemInterface::setMaxPasswordAge(qint32 nDays)
{
    return m_inter->asyncCallWithArgumentList("SetPasswordAge", {QVariant::fromValue(nDays)});
}

QDBusPendingReply<void> DUserSystemInterface::setPassword(const QString &password)
{
    return m_inter->asyncCallWithArgumentList("SetPassword", {QVariant::fromValue(password)});
}

QDBusPendingReply<void> DUserSystemInterface::setPasswordHint(const QString &hint)
{
    return m_inter->asyncCallWithArgumentList("SetPasswordHint", {QVariant::fromValue(hint)});
}

QDBusPendingReply<void> DUserSystemInterface::setSecretQuestions(const QMap<qint32, QByteArray> &list)
{
    return m_inter->asyncCallWithArgumentList("SetSecretQuestions", {QVariant::fromValue(list)});
}

QDBusPendingReply<QList<qint32>> DUserSystemInterface::verifySecretQuestions(const QMap<qint32, QString> &anwsers)
{
    return m_inter->asyncCallWithArgumentList("VerifySecretQuestions", {QVariant::fromValue(anwsers)});
}
DACCOUNTS_END_NAMESPACE

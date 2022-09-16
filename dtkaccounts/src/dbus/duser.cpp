// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "daccountstypes_p.h"
#include "ddbusinterface.h"
#include "duser.h"
#include "dutils.h"
#include <qdbusconnection.h>
#include <qdbusinterface.h>
#include <qdbuspendingreply.h>
#include <qstringliteral.h>
#include <qvariant.h>

DACCOUNTS_BEGIN_NAMESPACE

DUser::DUser(const QString &path, QObject *parent): QObject(parent)
{
    const QString &Service = QStringLiteral("org.freedesktop.Accounts");
    const QString &Interface = QStringLiteral("org.freedesktop.Accounts.User");

    LoginHistory_p::registerMetaType();

    m_inter.reset(new DDBusInterface(Service, path, Interface, QDBusConnection::systemBus(), this));
    QDBusConnection::systemBus().connect(Service, path, Interface, "Changed", this, "receiveChanged");
};

QList<LoginHistory> DUser::loginHistorys() const
{
    const auto &result = qdbus_cast<QList<LoginHistory_p>>(m_inter->property("LoginHistory"));
    QList<LoginHistory> loginHistory;
    for (auto &&history_p : result) {
        LoginHistory history;
        history.login_time = history_p.login_time;
        history.logout_time = history_p.logout_time;
        history.session_info = std::move(history_p.session_info);
        loginHistory.push_back(std::move(history));
    }
    return loginHistory;
}

bool DUser::automaticLogin() const
{
    return qdbus_cast<bool>(m_inter->property("AutomaticLogin"));
}

bool DUser::localAccount() const
{
    return qdbus_cast<bool>(m_inter->property("LocalAccount"));
}

bool DUser::locked() const
{
    return qdbus_cast<bool>(m_inter->property("Locked"));
}

bool DUser::systemAccount() const
{
    return qdbus_cast<bool>(m_inter->property("SystemAccount"));
}

qint32 DUser::accountType() const
{
    return qdbus_cast<qint32>(m_inter->property("AccountType"));
}

qint32 DUser::passwordMode() const
{
    return qdbus_cast<qint32>(m_inter->property("PasswordMode"));
}

qint64 DUser::loginTime() const
{
    return qdbus_cast<qint64>(m_inter->property("LoginTime"));
}

QString DUser::email() const
{
    return qdbus_cast<QString>(m_inter->property("Email"));
}

QString DUser::homeDirectory() const
{
    return qdbus_cast<QString>(m_inter->property("HomeDirectory"));
}

QString DUser::iconFile() const
{
    return qdbus_cast<QString>(m_inter->property("IconFile"));
}

QString DUser::language() const
{
    return qdbus_cast<QString>(m_inter->property("Language"));
}

QString DUser::location() const
{
    return qdbus_cast<QString>(m_inter->property("Location"));
}

QString DUser::passwordHint() const
{
    return qdbus_cast<QString>(m_inter->property("PasswordHint"));
}

QString DUser::realName() const
{
    return qdbus_cast<QString>(m_inter->property("RealName"));
}

QString DUser::shell() const
{
    return qdbus_cast<QString>(m_inter->property("Shell"));
}

QString DUser::userName() const
{
    return qdbus_cast<QString>(m_inter->property("UserName"));
}

QString DUser::xSession() const
{
    return qdbus_cast<QString>(m_inter->property("XSession"));
}

quint64 DUser::loginFrequency() const
{
    return qdbus_cast<quint64>(m_inter->property("LoginFrequency"));
}

quint64 DUser::uid() const
{
    return qdbus_cast<quint64>(m_inter->property("Uid"));
}

// public slots
QString DUser::lastError() const
{
    return m_errorMessage;
}

//private slots
void DUser::receiveChanged(){
    emit userChanged();
}

std::tuple<qint64, qint64, qint64, qint64, qint64, qint64> DUser::GetPasswordExpirationPolicy()
{
    QDBusPendingReply<qint64, qint64, qint64, qint64, qint64, qint64> replay =
        m_inter->asyncCall("GetPasswordExpirationPolicy");
    replay.waitForFinished();
    if (!replay.isValid()) 
    {
        return std::tuple<qint64, qint64, qint64, qint64, qint64, qint64>();
    }
    return std::make_tuple<qint64, qint64, qint64, qint64, qint64, qint64>(replay.argumentAt(0).toLongLong(),
                                                                           replay.argumentAt(1).toLongLong(),
                                                                           replay.argumentAt(2).toLongLong(),
                                                                           replay.argumentAt(3).toLongLong(),
                                                                           replay.argumentAt(4).toLongLong(),
                                                                           replay.argumentAt(5).toLongLong());
}

void DUser::SetAccountType(qint32 accountType)
{
    QVariantList args{QVariant::fromValue(accountType)};
    QDBusPendingReply<> replay = m_inter->asyncCallWithArgumentList("SetAccountType", args);
    replay.waitForFinished();
    if (!replay.isValid()) {
        m_errorMessage = replay.error().message();
        emit errorMessageChanged(m_errorMessage);
    }
}

void DUser::SetAutomaticLogin(bool enabled)
{
    QVariantList args{QVariant::fromValue(enabled)};
    QDBusPendingReply<> replay = m_inter->asyncCallWithArgumentList("SetAutomaticLogin", args);
    replay.waitForFinished();
    if (!replay.isValid()) {
        m_errorMessage = replay.error().message();
        emit errorMessageChanged(m_errorMessage);
    }
}

void DUser::SetEmail(const QString &email)
{
    QVariantList args{QVariant::fromValue(email)};
    QDBusPendingReply<> replay = m_inter->asyncCallWithArgumentList("SetEmail", args);
    replay.waitForFinished();
    if (!replay.isValid()) {
        m_errorMessage = replay.error().message();
        emit errorMessageChanged(m_errorMessage);
    }
}

void DUser::SetHomeDirectory(const QString &homedir)
{
    QVariantList args{QVariant::fromValue(homedir)};
    QDBusPendingReply<> replay = m_inter->asyncCallWithArgumentList("SetHomeDirectory", args);
    replay.waitForFinished();
    if (!replay.isValid()) {
        m_errorMessage = replay.error().message();
        emit errorMessageChanged(m_errorMessage);
    }
}

void DUser::SetIconFile(const QString &filename)
{
    QVariantList args{QVariant::fromValue(filename)};
    QDBusPendingReply<> replay = m_inter->asyncCallWithArgumentList("SetIconFile", args);
    replay.waitForFinished();
    if (!replay.isValid()) {
        m_errorMessage = replay.error().message();
        emit errorMessageChanged(m_errorMessage);
    }
}

void DUser::SetLanguage(const QString &language)
{
    QVariantList args{QVariant::fromValue(language)};
    QDBusPendingReply<> replay = m_inter->asyncCallWithArgumentList("SetLanguage", args);
    replay.waitForFinished();
    if (!replay.isValid()) {
        m_errorMessage = replay.error().message();
        emit errorMessageChanged(m_errorMessage);
    }
}

void DUser::SetLocation(const QString &location)
{
    QVariantList args{QVariant::fromValue(location)};
    QDBusPendingReply<> replay = m_inter->asyncCallWithArgumentList("SetLocation", args);
    replay.waitForFinished();
    if (!replay.isValid()) {
        m_errorMessage = replay.error().message();
        emit errorMessageChanged(m_errorMessage);
    }
}

void DUser::SetLocked(bool locked)
{
    QVariantList args{QVariant::fromValue(locked)};
    QDBusPendingReply<> replay = m_inter->asyncCallWithArgumentList("SetLocked", args);
    replay.waitForFinished();
    if (!replay.isValid()) {
        m_errorMessage = replay.error().message();
        emit errorMessageChanged(m_errorMessage);
    }
}

void DUser::SetPassword(const QString &password, const QString &hint)
{
    QVariantList args{QVariant::fromValue(Dutils::encryptPassword(password)), QVariant::fromValue(hint)};
    QDBusPendingReply<> replay = m_inter->asyncCallWithArgumentList("SetPassword", args);
    replay.waitForFinished();
    if (!replay.isValid()) {
        m_errorMessage = replay.error().message();
        emit errorMessageChanged(m_errorMessage);
    }
}

void DUser::SetPasswordHint(const QString &hint)
{
    QVariantList args{QVariant::fromValue(hint)};
    QDBusPendingReply<> replay = m_inter->asyncCallWithArgumentList("SetPasswordHint", args);
    replay.waitForFinished();
    if (!replay.isValid()) {
        m_errorMessage = replay.error().message();
        emit errorMessageChanged(m_errorMessage);
    }
}

void DUser::SetPasswordMode(qint32 mode)
{
    QVariantList args{QVariant::fromValue(mode)};
    QDBusPendingReply<> replay = m_inter->asyncCallWithArgumentList("SetPasswordMode", args);
    replay.waitForFinished();
    if (!replay.isValid()) {
        m_errorMessage = replay.error().message();
        emit errorMessageChanged(m_errorMessage);
    }
}

void DUser::SetRealName(const QString &name)
{
    QVariantList args{QVariant::fromValue(name)};
    QDBusPendingReply<> replay = m_inter->asyncCallWithArgumentList("SetRealName", args);
    replay.waitForFinished();
    if (!replay.isValid()) {
        m_errorMessage = replay.error().message();
        emit errorMessageChanged(m_errorMessage);
    }
}

void DUser::SetShell(const QString &shell)
{
    QVariantList args{QVariant::fromValue(shell)};
    QDBusPendingReply<> replay = m_inter->asyncCallWithArgumentList("SetShell", args);
    replay.waitForFinished();
    if (!replay.isValid()) {
        m_errorMessage = replay.error().message();
        emit errorMessageChanged(m_errorMessage);
    }
}

void DUser::SetUserName(const QString &name)
{
    QVariantList args{QVariant::fromValue(name)};
    QDBusPendingReply<> replay = m_inter->asyncCallWithArgumentList("SetUserName", args);
    replay.waitForFinished();
    if (!replay.isValid()) {
        m_errorMessage = replay.error().message();
        emit errorMessageChanged(m_errorMessage);
    }
}

void DUser::SetXSession(const QString &x_session)
{
    QVariantList args{QVariant::fromValue(x_session)};
    QDBusPendingReply<> replay = m_inter->asyncCallWithArgumentList("SetXSession", args);
    replay.waitForFinished();
    if (!replay.isValid()) {
        m_errorMessage = replay.error().message();
        emit errorMessageChanged(m_errorMessage);
    }
}

DACCOUNTS_END_NAMESPACE

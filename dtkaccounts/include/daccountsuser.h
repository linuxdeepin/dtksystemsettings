// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "daccountstypes.h"
#include "namespace.h"
#include <qobject.h>
#include <qscopedpointer.h>
#include <qurl.h>
#include <qdatetime.h>

DACCOUNTS_BEGIN_NAMESPACE

class DAccountsUserPrivate;

class DAccountsUser : public QObject
{
    Q_OBJECT
    friend class DAccountsManager;
public:
    virtual ~DAccountsUser() = default;

    Q_PROPERTY(AccountTypes accountType READ AccountType WRITE SetAccountType)
    Q_PROPERTY(bool automaticLogin READ AutomaticLogin WRITE SetAutomaticLogin)
    Q_PROPERTY(QString fullName READ FullName WRITE SetFullName)
    Q_PROPERTY(quint64 GID READ Gid)
    Q_PROPERTY(quint64 UID READ Uid)
    Q_PROPERTY(QStringList groups READ Groups WRITE SetGroups)
    Q_PROPERTY(QList<QByteArray> layoutList READ LayoutList WRITE SetLayoutList)
    Q_PROPERTY(QString homeDir READ HomeDir WRITE SetHomeDir)
    Q_PROPERTY(QList<QByteArray> iconFileList READ IconFileList)
    Q_PROPERTY(QUrl iconFile READ IconFile WRITE SetIconFile)
    Q_PROPERTY(QByteArray layout READ Layout WRITE SetLayout)
    Q_PROPERTY(QByteArray locale READ Locale WRITE SetLocale)
    Q_PROPERTY(bool locked READ Locked WRITE SetLocked)
    Q_PROPERTY(qint32 maxPasswordAge READ MaxPasswordAge WRITE SetMaxPasswordAge)
    Q_PROPERTY(QString passwordHint READ PasswordHint WRITE SetPasswordHint)
    Q_PROPERTY(QDateTime passwordLastChange READ PasswordLastChange)
    Q_PROPERTY(PasswdStatus passwordStatus READ PasswordStatus)
    Q_PROPERTY(QString shell READ Shell WRITE SetShell)
    Q_PROPERTY(QByteArray UUID READ Uuid)
    Q_PROPERTY(QByteArray userName READ UserName)

    AccountTypes AccountType() const;
    bool AutomaticLogin() const;
    QString FullName() const;
    quint64 Gid() const;
    quint64 Uid() const;
    QStringList Groups() const;
    QList<QByteArray> LayoutList() const;
    QString HomeDir() const;
    QList<QByteArray> IconFileList() const;
    QByteArray IconFile() const;
    QByteArray Layout() const;
    QByteArray Locale() const;
    bool Locked() const;
    qint32 MaxPasswordAge() const;
    QString PasswordHint() const;
    QDateTime PasswordLastChange() const;
    PasswdStatus PasswordStatus() const;
    QString Shell() const;
    QByteArray Uuid() const;
    QByteArray UserName() const;

    void SetAccountType(AccountTypes newtype);
    void SetAutomaticLogin(bool enabled);
    void SetFullName(const QString& newfullname);
    void SetGroups(const QStringList& newgroups);
    void SetLayoutList(const QList<QByteArray>& newlayouts);
    void SetHomeDir(const QString& newhomedir);
    void SetIconFile(const QUrl& newiconURL);
    void SetLayout(const QByteArray& newlayout);
    void SetLocale(const QByteArray& newlocale);
    void SetLocked(bool locked);
    void SetMaxPasswordAge(int newndays);
    void SetPassword(const QByteArray& newpassword);
    void SetPasswordHint(const QString& newpasswordhint);
    void SetShell(const QString& newshellpath);

    void AddGroup(const QString& group);
    void DeleteGroup(const QString& group);
    void DeleteIconFile(const QUrl& iconURL);
    bool IsPasswordExpired() const;
    ReminderInfo GetReminderInfo() const;
    QList<qint32> SecretQuestions() const;
    void SetSecretQuestions(const QList<Question>& newquestions);
    QList<qint32> VertifySecretQuestions(const QMap<qint32, QByteArray>& anwsers);
    PasswdExpirInfo PasswordExpirationInfo(qint64& dayLeft) const;

private:
    explicit DAccountsUser(const QString& path, QObject *parent = nullptr);
    QScopedPointer<DAccountsUserPrivate> d_ptr;
    Q_DECLARE_PRIVATE(DAccountsUser)
};


DACCOUNTS_END_NAMESPACE

// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "daccountstypes.h"
#include <QDateTime>
#include <QUrl>

DACCOUNTS_BEGIN_NAMESPACE

class DAccountsUserPrivate;

class DAccountsUser : public QObject
{
    Q_OBJECT

public:
    virtual ~DAccountsUser();

    Q_PROPERTY(AccountTypes accountType READ accountType)
    Q_PROPERTY(bool automaticLogin READ automaticLogin WRITE setAutomaticLogin)
    Q_PROPERTY(QString fullName READ fullName WRITE setFullName)
    Q_PROPERTY(quint64 GID READ GID)
    Q_PROPERTY(quint64 UID READ UID)
    Q_PROPERTY(QStringList groups READ groups WRITE setGroups)
    Q_PROPERTY(QList<QByteArray> layoutList READ layoutList WRITE setLayoutList)
    Q_PROPERTY(QString homeDir READ homeDir WRITE setHomeDir)
    Q_PROPERTY(QList<QByteArray> iconFileList READ iconFileList)
    Q_PROPERTY(QUrl iconFile READ iconFile WRITE setIconFile)
    Q_PROPERTY(QByteArray layout READ layout WRITE setLayout)
    Q_PROPERTY(QByteArray locale READ locale WRITE setLocale)
    Q_PROPERTY(bool locked READ locked WRITE setLocked)
    Q_PROPERTY(qint32 maxPasswordAge READ maxPasswordAge WRITE setMaxPasswordAge)
    Q_PROPERTY(QString passwordHint READ passwordHint WRITE setPasswordHint)
    Q_PROPERTY(QDateTime passwordLastChange READ passwordLastChange)
    Q_PROPERTY(PasswdStatus passwordStatus READ passwordStatus)
    Q_PROPERTY(QString shell READ shell WRITE setShell)
    Q_PROPERTY(QByteArray UUID READ UUID)
    Q_PROPERTY(QByteArray userName READ userName)
    Q_PROPERTY(bool noPasswdLogin READ noPasswdLogin WRITE setNopasswdLogin)
    Q_PROPERTY(QDateTime loginTime READ loginTime)
    Q_PROPERTY(QDateTime createdTime READ createdTime)

    AccountTypes accountType() const;
    bool automaticLogin() const;
    QString fullName() const;
    quint64 GID() const;
    quint64 UID() const;
    QStringList groups() const;
    QList<QByteArray> layoutList() const;
    QString homeDir() const;
    QList<QByteArray> iconFileList() const;
    QByteArray iconFile() const;
    QByteArray layout() const;
    QByteArray locale() const;
    bool locked() const;
    qint32 maxPasswordAge() const;
    QString passwordHint() const;
    QDateTime passwordLastChange() const;
    PasswdStatus passwordStatus() const;
    QString shell() const;
    QByteArray UUID() const;
    QByteArray userName() const;
    bool noPasswdLogin() const;
    QDateTime loginTime() const;
    QDateTime createdTime() const;

public slots:

    void setAutomaticLogin(const bool enabled);
    void setFullName(const QString &newfullname);
    void setGroups(const QStringList &newgroups);
    void setLayoutList(const QList<QByteArray> &newlayouts);
    void setHomeDir(const QString &newhomedir);
    void setIconFile(const QUrl &newiconURL);
    void setLayout(const QByteArray &newlayout);
    void setLocale(const QByteArray &newlocale);
    void setLocked(const bool locked);
    void setMaxPasswordAge(const int newndays);
    void setPassword(const QByteArray &newpassword);
    void setPasswordHint(const QString &newpasswordhint);
    void setShell(const QString &newshellpath);
    void setNopasswdLogin(const bool enabled);

    void addGroup(const QString &group);
    void deleteGroup(const QString &group);
    void deleteIconFile(const QUrl &iconURL);
    bool isPasswordExpired() const;
    ReminderInfo getReminderInfo() const;
    QList<qint32> secretQuestions() const;
    void setSecretQuestions(const QMap<qint32, QByteArray> &newquestions);
    QList<qint32> vertifySecretQuestions(const QMap<qint32, QString> &anwsers);
    PasswdExpirInfo passwordExpirationInfo(qint64 &dayLeft) const;

private:
    explicit DAccountsUser(const quint64 uid, QObject *parent = nullptr);
    QScopedPointer<DAccountsUserPrivate> d_ptr;
    friend class DAccountsManager;
    Q_DECLARE_PRIVATE(DAccountsUser)
    Q_DISABLE_COPY(DAccountsUser)
};

DACCOUNTS_END_NAMESPACE

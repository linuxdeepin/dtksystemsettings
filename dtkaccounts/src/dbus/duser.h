// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <QtGlobal>
#include <QList>
#include <QObject>
#include <QScopedPointer>
#include <qglobal.h>
#include <qscopedpointer.h>
#include <tuple>
#include "daccountstypes.h"
#include "ddbusinterface.h"

DACCOUNTS_BEGIN_NAMESPACE

class DUser : public QObject
{
    Q_OBJECT

public:
    explicit DUser(const QString &path, QObject *parent = nullptr);
    virtual ~DUser() = default;

    Q_PROPERTY(QList<LoginHistory> LoginHistory READ loginHistorys)
    Q_PROPERTY(bool AutomaticLogin READ automaticLogin)
    Q_PROPERTY(bool LocalAccount READ localAccount)
    Q_PROPERTY(bool Locked READ locked)
    Q_PROPERTY(bool SystemAccount READ systemAccount)
    Q_PROPERTY(qint32 AccountType READ accountType)
    Q_PROPERTY(qint32 PasswordMode READ passwordMode)
    Q_PROPERTY(qint64 LoginTime READ loginTime)
    Q_PROPERTY(QString Email READ email)
    Q_PROPERTY(QString HomeDirectory READ homeDirectory)
    Q_PROPERTY(QString IconFile READ iconFile)
    Q_PROPERTY(QString Language READ language)
    Q_PROPERTY(QString Location READ location)
    Q_PROPERTY(QString PasswordHint READ passwordHint)
    Q_PROPERTY(QString RealName READ realName)
    Q_PROPERTY(QString Shell READ shell)
    Q_PROPERTY(QString UserName READ userName)
    Q_PROPERTY(QString XSession READ xSession)
    Q_PROPERTY(quint64 LoginFrequency READ loginFrequency)
    Q_PROPERTY(quint64 Uid READ uid)

    QList<LoginHistory> loginHistorys() const;
    bool automaticLogin() const;
    bool localAccount() const;
    bool locked() const;
    bool systemAccount() const;
    qint32 accountType() const;
    qint32 passwordMode() const;
    qint64 loginTime() const;
    QString email() const;
    QString homeDirectory() const;
    QString iconFile() const;
    QString language() const;
    QString location() const;
    QString passwordHint() const;
    QString realName() const;
    QString shell() const;
    QString userName() const;
    QString xSession() const;
    quint64 loginFrequency() const;
    quint64 uid() const;

signals:
    void userChanged();
    void errorMessageChanged(const QString &message);

public slots:
    QString lastError() const;
    std::tuple<qint64,  // expiration time
               qint64,  // last_change_time
               qint64,  // min days between changes
               qint64,  // max days between changes
               qint64,  // days to warn
               qint64   // days after expiration until lock
               >
    GetPasswordExpirationPolicy();
    void SetAccountType(qint32 accountType);
    void SetAutomaticLogin(bool enabled);
    void SetEmail(const QString &email);
    void SetHomeDirectory(const QString &homedir);
    void SetIconFile(const QString &filename);
    void SetLanguage(const QString &language);
    void SetLocation(const QString &location);
    void SetLocked(bool locked);
    void SetPassword(const QString &password, const QString &hint);
    void SetPasswordHint(const QString &hint);
    void SetPasswordMode(qint32 mode);
    void SetRealName(const QString &name);
    void SetShell(const QString &shell);
    void SetUserName(const QString &name);
    void SetXSession(const QString &x_session);

private slots:
    void receiveChanged();

private:
    QString m_errorMessage;
    QScopedPointer<DDBusInterface> m_inter;
};

DACCOUNTS_END_NAMESPACE

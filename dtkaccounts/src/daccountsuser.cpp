// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "daccountsuser.h"
#include "daccountsuser_p.h"
#include <QMimeDatabase>
#include <QDebug>
#include <QRegularExpression>
#include <grp.h>
#include <pwd.h>
#include <sys/stat.h>
#include <unistd.h>
#include "dutils.h"
#include "dglobalconfig.h"

DACCOUNTS_BEGIN_NAMESPACE

DAccountsUserPrivate::DAccountsUserPrivate(const quint64 uid, DAccountsUser *parent)
    : q_ptr(parent)
{
    const auto &freeDesktopPath = "/org/freedesktop/Accounts/User" + QString::number(uid);
    const auto &daemonPath = "/com/deepin/daemon/Accounts/User" + QString::number(uid);
    m_dSystemUserInter = new DSystemUserInterface(daemonPath, this);
    m_dUserInter = new DUserInterface(freeDesktopPath, this);
}

DAccountsUser::DAccountsUser(const quint64 uid, QObject *parent)
    : QObject(parent)
    , d_ptr(new DAccountsUserPrivate(uid, this))
{
}

DAccountsUser::~DAccountsUser() {}

AccountTypes DAccountsUser::accountType() const
{
    auto typenum = d_ptr->m_dSystemUserInter->accountType();
    switch (typenum) {
        case 0:
            return AccountTypes::Default;
        case 1:
            return AccountTypes::Admin;
        case 2:
            return AccountTypes::Udcp;
        default:
            return AccountTypes::Unknown;  // 函数不应该运行到这里
    }
}

bool DAccountsUser::automaticLogin() const
{
    Q_D(const DAccountsUser);
    return d->m_dSystemUserInter->automaticLogin();
}

QString DAccountsUser::fullName() const
{
    Q_D(const DAccountsUser);
    return d->m_dUserInter->realName();
}

quint64 DAccountsUser::GID() const
{
    return getgid();
}

quint64 DAccountsUser::UID() const
{
    return getuid();
}

QStringList DAccountsUser::groups() const
{
    QStringList groupList;
    gid_t *groupid = nullptr;
    auto num = getgroups(0, groupid);
    if (num == -1)
        qWarning() << strerror(errno);
    groupid = static_cast<gid_t *>(malloc(sizeof(gid_t) * num));
    num = getgroups(num, groupid);
    if (num == -1) {
        qWarning() << strerror(errno);
        free(groupid);
        return groupList;
    }
    for (int i = 0; i < num; ++i) {
        auto g = getgrgid(groupid[i]);
        groupList.push_back(g->gr_name);
    }
    free(groupid);
    return groupList;
}

QList<QByteArray> DAccountsUser::layoutList() const
{
    Q_D(const DAccountsUser);
    QList<QByteArray> layouts;
    const auto &reply = d->m_dSystemUserInter->historyLayout();
    for (const auto &v : reply)
        layouts.push_back(v.toUtf8());
    return layouts;
}

QString DAccountsUser::homeDir() const
{
    Q_D(const DAccountsUser);
    return d->m_dUserInter->homeDirectory();
}

QList<QByteArray> DAccountsUser::iconFileList() const
{
    Q_D(const DAccountsUser);
    QList<QByteArray> icons;
    QDir icondir(UserIconsDir);
    QFileInfo cusdirinfo(UserCustomIconsDir);
    if (!icondir.exists()) {
        return icons;
    }
    icondir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
    icondir.setSorting(QDir::NoSort);
    icons.append(d->getImageFromDir(icondir));
    if (cusdirinfo.exists() and cusdirinfo.isDir()) {
        auto cusdir = QDir(cusdirinfo.absoluteFilePath());
        icondir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
        icondir.setSorting(QDir::NoSort);
        icons.append(d->getImageFromDir(cusdir));
    }
    return icons;
}

QByteArray DAccountsUser::iconFile() const
{
    Q_D(const DAccountsUser);
    return d->m_dSystemUserInter->iconFile().toUtf8();
}

QByteArray DAccountsUser::layout() const
{
    Q_D(const DAccountsUser);
    return d->m_dSystemUserInter->layout().toUtf8();
}

QByteArray DAccountsUser::locale() const
{
    Q_D(const DAccountsUser);
    return d->m_dSystemUserInter->locale().toUtf8();
}

bool DAccountsUser::locked() const
{
    Q_D(const DAccountsUser);
    return d->m_dUserInter->locked();
}

qint32 DAccountsUser::maxPasswordAge() const
{
    Q_D(const DAccountsUser);
    auto reply = d->m_dUserInter->getPasswordExpirationPolicy();
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return -1;
    }
    auto value = reply.argumentAt(3);
    if (!value.isNull()) {
        qWarning() << "can't get maxPasswordAge: max_days_between_changes null";
        return -1;
    }
    return value.toInt();
}

QString DAccountsUser::passwordHint() const
{
    Q_D(const DAccountsUser);
    return d->m_dSystemUserInter->passwordHint();
}

QDateTime DAccountsUser::passwordLastChange() const
{
    Q_D(const DAccountsUser);
    auto reply = d->m_dUserInter->getPasswordExpirationPolicy();
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return QDateTime::fromSecsSinceEpoch(0);
    }
    auto value = reply.argumentAt(1);
    if (!value.isNull()) {
        qWarning() << "can't get passwordLastChange: last_change_time null";
        return QDateTime::fromSecsSinceEpoch(0);
    }
    return QDateTime::fromSecsSinceEpoch(value.toLongLong());
}

PasswdStatus DAccountsUser::passwordStatus() const
{
    Q_D(const DAccountsUser);
    if (d->m_dUserInter->locked())
        return PasswdStatus::L;
    auto mode = d->m_dUserInter->passwordMode();
    if (mode == 0)
        return PasswdStatus::P;
    else if (mode == 2)
        return PasswdStatus::NP;
    // 函数不应该运行到这里
    return PasswdStatus::Unknown;
}

QString DAccountsUser::shell() const
{
    Q_D(const DAccountsUser);
    return d->m_dUserInter->shell();
}

QByteArray DAccountsUser::userName() const
{
    Q_D(const DAccountsUser);
    return d->m_dUserInter->userName().toUtf8();
}

QByteArray DAccountsUser::UUID() const
{
    Q_D(const DAccountsUser);
    return d->m_dSystemUserInter->UUID().toUtf8();
}

bool DAccountsUser::noPasswdLogin() const
{
    Q_D(const DAccountsUser);
    return d->m_dSystemUserInter->noPasswdLogin();
}

QDateTime DAccountsUser::loginTime() const
{
    Q_D(const DAccountsUser);
    auto time = d->m_dUserInter->loginTime();
    return QDateTime::fromSecsSinceEpoch(time);
}

QDateTime DAccountsUser::createdTime() const
{
    Q_D(const DAccountsUser);
    qint64 time = 0;
    QFileInfo bash(homeDir() + "/.bash_logout");
    if (bash.exists() and bash.isFile())
        time = d->getCreatedTimeFromFile(bash.absoluteFilePath());
    if (time == 0) {
        QFileInfo custom(UserConfigDir + userName());
        if (custom.exists() and custom.isFile())
            time = d->getCreatedTimeFromFile(custom.absoluteFilePath());
    }
    return QDateTime::fromSecsSinceEpoch(time);
}

void DAccountsUser::setNopasswdLogin(const bool enabled)
{
    Q_D(const DAccountsUser);
    auto reply = d->m_dSystemUserInter->enableNoPasswdLogin(enabled);
    reply.waitForFinished();
    if (!reply.isValid())
        qWarning() << reply.error().message();
}

void DAccountsUser::setAutomaticLogin(bool enabled)
{
    Q_D(const DAccountsUser);
    auto reply = d->m_dSystemUserInter->setAutomaticLogin(enabled);
    reply.waitForFinished();
    if (!reply.isValid())
        qWarning() << reply.error().message();
}

void DAccountsUser::setFullName(const QString &fullname)
{
    Q_D(const DAccountsUser);
    auto reply = d->m_dUserInter->setRealName(fullname);
    reply.waitForFinished();
    if (!reply.isValid())
        qWarning() << reply.error().message();
}

void DAccountsUser::setGroups(const QStringList &newgroups)
{
    Q_D(const DAccountsUser);
    auto reply = d->m_dSystemUserInter->setGroups(newgroups);
    reply.waitForFinished();
    if (!reply.isValid())
        qWarning() << reply.error().message();
}

void DAccountsUser::setLayoutList(const QList<QByteArray> &newlayouts)
{
    Q_D(const DAccountsUser);
    QStringList tmp;
    for (const auto &layout : newlayouts) {
        tmp.push_back(layout);
    }
    auto reply = d->m_dSystemUserInter->setHistoryLayout(tmp);
    reply.waitForFinished();
    if (!reply.isValid())
        qWarning() << reply.error().message();
}

void DAccountsUser::setHomeDir(const QString &newhomedir)
{
    Q_D(const DAccountsUser);
    auto reply = d->m_dUserInter->setHomeDirectory(newhomedir);
    reply.waitForFinished();
    if (!reply.isValid())
        qWarning() << reply.error().message();
}

void DAccountsUser::setIconFile(const QUrl &newiconURL)
{
    Q_D(const DAccountsUser);
    auto reply = d->m_dSystemUserInter->setIconFile(newiconURL.toLocalFile());
    reply.waitForFinished();
    if (!reply.isValid())
        qWarning() << reply.error().message();
}

void DAccountsUser::setLayout(const QByteArray &newlayout)
{
    Q_D(const DAccountsUser);
    auto reply = d->m_dSystemUserInter->setLayout(newlayout);
    reply.waitForFinished();
    if (!reply.isValid())
        qWarning() << reply.error().message();
}

void DAccountsUser::setLocale(const QByteArray &newlocale)
{
    Q_D(const DAccountsUser);
    auto reply = d->m_dSystemUserInter->setLocale(newlocale);
    reply.waitForFinished();
    if (!reply.isValid())
        qWarning() << reply.error().message();
}

void DAccountsUser::setLocked(const bool locked)
{
    Q_D(const DAccountsUser);
    auto reply = d->m_dSystemUserInter->setLocked(locked);
    reply.waitForFinished();
    if (!reply.isValid())
        qWarning() << reply.error().message();
}

void DAccountsUser::setMaxPasswordAge(const int newndays)
{
    Q_D(const DAccountsUser);
    auto reply = d->m_dSystemUserInter->setMaxPasswordAge(newndays);
    reply.waitForFinished();
    if (!reply.isValid())
        qWarning() << reply.error().message();
}

void DAccountsUser::setPassword(const QByteArray &newpassword)
{
    Q_D(const DAccountsUser);
    auto reply = d->m_dSystemUserInter->setPassword(newpassword);
    reply.waitForFinished();
    if (!reply.isValid())
        qWarning() << reply.error().message();
}

void DAccountsUser::setPasswordHint(const QString &newpasswordhint)
{
    Q_D(const DAccountsUser);
    auto reply = d->m_dSystemUserInter->setPasswordHint(newpasswordhint);
    reply.waitForFinished();
    if (!reply.isValid())
        qWarning() << reply.error().message();
}

void DAccountsUser::setShell(const QString &newshellpath)
{
    Q_D(const DAccountsUser);
    auto reply = d->m_dUserInter->setShell(newshellpath);
    reply.waitForFinished();
    if (!reply.isValid())
        qWarning() << reply.error().message();
}

void DAccountsUser::addGroup(const QString &group)
{
    Q_D(const DAccountsUser);
    auto reply = d->m_dSystemUserInter->addGroup(group);
    reply.waitForFinished();
    if (!reply.isValid())
        qWarning() << reply.error().message();
}

void DAccountsUser::deleteGroup(const QString &group)
{
    Q_D(const DAccountsUser);
    auto reply = d->m_dSystemUserInter->deleteGroup(group);
    reply.waitForFinished();
    if (!reply.isValid())
        qWarning() << reply.error().message();
}

void DAccountsUser::deleteIconFile(const QUrl &iconURL)
{
    Q_D(const DAccountsUser);
    auto reply = d->m_dSystemUserInter->deleteIconFile(iconURL.toLocalFile());
    reply.waitForFinished();
    if (!reply.isValid())
        qWarning() << reply.error().message();
}

bool DAccountsUser::isPasswordExpired() const
{
    auto age = maxPasswordAge();
    if (age > 0)
        return true;
    return false;
}

ReminderInfo DAccountsUser::getReminderInfo() const
{
    Q_D(const DAccountsUser);
    ReminderInfo info;
    auto reply = d->m_dSystemUserInter->getReminderInfo();
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return info;
    }
    const auto &info_p = reply.value();

    info.userName = info_p.userName;

    info.failCountSinceLastLogin = info_p.failCountSinceLastLogin;

    info.spent.lastChange = info_p.spent.lastChange;
    info.spent.expired = info_p.spent.expired;
    info.spent.inactive = info_p.spent.inactive;
    info.spent.max = info_p.spent.max;
    info.spent.min = info_p.spent.min;
    info.spent.warn = info_p.spent.warn;

    info.currentLogin.address = info_p.currentLogin.address;
    info.currentLogin.host = info_p.currentLogin.host;
    info.currentLogin.inittabID = info_p.currentLogin.inittabID;
    info.currentLogin.line = info_p.currentLogin.line;
    info.currentLogin.time = info_p.currentLogin.time;

    info.lastLogin.address = info_p.lastLogin.address;
    info.lastLogin.host = info_p.lastLogin.host;
    info.lastLogin.inittabID = info_p.lastLogin.inittabID;
    info.lastLogin.line = info_p.lastLogin.line;
    info.lastLogin.time = info_p.lastLogin.time;

    return info;
}

QList<qint32> DAccountsUser::secretQuestions() const
{
    Q_D(const DAccountsUser);
    auto reply = d->m_dSystemUserInter->getSecretQuestions();
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return {};
    }
    return reply.value();
}

void DAccountsUser::setSecretQuestions(const QMap<qint32, QByteArray> &newquestions)
{
    Q_D(const DAccountsUser);
    auto reply = d->m_dSystemUserInter->setSecretQuestions(newquestions);
    reply.waitForFinished();
    if (!reply.isValid())
        qWarning() << reply.error().message();
}

QList<qint32> DAccountsUser::vertifySecretQuestions(const QMap<qint32, QString> &anwsers)
{
    Q_D(const DAccountsUser);
    auto reply = d->m_dSystemUserInter->verifySecretQuestions(anwsers);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return {};
    }
    return reply.value();
}

PasswdExpirInfo DAccountsUser::passwordExpirationInfo(qint64 &dayLeft) const
{
    Q_D(const DAccountsUser);
    auto reply = d->m_dUserInter->getPasswordExpirationPolicy();
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return PasswdExpirInfo::Unknown;
    }

    const auto &lstch = reply.argumentAt(1);
    if (!lstch.isNull()) {
        qWarning() << "can't get passwordExpirationInfo: last_change_time is null.";
        return PasswdExpirInfo::Unknown;
    }
    if (lstch.toLongLong() == 0)
        return PasswdExpirInfo::Expired;

    const auto &max = reply.argumentAt(3);
    if (!max.isNull()) {
        qWarning() << "can't get passwordExpirationInfo: max_days_between_changes is null.";
        return PasswdExpirInfo::Unknown;
    }
    if (max.toLongLong() == -1)
        return PasswdExpirInfo::Normal;

    const auto &warn = reply.argumentAt(4);
    if (!warn.isNull()) {
        qWarning() << "can't get passwordExpirationInfo: days_to_warn is null.";
        return PasswdExpirInfo::Unknown;
    }
    const auto &curDate = QDateTime::currentDateTime().toSecsSinceEpoch() / (60 * 60 * 24);
    dayLeft = lstch.toLongLong() + max.toLongLong() - curDate;
    if (dayLeft < 0)
        return PasswdExpirInfo::Expired;
    if (dayLeft < warn.toLongLong())
        return PasswdExpirInfo::Closed;
    return PasswdExpirInfo::Normal;
}

QList<QByteArray> DAccountsUserPrivate::getImageFromDir(const QDir &dir) const
{
    QList<QByteArray> icons;
    auto list = dir.entryInfoList();
    if (list.empty()) {
        return icons;
    }
    QMimeDatabase db;
    for (const auto &v : list) {
        QMimeType type = db.mimeTypeForFile(v);
        if (!type.isValid() or !type.name().startsWith("image/"))
            continue;
        auto filepath = v.absoluteFilePath();
        if (filepath.contains(QRegularExpression("[\\x4e00-\\x9fa5]+")))
            continue;
        icons.push_back(("file://" + v.absoluteFilePath()).toUtf8());
    }
    return icons;
}

qint64 DAccountsUserPrivate::getCreatedTimeFromFile(const QString &file) const
{
    auto *info = static_cast<struct stat *>(malloc(sizeof(struct stat)));
    if (stat(file.toUtf8(), info) == -1) {
        qWarning() << strerror(errno);
        return 0;
    }
    return info->st_ctim.tv_sec;
}

DACCOUNTS_END_NAMESPACE

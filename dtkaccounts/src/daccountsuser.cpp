// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "daccountsuser.h"
#include "daccountstypes.h"
#include "daccountsuser_p.h"
#include "dbus/dutils.h"
#include "dglobalconfig.h"
#include <cstdint>
#include <grp.h>
#include <pwd.h>
#include <qlist.h>
#include <qdatetime.h>
#include <qtimezone.h>
#include <shadow.h>
#include <unistd.h>

DACCOUNTS_BEGIN_NAMESPACE

DAccountsUser::DAccountsUser(const QString &path, QObject *parent)
    : QObject(parent)
    , d_ptr(new DAccountsUserPrivate(path, this))
{
}

AccountTypes DAccountsUser::accountType() const
{
    auto typenum = d_ptr->m_dUserInter->accountType();
    switch (typenum) {
        case 0:
            return AccountTypes::Default;
        case 1:
            return AccountTypes::Admin;
        case 2:
            return AccountTypes::Udcp;
    }
}

bool DAccountsUser::automaticLogin() const
{
    Q_D(const DAccountsUser);
    return d->m_dUserInter->automaticLogin();
}

QString DAccountsUser::fullName() const
{
    Q_D(const DAccountsUser);
    return d->m_dUserInter->realName();
}

quint64 DAccountsUser::GID() const
{
    auto pw = getpwuid(getuid());
    auto gid = pw->pw_gid;
    free(pw);
    return gid;
}

quint64 DAccountsUser::UID() const
{
    Q_D(const DAccountsUser);
    return d->m_dUserInter->uid();
}

QStringList DAccountsUser::groups() const
{
    int ngroups = 1;
    QStringList grouplist;
    struct passwd *pw = getpwuid(getuid());
    gid_t *gs = reinterpret_cast<gid_t *>(malloc(sizeof(gid_t) * ngroups));
    if (pw == nullptr) {
        return grouplist;
    }
    if (gs == nullptr) {
        return grouplist;
    }

    if (getgrouplist(pw->pw_name, pw->pw_gid, gs, &ngroups) == -1) {
        gs = reinterpret_cast<gid_t *>(realloc(gs, sizeof(gid_t) * ngroups));
        if (gs == nullptr) {
            return grouplist;
        }
        if (getgrouplist(pw->pw_name, pw->pw_gid, gs, &ngroups) == -1) {
            return grouplist;
        }
    }

    for (int i = 0; i < ngroups; ++i) {
        grouplist.push_back(getgrgid(gs[i])->gr_name);
    }
    free(gs);
    return grouplist;
}

QList<QByteArray> DAccountsUser::layoutList() const
{
    Q_D(const DAccountsUser);
    QList<QByteArray> layouts;
    auto value = Dutils::getUserConfigValue(d->m_dUserInter->userName().toUtf8(), keyType::LayoutList);
    if (value.isEmpty()) {
        return layouts;
    }
    auto splitlayout = value.split("\\;;");
    for (const auto &v : splitlayout) {
        layouts.push_back((v + ";").toUtf8());
    }
    return layouts;
}

QString DAccountsUser::homeDir() const
{
    Q_D(const DAccountsUser);
    return d->m_dUserInter->homeDirectory();
}

QList<QByteArray> DAccountsUser::iconFileList() const
{
    QList<QByteArray> icons;
    QDir icondir(userIconsDir);
    QFileInfo cusdirinfo(userCustomIconsDir);
    if (!icondir.exists()) {
        return icons;
    }
    icondir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
    icondir.setSorting(QDir::NoSort);
    icons.append(Dutils::getImageFromDir(icondir));
    if (cusdirinfo.exists() and cusdirinfo.isDir()) {
        auto cusdir = QDir(cusdirinfo.absoluteFilePath());
        icondir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
        icondir.setSorting(QDir::NoSort);
        icons.append(Dutils::getImageFromDir(cusdir));
    }
    return icons;
}

QByteArray DAccountsUser::iconFile() const
{
    Q_D(const DAccountsUser);
    return Dutils::getUserConfigValue(d->m_dUserInter->userName().toUtf8(), keyType::IconFile).toUtf8();
}

QByteArray DAccountsUser::layout() const
{
    Q_D(const DAccountsUser);
    return Dutils::getUserConfigValue(d->m_dUserInter->userName().toUtf8(), keyType::Layout).toUtf8();
}

QByteArray DAccountsUser::locale() const
{
    Q_D(const DAccountsUser);
    return Dutils::getUserConfigValue(d->m_dUserInter->userName().toUtf8(), keyType::Locale).toUtf8();
}

bool DAccountsUser::locked() const
{
    Q_D(const DAccountsUser);
    return d->m_dUserInter->locked();
}

qint32 DAccountsUser::maxPasswordAge() const
{
    Q_D(const DAccountsUser);
    auto shadowinfo = getspnam(d->m_dUserInter->userName().toUtf8().data());
    if (shadowinfo == nullptr)
        return -1;
    return shadowinfo->sp_max;
}

QString DAccountsUser::passwordHint() const
{
    Q_D(const DAccountsUser);
    return d->m_dUserInter->passwordHint();
}

QDateTime DAccountsUser::passwordLastChange() const
{
    Q_D(const DAccountsUser);
    QDateTime timestamp(QDate(1970, 1, 1), QTime(0, 0, 0), QTimeZone::utc());
    auto shadowinfo = getspnam(d->m_dUserInter->userName().toUtf8().data());
    if (shadowinfo != nullptr)
        timestamp = timestamp.addDays(shadowinfo->sp_lstchg);
    return timestamp;
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
    return Dutils::getUserConfigValue(d->m_dUserInter->userName().toUtf8(), keyType::UUID).toUtf8();
}

void DAccountsUser::setAccountType(AccountTypes type)
{
    Q_D(const DAccountsUser);
    d->m_dUserInter->setAccountType(static_cast<qint32>(type));
}

void DAccountsUser::setAutomaticLogin(bool enabled)
{
    Q_D(const DAccountsUser);
    d->m_dUserInter->setAutomaticLogin(enabled);
}

void DAccountsUser::setFullName(const QString &fullname)
{
    Q_D(const DAccountsUser);
    d->m_dUserInter->setRealName(fullname);
}

void DAccountsUser::setGroups(const QStringList &newgroups)
{
    QString groups;
    for (const auto &v : newgroups) {
        groups += (v + ",");
    }
    groups = "usermod -G " + groups;
    system(groups.toUtf8());
}

void DAccountsUser::setLayoutList(const QList<QByteArray> &newlayouts) {}

void DAccountsUser::setHomeDir(const QString &newhomedir) {}

void DAccountsUser::setIconFile(const QUrl &newiconURL) {}

void DAccountsUser::setLayout(const QByteArray &newlayout) {}

void DAccountsUser::setLocale(const QByteArray &newlocale) {}

void DAccountsUser::setLocked(bool locked) {}

void DAccountsUser::setMaxPasswordAge(int newndays) {}

void DAccountsUser::setPassword(const QByteArray &newpassword) {}

void DAccountsUser::setPasswordHint(const QString &newpasswordhint) {}

void DAccountsUser::setShell(const QString &newshellpath) {}

void DAccountsUser::addGroup(const QString &group) {}

void DAccountsUser::deleteGroup(const QString &group) {}

void DAccountsUser::deleteIconFile(const QUrl &iconURL) {}

bool DAccountsUser::isPasswordExpired() const {}

ReminderInfo DAccountsUser::getReminderInfo() const {}

QList<qint32> DAccountsUser::secretQuestions() const {}

void DAccountsUser::setSecretQuestions(const QList<Question> &newquestions) {}

QList<qint32> DAccountsUser::vertifySecretQuestions(const QMap<qint32, QByteArray> &anwsers) {}

PasswdExpirInfo DAccountsUser::passwordExpirationInfo(qint64 &dayLeft) const {}

DACCOUNTS_END_NAMESPACE

// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "daccountstypes.h"
#include "daccountsuser.h"
#include "daccountsuser_p.h"
#include "dbus/duser.h"
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

DAccountsUser::DAccountsUser(const QString& path, QObject *parent)
: QObject(parent),d_ptr(new DAccountsUserPrivate(path,this))
{
}

AccountTypes DAccountsUser::AccountType() const
{
    auto typenum = d_ptr->u->accountType();
    switch(typenum){
        case 0: return AccountTypes::DEFAULT;
        case 1: return AccountTypes::ADMIN;
    }
    return AccountTypes::UNKNOWN;
}

bool DAccountsUser::AutomaticLogin() const
{
    return d_ptr->u->automaticLogin();
}

QString DAccountsUser::FullName() const
{
    return d_ptr->u->realName();
}

quint64 DAccountsUser::Gid() const
{
    auto pw = getpwuid(getuid());
    auto gid = pw->pw_gid;
    free(pw);
    return gid;
}

quint64 DAccountsUser::Uid() const
{
    return d_ptr->u->uid();
}

QStringList DAccountsUser::Groups() const
{
    int ngroups = 1;
    QStringList grouplist;
    struct passwd *pw = getpwuid(getuid());
    gid_t *gs = reinterpret_cast<gid_t*>(malloc(sizeof(gid_t) * ngroups));
    if(pw == nullptr)
    {
        return grouplist;
    }
    if(gs == nullptr)
    {
        return grouplist;
    }

    if(getgrouplist(pw->pw_name, pw->pw_gid, gs, &ngroups) == -1)
    {
        gs = reinterpret_cast<gid_t*>(realloc(gs, sizeof(gid_t) * ngroups));
        if(gs == nullptr)
        {
            return grouplist;
        }
        if(getgrouplist(pw->pw_name, pw->pw_gid, gs, &ngroups) == -1)
        {
            return grouplist;
        }
    }

    for(int i = 0; i < ngroups; ++i)
    {
        grouplist.push_back(getgrgid(gs[i])->gr_name);
    }
    free(gs);
    return grouplist;
}

QList<QByteArray> DAccountsUser::LayoutList() const
{
    QList<QByteArray> layouts;
    auto value = Dutils::getUserConfigValue(d_ptr->u->userName().toUtf8(), keyType::LayoutList);
    if(value.isEmpty())
    {
        return layouts;
    }
    auto splitlayout = value.split("\\;;");
    for(const auto& v : splitlayout)
    {
        layouts.push_back((v + ";").toUtf8());
    }
    return layouts;
}

QString DAccountsUser::HomeDir() const
{
    return d_ptr->u->homeDirectory();
}

QList<QByteArray> DAccountsUser::IconFileList() const
{
    QList<QByteArray> icons;
    QDir icondir(userIconsDir);
    QFileInfo cusdirinfo(userCustomIconsDir);
    if(!icondir.exists())
    {
        return icons;
    }
    icondir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
    icondir.setSorting(QDir::NoSort);
    icons.append(Dutils::getImageFromDir(icondir));
    if(cusdirinfo.exists() and cusdirinfo.isDir())
    {
        auto cusdir = QDir(cusdirinfo.absoluteFilePath());
        icondir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
        icondir.setSorting(QDir::NoSort);
        icons.append(Dutils::getImageFromDir(cusdir));
    }
    return icons;
}

QByteArray DAccountsUser::IconFile() const
{
    return Dutils::getUserConfigValue(d_ptr->u->userName().toUtf8(), keyType::IconFile).toUtf8();
}

QByteArray DAccountsUser::Layout() const
{
    return Dutils::getUserConfigValue(d_ptr->u->userName().toUtf8(), keyType::Layout).toUtf8();
}

QByteArray DAccountsUser::Locale() const
{
    return Dutils::getUserConfigValue(d_ptr->u->userName().toUtf8(), keyType::Locale).toUtf8();
}

bool DAccountsUser::Locked() const
{
    return d_ptr->u->locked();
}

qint32 DAccountsUser::MaxPasswordAge() const
{
    auto shadowinfo = getspnam(d_ptr->u->userName().toUtf8().data());
    if(shadowinfo == nullptr)
        return -1;
    return shadowinfo->sp_max;
}

QString DAccountsUser::PasswordHint() const
{
    return d_ptr->u->passwordHint();
}

QDateTime DAccountsUser::PasswordLastChange() const
{
    QDateTime timestamp(QDate(1970,1,1),QTime(0,0,0),QTimeZone::utc());
    auto shadowinfo = getspnam(d_ptr->u->userName().toUtf8().data());
    if(shadowinfo != nullptr)
        timestamp = timestamp.addDays(shadowinfo->sp_lstchg);
    return timestamp;
}

PasswdStatus DAccountsUser::PasswordStatus() const
{
    if(d_ptr->u->locked())
        return PasswdStatus::L;
    auto mode = d_ptr->u->passwordMode();
    if(mode == 0)
        return PasswdStatus::P;
    else if(mode == 2)
        return PasswdStatus::NP;
    // 函数不应该执行到这里
    return PasswdStatus::UNKNOWN;
}

QString DAccountsUser::Shell() const
{
    return d_ptr->u->shell();
}

QByteArray DAccountsUser::UserName() const
{
    return d_ptr->u->userName().toUtf8();
}

QByteArray DAccountsUser::Uuid() const
{
    return Dutils::getUserConfigValue(d_ptr->u->userName().toUtf8(), keyType::UUID).toUtf8();
}

void DAccountsUser::SetAccountType(AccountTypes type)
{
    if(type == AccountTypes::UNKNOWN)
        return;
    d_ptr->u->SetAccountType(static_cast<qint32>(type));
}

void DAccountsUser::SetAutomaticLogin(bool enabled)
{
    d_ptr->u->SetAutomaticLogin(enabled);
}

void DAccountsUser::SetFullName(const QString& fullname)
{
    d_ptr->u->SetRealName(fullname);
}

void DAccountsUser::SetGroups(const QStringList &newgroups)
{
    QString groups;
    for(const auto& v : newgroups)
    {
        groups += (v + ",");
    }
    groups = "usermod -G " + groups;
    system(groups.toUtf8());
}

void DAccountsUser::SetLayoutList(const QList<QByteArray>& newlayouts)
{

}

void DAccountsUser::SetHomeDir(const QString &newhomedir)
{

}

void DAccountsUser::SetIconFile(const QUrl &newiconURL)
{

}

void DAccountsUser::SetLayout(const QByteArray &newlayout)
{

}

void DAccountsUser::SetLocale(const QByteArray &newlocale)
{

}

void DAccountsUser::SetLocked(bool locked)
{

}

void DAccountsUser::SetMaxPasswordAge(int newndays)
{

}

void DAccountsUser::SetPassword(const QByteArray &newpassword)
{

}

void DAccountsUser::SetPasswordHint(const QString &newpasswordhint)
{

}

void DAccountsUser::SetShell(const QString &newshellpath)
{

}

void DAccountsUser::AddGroup(const QString &group)
{

}

void DAccountsUser::DeleteGroup(const QString &group)
{

}

void DAccountsUser::DeleteIconFile(const QUrl &iconURL)
{

}
bool DAccountsUser::IsPasswordExpired() const
{

}

ReminderInfo DAccountsUser::GetReminderInfo() const
{

}

QList<qint32> DAccountsUser::SecretQuestions() const
{

}

void DAccountsUser::SetSecretQuestions(const QList<Question> &newquestions)
{

}

QList<qint32> DAccountsUser::VertifySecretQuestions(const QMap<qint32, QByteArray> &anwsers)
{

}

PasswdExpirInfo DAccountsUser::PasswordExpirationInfo(qint64 &dayLeft) const
{

}

DACCOUNTS_END_NAMESPACE

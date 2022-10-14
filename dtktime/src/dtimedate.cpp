// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dtimedate.h"
#include "dtimedate_p.h"
#include "dbus/timedate1interface.h"
#include <qdbusreply.h>
#include <qdebug.h>
DTIME_BEGIN_NAMESPACE
DTimeDate::DTimeDate(QObject *parent)
    : QObject(parent)
    , d_ptr(new DTimeDatePrivate(this))
{
    Q_D(DTimeDate);
    d->m_timedate_inter = new TimeDate1Interface(this);
    // without signals
}

DTimeDate::~DTimeDate() {}
// properties
bool DTimeDate::canNTP() const
{
    Q_D(const DTimeDate);
    return d->m_timedate_inter->canNTP();
}

bool DTimeDate::localRTC() const
{
    Q_D(const DTimeDate);
    return d->m_timedate_inter->localRTC();
}

bool DTimeDate::NTP() const
{
    Q_D(const DTimeDate);
    return d->m_timedate_inter->NTP();
}

bool DTimeDate::NTPSynchronized() const
{
    Q_D(const DTimeDate);
    return d->m_timedate_inter->NTPSynchronized();
}

QString DTimeDate::timeZone() const
{
    Q_D(const DTimeDate);
    return d->m_timedate_inter->timeZone();
}

quint64 DTimeDate::RTCTimeUSec() const
{
    Q_D(const DTimeDate);
    return d->m_timedate_inter->RTCTimeUSec();
}

quint64 DTimeDate::timeUSec() const
{
    Q_D(const DTimeDate);
    return d->m_timedate_inter->timeUSec();
}
// slots
QStringList DTimeDate::listTimeZones() const
{
    Q_D(const DTimeDate);
    QDBusPendingReply<QStringList> reply = d->m_timedate_inter->listTimeZones();
    reply.waitForFinished();
    QStringList timezones;
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return timezones;
        ;
    }
    timezones = reply.value();
    return timezones;
}

void DTimeDate::setLocalRTC(const bool local_rtc, const bool fix_system, const bool interactive)
{
    Q_D(DTimeDate);
    QDBusPendingReply<> reply = d->m_timedate_inter->setLocalRTC(local_rtc, fix_system, interactive);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DTimeDate::setLocalTime(const bool use_NTP, const bool interactive)
{
    Q_D(DTimeDate);
    QDBusPendingReply<> reply = d->m_timedate_inter->setLocalTime(use_NTP, interactive);
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DTimeDate::setTime(const qint64 usec_utc, const bool relative, const bool interactive)
{
    Q_D(DTimeDate);
    QDBusPendingReply<> reply = d->m_timedate_inter->setTime(usec_utc, relative, interactive);
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DTimeDate::setTimeZone(const QString &timezone, const bool interactive)
{
    Q_D(DTimeDate);
    QDBusPendingReply<> reply = d->m_timedate_inter->setTimeZone(timezone, interactive);
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

DTIME_END_NAMESPACE
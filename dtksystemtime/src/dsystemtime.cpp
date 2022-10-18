// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dsystemtime.h"
#include "dsystemtime_p.h"
#include "dbus/timedate1interface.h"
#include "dbus/timesync1interface.h"
#include "dbus/dsystemtimetypes_p.h"
#include <qdbusreply.h>
#include <qdebug.h>
DSYSTEMTIME_BEGIN_NAMESPACE
DSystemTime::DSystemTime(QObject *parent)
    : QObject(parent)
    , d_ptr(new DSystemTimePrivate(this))
{
    Q_D(DSystemTime);
    d->m_timedate_inter = new TimeDate1Interface(this);
    d->m_timesync_inter = new TimeSync1Interface(this);
    // without signals
}

QStringList DSystemTime::fallbackNTPServers() const
{
    Q_D(const DSystemTime);
    return d->m_timesync_inter->fallbackNTPServers();
}

QStringList DSystemTime::linkNTPServers() const
{
    Q_D(const DSystemTime);
    return d->m_timesync_inter->linkNTPServers();
}

QStringList DSystemTime::systemNTPServers() const
{
    Q_D(const DSystemTime);
    return d->m_timesync_inter->systemNTPServers();
}

qint64 DSystemTime::frequency() const
{
    Q_D(const DSystemTime);
    return d->m_timesync_inter->frequency();
}

QString DSystemTime::serverName() const
{
    Q_D(const DSystemTime);
    return d->m_timesync_inter->serverName();
}

Address DSystemTime::serverAddress() const  // TODO: check it
{
    Q_D(const DSystemTime);
    Address_p address_p = d->m_timesync_inter->serverAddress();
    Address address;
    address.ip = address_p.ip;
    address.type = address_p.type;
    return address;
}

Message DSystemTime::NTPMessage() const
{
    Q_D(const DSystemTime);
    Message_p message_p = d->m_timesync_inter->NTPMessage();
    Message message;
    message.ntp_field_leap = message_p.ntp_field_leap;
    message.ntp_field_version = message_p.ntp_field_version;
    message.ntp_field_mode = message_p.ntp_field_mode;
    message.ntp_msg_stratum = message_p.ntp_msg_stratum;
    message.ntp_msg_precision = message_p.ntp_msg_precision;
    message.ntp_ts_short_to_usec_delay = message_p.ntp_ts_short_to_usec_delay;
    message.ntp_ts_short_to_usec_dispersion = message_p.ntp_ts_short_to_usec_dispersion;
    message.ntp_msg_refid = message_p.ntp_msg_refid;
    message.origin_time = message_p.origin_time;
    message.ntp_msg_recv_time = message_p.ntp_msg_recv_time;
    message.ntp_msg_trans_time = message_p.ntp_msg_trans_time;
    message.dest_time = message_p.dest_time;
    message.spike = message_p.spike;
    message.packet_count = message_p.packet_count;
    message.samples_jitter = message_p.samples_jitter;
    return message;
}

quint64 DSystemTime::pollIntervalMaxUSec() const
{
    Q_D(const DSystemTime);
    return d->m_timesync_inter->pollIntervalMaxUSec();
}

quint64 DSystemTime::pollIntervalMinUSec() const
{
    Q_D(const DSystemTime);
    return d->m_timesync_inter->pollIntervalMinUSec();
}

quint64 DSystemTime::pollIntervalUSec() const
{
    Q_D(const DSystemTime);
    return d->m_timesync_inter->pollIntervalUSec();
}

quint64 DSystemTime::rootDistanceMaxUSec() const
{
    Q_D(const DSystemTime);
    return d->m_timesync_inter->rootDistanceMaxUSec();
}

DSystemTime::~DSystemTime() {}
// properties
bool DSystemTime::canNTP() const
{
    Q_D(const DSystemTime);
    return d->m_timedate_inter->canNTP();
}

bool DSystemTime::localRTC() const
{
    Q_D(const DSystemTime);
    return d->m_timedate_inter->localRTC();
}

bool DSystemTime::NTP() const
{
    Q_D(const DSystemTime);
    return d->m_timedate_inter->NTP();
}

bool DSystemTime::NTPSynchronized() const
{
    Q_D(const DSystemTime);
    return d->m_timedate_inter->NTPSynchronized();
}

QString DSystemTime::timeZone() const
{
    Q_D(const DSystemTime);
    return d->m_timedate_inter->timeZone();
}

quint64 DSystemTime::RTCTimeUSec() const
{
    Q_D(const DSystemTime);
    return d->m_timedate_inter->RTCTimeUSec();
}

quint64 DSystemTime::timeUSec() const
{
    Q_D(const DSystemTime);
    return d->m_timedate_inter->timeUSec();
}
// slots
QStringList DSystemTime::listTimeZones() const
{
    Q_D(const DSystemTime);
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

void DSystemTime::setLocalRTC(const bool local_rtc, const bool fix_system, const bool interactive)
{
    Q_D(DSystemTime);
    QDBusPendingReply<> reply = d->m_timedate_inter->setLocalRTC(local_rtc, fix_system, interactive);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DSystemTime::setNTP(const bool use_NTP, const bool interactive)
{
    Q_D(DSystemTime);
    QDBusPendingReply<> reply = d->m_timedate_inter->setNTP(use_NTP, interactive);
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DSystemTime::setTime(const qint64 usec_utc, const bool relative, const bool interactive)
{
    Q_D(DSystemTime);
    QDBusPendingReply<> reply = d->m_timedate_inter->setTime(usec_utc, relative, interactive);
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DSystemTime::setTimeZone(const QString &timezone, const bool interactive)
{
    Q_D(DSystemTime);
    QDBusPendingReply<> reply = d->m_timedate_inter->setTimeZone(timezone, interactive);
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

DSYSTEMTIME_END_NAMESPACE
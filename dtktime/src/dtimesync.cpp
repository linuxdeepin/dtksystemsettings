// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dtimesync.h"
#include "dtimesync_p.h"
#include "dbus/dtimetypes_p.h"
#include "dbus/timesync1interface.h"
#include <qdbusreply.h>
#include <qdebug.h>
DTIME_BEGIN_NAMESPACE
DTimeSync::DTimeSync(QObject *parent)
    : QObject(parent)
    , d_ptr(new DTimeSyncPrivate(this))
{
    Q_D(DTimeSync);
    d->m_timesync_inter = new TimeSync1Interface(this);
    // without signal
}
DTimeSync::~DTimeSync() {}

QStringList DTimeSync::fallbackNTPServers() const
{
    Q_D(const DTimeSync);
    return d->m_timesync_inter->fallbackNTPServers();
}

QStringList DTimeSync::linkNTPServers() const
{
    Q_D(const DTimeSync);
    return d->m_timesync_inter->linkNTPServers();
}

QStringList DTimeSync::systemNTPServers() const
{
    Q_D(const DTimeSync);
    return d->m_timesync_inter->systemNTPServers();
}

qint64 DTimeSync::frequency() const
{
    Q_D(const DTimeSync);
    return d->m_timesync_inter->frequency();
}

QString DTimeSync::serverName() const
{
    Q_D(const DTimeSync);
    return d->m_timesync_inter->serverName();
}

Address DTimeSync::serverAddress() const  // TODO: check it
{
    Q_D(const DTimeSync);
    Address_p address_p = d->m_timesync_inter->serverAddress();
    Address address;
    address.ip = address_p.ip;
    address.type = address_p.type;
    return address;
}

Message DTimeSync::NTPMessage() const
{
    Q_D(const DTimeSync);
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

quint64 DTimeSync::pollIntervalMaxUSec() const
{
    Q_D(const DTimeSync);
    return d->m_timesync_inter->pollIntervalMaxUSec();
}

quint64 DTimeSync::pollIntervalMinUSec() const
{
    Q_D(const DTimeSync);
    return d->m_timesync_inter->pollIntervalMinUSec();
}

quint64 DTimeSync::pollIntervalUSec() const
{
    Q_D(const DTimeSync);
    return d->m_timesync_inter->pollIntervalUSec();
}

quint64 DTimeSync::rootDistanceMaxUSec() const
{
    Q_D(const DTimeSync);
    return d->m_timesync_inter->rootDistanceMaxUSec();
}

DTIME_END_NAMESPACE

/*
    Q_D(const DLoginManager);
    const auto &result = d->m_inter->scheduledShutdown();
    ScheduledShutdownValue value;
    value.type = Utils::stringToShutdownType(result.type);
    value.time = QDateTime::fromMSecsSinceEpoch(result.usec / 1000);
    return value;
*/
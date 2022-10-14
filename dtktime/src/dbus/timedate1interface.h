// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef __TIMEDATE1INTERFACE_H__
#define __TIMEDATE1INTERFACE_H__

#include <qobject.h>
#include <qscopedpointer.h>
#include <qdbuspendingreply.h>
#include "dtktime_globle.h"
#include "ddbusinterface.h"

DTIME_BEGIN_NAMESPACE
class TimeDate1Interface : public QObject
{
    Q_OBJECT
public:
    explicit TimeDate1Interface(QObject *parent = nullptr);
    virtual ~TimeDate1Interface();
    // properties
    Q_PROPERTY(bool CanNTP READ canNTP);
    Q_PROPERTY(bool LocalRTC READ localRTC);
    Q_PROPERTY(bool NTP READ NTP);
    Q_PROPERTY(bool NTPSynchronized READ NTPSynchronized);
    Q_PROPERTY(QString TimeZone READ timeZone);
    Q_PROPERTY(quint64 RTCTimeUSec READ RTCTimeUSec);
    Q_PROPERTY(quint64 TimeUSec READ timeUSec);
    bool canNTP() const;
    bool localRTC() const;
    bool NTP() const;
    bool NTPSynchronized() const;
    QString timeZone() const;
    quint64 RTCTimeUSec() const;
    quint64 timeUSec() const;
    // slot
public slots:
    QDBusPendingReply<QStringList> listTimeZones() const;
    QDBusPendingReply<> setLocalRTC(const bool local_rtc, const bool fix_system, const bool interactive);
    QDBusPendingReply<> setLocalTime(const bool use_NTP, const bool interactive);
    QDBusPendingReply<> setTime(const qint64 usec_utc, const bool relative, const bool interactive);
    QDBusPendingReply<> setTimeZone(const QString &timezone, const bool interactive);

private:
    DDBusInterface *m_inter;
};

DTIME_END_NAMESPACE
#endif
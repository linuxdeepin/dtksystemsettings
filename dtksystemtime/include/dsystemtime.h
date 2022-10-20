// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DSYSTEMTIME_H
#define DSYSTEMTIME_H

#include <qobject.h>
#include <qscopedpointer.h>
#include <qdatetime.h>
#include "dtksystemtime_global.h"
#include "dsystemtimetypes.h"

DSYSTEMTIME_BEGIN_NAMESPACE
class DSystemTimePrivate;
class DSystemTime : public QObject
{
    Q_OBJECT
public:
    explicit DSystemTime(QObject *parent = nullptr);
    virtual ~DSystemTime();
    // properties
    Q_PROPERTY(bool canNTP READ canNTP);
    Q_PROPERTY(bool localRTC READ localRTC);
    Q_PROPERTY(bool NTP READ NTP);
    Q_PROPERTY(bool NTPSynchronized READ NTPSynchronized);
    Q_PROPERTY(QString timeZone READ timeZone);
    Q_PROPERTY(quint64 RTCTimeUSec READ RTCTimeUSec);
    Q_PROPERTY(QDateTime timeDate READ timeDate);
    bool canNTP() const;
    bool localRTC() const;
    bool NTP() const;
    bool NTPSynchronized() const;
    QString timeZone() const;
    quint64 RTCTimeUSec() const;
    QDateTime timeDate() const;
    // sync properties
    Q_PROPERTY(QStringList fallbackNTPServers READ fallbackNTPServers);
    Q_PROPERTY(QStringList linkNTPServers READ linkNTPServers);
    Q_PROPERTY(QStringList systemNTPServers READ systemNTPServers);
    Q_PROPERTY(qint64 frequency READ frequency);
    Q_PROPERTY(QString serverName READ serverName);
    Q_PROPERTY(Address serverAddress READ serverAddress);
    Q_PROPERTY(Message NTPMessage READ NTPMessage);
    Q_PROPERTY(quint64 pollIntervalMaxUSec READ pollIntervalMaxUSec);
    Q_PROPERTY(quint64 pollIntervalMinUSec READ pollIntervalMinUSec);
    Q_PROPERTY(quint64 pollIntervalUSec READ pollIntervalUSec);
    Q_PROPERTY(quint64 rootDistanceMaxUSec READ rootDistanceMaxUSec);
    QStringList fallbackNTPServers() const;
    QStringList linkNTPServers() const;
    QStringList systemNTPServers() const;
    qint64 frequency() const;
    QString serverName() const;
    Address serverAddress() const;
    Message NTPMessage() const;
    quint64 pollIntervalMaxUSec() const;
    quint64 pollIntervalMinUSec() const;
    quint64 pollIntervalUSec() const;
    quint64 rootDistanceMaxUSec() const;
    // slot
public slots:
    QStringList listTimeZones() const;
    void setLocalRTC(const bool local_rtc, const bool fix_system, const bool interactive);  // TODO: fix system是否可以被丢掉
    void setNTP(const bool use_NTP, const bool interactive);
    void setRelativeTime(const qint64 usec_utc, const bool interactive);
    void setAbsoluteTime(const QDateTime &time, const bool interactive);
    void setTimeZone(const QString &timezone, const bool interactive);

private:
    QScopedPointer<DSystemTimePrivate> d_ptr;
    Q_DECLARE_PRIVATE(DSystemTime)
};

DSYSTEMTIME_END_NAMESPACE
#endif
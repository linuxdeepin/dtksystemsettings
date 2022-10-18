// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef TIMEDATE1SERVICE_H
#define TIMEDATE1SERVICE_H

#include <qobject.h>
#include <qscopedpointer.h>
#include <qdbuspendingreply.h>
#include "ddbusinterface.h"

class TimeDate1Service : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.deepin.daemon.FakeTimeDate1")
public:
    explicit TimeDate1Service(QObject *parent = nullptr);
    virtual ~TimeDate1Service();
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
    Q_SCRIPTABLE QStringList ListTimeZones() const;
    Q_SCRIPTABLE void SetLocalRTC(const bool local_rtc, const bool fix_system, const bool interactive);
    Q_SCRIPTABLE void SetNTP(const bool use_NTP, const bool interactive);
    Q_SCRIPTABLE void SetTime(const qint64 usec_utc, const bool relative, const bool interactive);
    Q_SCRIPTABLE void SetTimeZone(const QString &timezone, const bool interactive);

public:
    bool setLocalRTC_sig = false;
    bool setLocalTime_sig = false;
    int setTime_sig = 0;
    QString setTimeZone_sig;

private:
    DDBusInterface *m_inter;
    void registerService();
    void unRegisterService();
};

#endif
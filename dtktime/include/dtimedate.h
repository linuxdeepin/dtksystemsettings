// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef __DTIMEDATE_H__
#define __DTIMEDATE_H__

#include <qobject.h>
#include <qscopedpointer.h>
#include "dtktime_globle.h"

DTIME_BEGIN_NAMESPACE
class DTimeDatePrivate;
class DTimeDate : public QObject
{
    Q_OBJECT
public:
    explicit DTimeDate(QObject *parent = nullptr);
    virtual ~DTimeDate();
    // properties
    Q_PROPERTY(bool canNTP READ canNTP);
    Q_PROPERTY(bool localRTC READ localRTC);
    Q_PROPERTY(bool NTP READ NTP);
    Q_PROPERTY(bool NTPSynchronized READ NTPSynchronized);
    Q_PROPERTY(QString timeZone READ timeZone);
    Q_PROPERTY(quint64 RTCTimeUSec READ RTCTimeUSec);
    Q_PROPERTY(quint64 timeUSec READ timeUSec);
    bool canNTP() const;
    bool localRTC() const;
    bool NTP() const;
    bool NTPSynchronized() const;
    QString timeZone() const;
    quint64 RTCTimeUSec() const;
    quint64 timeUSec() const;
    // slot
public slots:
    QStringList listTimeZones() const;
    void setLocalRTC(const bool local_rtc, const bool fix_system, const bool interactive);
    void setLocalTime(const bool use_NTP, const bool interactive);
    void setTime(const qint64 usec_utc, const bool relative, const bool interactive);
    void setTimeZone(const QString &timezone, const bool interactive);

private:
    QScopedPointer<DTimeDatePrivate> d_ptr;
    Q_DECLARE_PRIVATE(DTimeDate)
};

DTIME_END_NAMESPACE
#endif
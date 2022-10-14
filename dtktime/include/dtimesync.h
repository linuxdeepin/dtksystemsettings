// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
#ifndef __DTIMESYNC_H__
#define __DTIMESYNC_H__
#include <qobject.h>
#include <qscopedpointer.h>
#include "dtimetypes.h"
#include "dtktime_globle.h"

DTIME_BEGIN_NAMESPACE
class DTimeSyncPrivate;
class DTimeSync : public QObject
{
    Q_OBJECT
public:
    explicit DTimeSync(QObject *parent = nullptr);
    virtual ~DTimeSync();
    // properties
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
    // properties
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

private:
    QScopedPointer<DTimeSyncPrivate> d_ptr;
    Q_DECLARE_PRIVATE(DTimeSync);
};
DTIME_END_NAMESPACE

#endif  // !__DTIMESYNC_H__
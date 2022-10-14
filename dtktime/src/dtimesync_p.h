// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
#ifndef __DTIMESYNC_P_H__
#define __DTIMESYNC_P_H__

#include "dtimesync.h"

class DDBusInterface;

DTIME_BEGIN_NAMESPACE

class TimeSync1Interface;
class DTimeSyncPrivate : public QObject
{
    Q_OBJECT
public:
    explicit DTimeSyncPrivate(DTimeSync *parent)
        : q_ptr(parent)
    {
    }
    virtual ~DTimeSyncPrivate() {}

public:
    TimeSync1Interface *m_timesync_inter;
    DTimeSync *q_ptr;
    Q_DECLARE_PUBLIC(DTimeSync)
};
DTIME_END_NAMESPACE

#endif
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
#ifndef __DTIMEDATE_P_H__
#define __DTIMEDATE_P_H__

#include "dtimedate.h"

class DDBusInterface;

DTIME_BEGIN_NAMESPACE

class TimeDate1Interface;
class DTimeDatePrivate : public QObject
{
    Q_OBJECT
public:
    explicit DTimeDatePrivate(DTimeDate *parent)
        : q_ptr(parent)
    {
    }
    virtual ~DTimeDatePrivate() {}

public:
    TimeDate1Interface *m_timedate_inter;
    DTimeDate *q_ptr;
    Q_DECLARE_PUBLIC(DTimeDate)
};

DTIME_END_NAMESPACE

#endif  // !__DTIMEDATE_P_H__

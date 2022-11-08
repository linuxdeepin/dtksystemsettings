// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <QObject>
#include <dtknotification_global.h>

DNOTIFICATION_BEGIN_NAMESPACE

class DNotificationAppConfig;
class DNotificationInterface;

class DNotificationAppConfigPrivate : public QObject
{
    Q_OBJECT
public:
    explicit DNotificationAppConfigPrivate(const QString &id, DNotificationAppConfig *parent = nullptr);
    ~DNotificationAppConfigPrivate() = default;

    DNotificationAppConfig *q_ptr;
    DNotificationInterface *m_dNoticationInter;
    const QString &m_id;
    Q_DECLARE_PUBLIC(DNotificationAppConfig)
};

DNOTIFICATION_END_NAMESPACE

// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "ddbusinterface.h"
#include "namespace.h"
#include <qdbuspendingreply.h>
#include <qscopedpointer.h>

DPOWER_BEGIN_NAMESPACE

class UPowerManagerInterface : public QObject
{
    Q_OBJECT
public:
    explicit UPowerManagerInterface(QObject *parent = nullptr);
    virtual ~UPowerManagerInterface();
    // properties
    Q_PROPERTY(bool LidIsClosed READ lidIsClosed)
    Q_PROPERTY(bool LidIsPresent READ lidIsPresent)
    Q_PROPERTY(bool OnBattery READ onBattery)
    Q_PROPERTY(QString DaemonVersion READ daemonVersion)
    bool lidIsClosed() const;
    bool lidIsPresent() const;
    bool onBattery() const;
    QString daemonVersion() const;

signals:
    void DeviceAdded(const QDBusObjectPath &path);
    void DeviceRemoved(const QDBusObjectPath &path);

public slots:
    QDBusPendingReply<QList<QDBusObjectPath>> enumerateDevices() const;
    QDBusPendingReply<QString> getCriticalAction() const;
    QDBusPendingReply<QDBusObjectPath> getDisplayDevice() const;

private:
    DDBusInterface *m_inter;
};

DPOWER_END_NAMESPACE

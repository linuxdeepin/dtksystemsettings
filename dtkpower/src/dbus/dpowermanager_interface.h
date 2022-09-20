// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "ddbusinterface.h"
#include "namespace.h"
#include <QDBusObjectPath>
#include <qdbuspendingreply.h>
#include <qlist.h>
#include <qobject.h>
#include <qobjectdefs.h>
#include <qscopedpointer.h>
#include <qvariant.h>

DPOWER_BEGIN_NAMESPACE

class DPowerManager_interface : public QObject
{
    Q_OBJECT
public:
    explicit DPowerManager_interface(QObject *parent = nullptr);
    virtual ~DPowerManager_interface();
    // properties
    Q_PROPERTY(bool LidlsClosed READ lidlsClosed)
    Q_PROPERTY(bool LidlsPresent READ lidlsPresent)
    Q_PROPERTY(bool OnBattery READ onBattery)
    Q_PROPERTY(QString DaemonVersion READ daemonVersion)
    bool lidlsClosed() const;
    bool lidlsPresent() const;
    bool onBattery() const;
    QString daemonVersion() const;

signals:
    void errorMessageChanged(const QString &message);
    void DeviceAdded(const QDBusObjectPath &path);
    void DeviceRemoved(const QDBusObjectPath &path);
public slots:
    QDBusPendingReply<QList<QDBusObjectPath>> enumerateDevices();
    QDBusPendingReply<QString> getCriticalAction();
    QDBusPendingReply<QDBusObjectPath> getDisplayDevice();

private:
    QString m_errorMessage;
    QScopedPointer<DDBusInterface> m_inter;
};

DPOWER_END_NAMESPACE
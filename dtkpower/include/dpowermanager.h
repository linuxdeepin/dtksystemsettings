// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma  once

#include <qlist.h>
#include <qobject.h>
#include <qobjectdefs.h>
#include <QDBusObjectPath>
#include "namespace.h"

DPOWER_BEGIN_NAMESPACE
class DPowerManagerPrivate;
class DPowerDevice;

class DPowerManager:public QObject
{
    Q_OBJECT
public:
    explicit DPowerManager(QObject *parent = nullptr);
    virtual ~DPowerManager();
    //properties
    Q_PROPERTY(bool LidlsClosed READ lidlsClosed)
    Q_PROPERTY(bool LidlsPresent READ lidlsPresent)
    Q_PROPERTY(bool OnBattery READ onBattery)
    Q_PROPERTY(QString DaemonVersion READ daemonVersion)
    bool lidlsClosed() const;
    bool lidlsPresent() const;
    bool onBattery() const;
    QString daemonVersion() const;
    QSharedPointer<DPowerDevice> getDisplayDevice();
    QSharedPointer<DPowerDevice> getDeviceByName(const QString &name);

signals:
    void errorMessageChanged(const QString &message);
    void DeviceAdded(const QDBusObjectPath &path);
    void DeviceRemoved(const QDBusObjectPath &path);
public slots:
    QString lastError() const;
    QStringList devices();
    QString getCriticalAction();
    


private:
    QScopedPointer<DPowerManagerPrivate> d_ptr;
    Q_DECLARE_PRIVATE(DPowerManager)

};

DPOWER_END_NAMESPACE
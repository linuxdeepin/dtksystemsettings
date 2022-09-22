// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <qobject.h>
#include "namespace.h"

DPOWER_BEGIN_NAMESPACE
class DPowerManagerPrivate;
class DPowerDevice;

class DPowerManager : public QObject
{
    Q_OBJECT
public:
    explicit DPowerManager(QObject *parent = nullptr);
    virtual ~DPowerManager();
    // properties
    Q_PROPERTY(bool lidIsClosed READ lidIsClosed)
    Q_PROPERTY(bool lidIsPresent READ lidIsPresent)
    Q_PROPERTY(bool onBattery READ onBattery)
    Q_PROPERTY(QString daemonVersion READ daemonVersion)
    bool lidIsClosed() const;
    bool lidIsPresent() const;
    bool onBattery() const;
    QString daemonVersion() const;
    QSharedPointer<DPowerDevice> displayDevice() const;
    QSharedPointer<DPowerDevice> findDeviceByName(const QString &name) const;

signals:
    void deviceAdded(const QString &name);
    void deviceRemoved(const QString &name);

public slots:
    QStringList devices() const;
    QString criticalAction() const;

private:
    QScopedPointer<DPowerManagerPrivate> d_ptr;
    Q_DECLARE_PRIVATE(DPowerManager)
};

DPOWER_END_NAMESPACE

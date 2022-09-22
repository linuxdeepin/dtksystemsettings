// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dpowermanager.h"
#include "dpowermanager_p.h"

#include <qdebug.h>
#include <qsharedpointer.h>

#include "dpowerdevice.h"
#include "dbus/upowermanagerinterface.h"

DPOWER_BEGIN_NAMESPACE

void DPowerManagerPrivate::connectDBusSignal()
{
    Q_Q(DPowerManager);
    connect(m_manager_inter, &UPowerManagerInterface::DeviceAdded, q, [q](const QDBusObjectPath &path) {
        emit q->DeviceAdded(path.path());
    });
    connect(m_manager_inter, &UPowerManagerInterface::DeviceRemoved, q, [q](const QDBusObjectPath &path) {
        emit q->DeviceRemoved(path.path());
    });
}

DPowerManager::DPowerManager(QObject *parent)
    : QObject(parent)
    , d_ptr(new DPowerManagerPrivate(this))
{
    Q_D(DPowerManager);
    d->m_manager_inter = new UPowerManagerInterface(this);
}

DPowerManager::~DPowerManager() {}

// properties
bool DPowerManager::lidlsClosed() const
{
    Q_D(const DPowerManager);
    return d->m_manager_inter->lidlsClosed();
}

bool DPowerManager::lidlsPresent() const
{
    Q_D(const DPowerManager);
    return d->m_manager_inter->lidlsPresent();
}

bool DPowerManager::onBattery() const
{
    Q_D(const DPowerManager);
    return d->m_manager_inter->onBattery();
}

QString DPowerManager::daemonVersion() const
{
    Q_D(const DPowerManager);
    return d->m_manager_inter->daemonVersion();
}

// pubilc slots
QStringList DPowerManager::devices() const
{
    Q_D(const DPowerManager);
    QDBusPendingReply<QList<QDBusObjectPath>> reply = d->m_manager_inter->enumerateDevices();
    reply.waitForFinished();
    QStringList devices;
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return devices;
    }
    for (auto &&device_p : reply.value()) {
        devices.append(device_p.path().mid(32));
    }
    return devices;
}

QString DPowerManager::getCriticalAction() const
{
    Q_D(const DPowerManager);
    QDBusPendingReply<QString> reply = d->m_manager_inter->getCriticalAction();
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return reply;
    }
    return reply;
}

QSharedPointer<DPowerDevice> DPowerManager::getDisplayDevice() const
{
    Q_D(const DPowerManager);
    QDBusPendingReply<QDBusObjectPath> reply = d->m_manager_inter->getDisplayDevice();
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return nullptr;
    }
    QString                      name = reply.value().path().mid(32);
    QSharedPointer<DPowerDevice> device(new DPowerDevice(name, nullptr));
    return device;
}

QSharedPointer<DPowerDevice> DPowerManager::getDeviceByName(const QString &name) const
{
    if (!devices().contains(name)) {
        qWarning() << QStringLiteral("Device does not exist");
        return nullptr;
    }
    QSharedPointer<DPowerDevice> device(new DPowerDevice(name, nullptr));
    return device;
}

DPOWER_END_NAMESPACE

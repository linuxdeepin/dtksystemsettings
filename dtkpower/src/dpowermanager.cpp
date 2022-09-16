// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dpowermanager.h"
#include "dpowerdevice.h"
#include "dpowermanager_p.h"
#include "namespace.h"
#include "ddbusinterface.h"
#include <cstddef>
#include <qdbusconnection.h>
#include <qdbusextratypes.h>
#include <qdbuspendingreply.h>
#include <qlist.h>
#include <qstringliteral.h>
#include <QSharedPointer>
#include <QDBusObjectPath>

DPOWER_BEGIN_NAMESPACE
DPowerManager::DPowerManager(QObject *parent)
    : QObject(parent)
    , d_ptr(new DPowerManagerPrivate(this))
{
    const QString &Service = QStringLiteral("org.freedesktop.UPower");
    const QString &Path = QStringLiteral("/org/freedesktop/UPower");  
    const QString &Interface = QStringLiteral("org.freedesktop.UPower");

    Q_D(DPowerManager);
    d->m_inter = new DDBusInterface(Service, Path, Interface, QDBusConnection::systemBus(), d);
}

DPowerManager::~DPowerManager(){}

// properties
bool DPowerManager::lidlsClosed() const
{
    Q_D(const DPowerManager);
    return qdbus_cast<bool>(d->m_inter->property("LidlsClosed"));
}

bool DPowerManager::lidlsPresent() const
{
    Q_D(const DPowerManager);
    return qdbus_cast<bool>(d->m_inter->property("LidlsPresent"));
}

bool DPowerManager::onBattery() const
{
    Q_D(const DPowerManager);
    return qdbus_cast<bool>(d->m_inter->property("OnBattery"));
}

QString DPowerManager::daemonVersion() const
{
    Q_D(const DPowerManager);
    return qdbus_cast<QString>(d->m_inter->property("DaemonVersion"));
}

// pubilc slots
QString DPowerManager::lastError() const
{
    Q_D(const DPowerManager);
    return d->m_errorMessage;
}

QStringList DPowerManager::devices()
{
    Q_D(DPowerManager);
    QDBusPendingReply<QList<QDBusObjectPath>> reply = d->m_inter->asyncCall(QStringLiteral("EnumerateDevices"));
    reply.waitForFinished();
    QStringList devices;
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return devices;
    }
    for (auto &&device_p :reply.value()){
        devices.append(device_p.path().mid(32));
    }
    return devices;
}

QString DPowerManager::getCriticalAction()
{
    Q_D(DPowerManager);
    QDBusPendingReply<QString> reply = d->m_inter->asyncCall(QStringLiteral("GetCriticalAction"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return reply;
    }
    return reply;
}

QSharedPointer<DPowerDevice> DPowerManager::getDisplayDevice()
{
    Q_D(DPowerManager);
    QDBusPendingReply<QDBusObjectPath> reply = d->m_inter->asyncCall(QStringLiteral("GetDisplayDevice"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return nullptr;
    }
    QString name = reply.value().path().mid(32);
    QSharedPointer<DPowerDevice> device(new DPowerDevice(name,nullptr));
    return device;
}

QSharedPointer<DPowerDevice> DPowerManager::getDeviceByName(const QString &name)
{
    Q_D(DPowerManager);
    if (!devices().contains(name)) {
        d->m_errorMessage = "Device does not exist";
        emit errorMessageChanged(d->m_errorMessage);
        return nullptr;
    }
    QSharedPointer<DPowerDevice> device(new DPowerDevice(name,nullptr));
    return device;
}

DPOWER_END_NAMESPACE
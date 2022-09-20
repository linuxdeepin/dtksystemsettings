// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dpowermanager.h"
#include "dbus/dpowermanager_interface.h"
#include "dpowerdevice.h"
#include "dpowermanager_p.h"
#include "namespace.h"
#include <QDBusObjectPath>
#include <QSharedPointer>
#include <cstddef>
#include <qdbusconnection.h>
#include <qdbusextratypes.h>
#include <qdbuspendingreply.h>
#include <qlist.h>
#include <qstringliteral.h>

DPOWER_BEGIN_NAMESPACE
DPowerManager::DPowerManager(QObject *parent)
    : QObject(parent)
    , d_ptr(new DPowerManagerPrivate(this))
{
}

DPowerManager::~DPowerManager() {}

// properties
bool DPowerManager::lidlsClosed() const
{
    return d_ptr->m_manager_inter->lidlsClosed();
}

bool DPowerManager::lidlsPresent() const
{
    d_ptr->m_manager_inter->lidlsPresent();
}

bool DPowerManager::onBattery() const
{
    d_ptr->m_manager_inter->onBattery();
}

QString DPowerManager::daemonVersion() const
{
    return d_ptr->m_manager_inter->daemonVersion();
}

// pubilc slots
QString DPowerManager::lastError() const
{
    return d_ptr->m_errorMessage;
}

QStringList DPowerManager::devices()
{
    QDBusPendingReply<QList<QDBusObjectPath>> reply = d_ptr->m_manager_inter->enumerateDevices();
    reply.waitForFinished();
    QStringList devices;
    if (!reply.isValid()) {
        d_ptr->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d_ptr->m_errorMessage);
        return devices;
    }
    for (auto &&device_p : reply.value()) {
        devices.append(device_p.path().mid(32));
    }
    return devices;
}

QString DPowerManager::getCriticalAction()
{
    QDBusPendingReply<QString> reply = d_ptr->m_manager_inter->getCriticalAction();
    reply.waitForFinished();
    if (!reply.isValid()) {
        d_ptr->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d_ptr->m_errorMessage);
        return reply;
    }
    return reply;
}

QSharedPointer<DPowerDevice> DPowerManager::getDisplayDevice()
{
    QDBusPendingReply<QDBusObjectPath> reply = d_ptr->m_manager_inter->getDisplayDevice();
    reply.waitForFinished();
    if (!reply.isValid()) {
        d_ptr->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d_ptr->m_errorMessage);
        return nullptr;
    }
    QString name = reply.value().path().mid(32);
    QSharedPointer<DPowerDevice> device(new DPowerDevice(name, nullptr));
    return device;
}

QSharedPointer<DPowerDevice> DPowerManager::getDeviceByName(const QString &name)
{
    if (!devices().contains(name)) {
        d_ptr->m_errorMessage = "Device does not exist";
        emit errorMessageChanged(d_ptr->m_errorMessage);
        return nullptr;
    }
    QSharedPointer<DPowerDevice> device(new DPowerDevice(name, nullptr));
    return device;
}

DPOWER_END_NAMESPACE
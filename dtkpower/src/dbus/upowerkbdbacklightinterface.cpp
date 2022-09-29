// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "upowerkbdbacklightinterface.h"
#include "ddbusinterface.h"
#include "namespace.h"
#include <qdbusconnection.h>
#include <qdbuspendingreply.h>

DPOWER_BEGIN_NAMESPACE
UPowerKbdBacklightInterface::UPowerKbdBacklightInterface(QObject *parent)
    : QObject(parent)
{
#ifdef USE_FAKE_INTERFACE
    static const QString &Service = QStringLiteral("com.deepin.daemon.FakePower");
    static const QString &Path = QStringLiteral("/com/deepin/daemon/FakePower");
    static const QString &Interface = QStringLiteral("com.deepin.daemon.FakePower");
    QDBusConnection connection = QDBusConnection::sessionBus();
#else
    static const QString &Service = QStringLiteral("org.freedesktop.UPower");
    static const QString &Path = QStringLiteral("/org/freedesktop/UPower/KbdBacklight");
    static const QString &Interface = QStringLiteral("org.freedesktop.UPower.KbdBacklight");
    QDBusConnection connection = QDBusConnection::systemBus();
#endif
    m_inter = new DDBusInterface(Service, Path, Interface, connection, this);
}

UPowerKbdBacklightInterface::~UPowerKbdBacklightInterface() {}

// pubilc slots

QDBusPendingReply<uint> UPowerKbdBacklightInterface::getBrightness() const
{
    return m_inter->asyncCall(QStringLiteral("GetBrightness"));
}

QDBusPendingReply<uint> UPowerKbdBacklightInterface::getMaxBrightness() const
{
    return m_inter->asyncCall(QStringLiteral("GetMaxBrightness"));
}

QDBusPendingReply<> UPowerKbdBacklightInterface::setBrightness(uint value)
{
    return m_inter->asyncCallWithArgumentList("SetBrightness", {QVariant::fromValue(value)});
}

DPOWER_END_NAMESPACE

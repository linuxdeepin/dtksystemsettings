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
    const QString &Service = QStringLiteral("org.freedesktop.UPower");
    const QString &Path = QStringLiteral("/org/freedesktop/UPower/KbdBacklight");
    const QString &Interface = QStringLiteral("org.freedesktop.UPower.KbdBacklight");

    m_inter.reset(new DDBusInterface(Service, Path, Interface, QDBusConnection::systemBus(), this));
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

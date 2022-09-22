// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dkbdbacklight_interface.h"
#include "ddbusinterface.h"
#include "namespace.h"
#include <qdbusconnection.h>
#include <qdbuspendingreply.h>

DPOWER_BEGIN_NAMESPACE
DKbdBacklight_interface::DKbdBacklight_interface(QObject *parent)
    : QObject(parent)
{
    const QString &Service = QStringLiteral("org.freedesktop.UPower");
    const QString &Path = QStringLiteral("/org/freedesktop/UPower/KbdBacklight");
    const QString &Interface = QStringLiteral("org.freedesktop.UPower.KbdBacklight");

    m_inter.reset(new DDBusInterface(Service, Path, Interface, QDBusConnection::systemBus(), this));
}

DKbdBacklight_interface::~DKbdBacklight_interface() {}

// pubilc slots

QDBusPendingReply<uint> DKbdBacklight_interface::getBrightness() const
{
    return m_inter->asyncCall(QStringLiteral("GetBrightness"));
}

QDBusPendingReply<uint> DKbdBacklight_interface::getMaxBrightness() const
{
    return m_inter->asyncCall(QStringLiteral("GetMaxBrightness"));
}

QDBusPendingReply<> DKbdBacklight_interface::setBrightness(uint value)
{
    return m_inter->asyncCallWithArgumentList("SetBrightness", {QVariant::fromValue(value)});
}

DPOWER_END_NAMESPACE

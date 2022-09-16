// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dkbdbacklight.h"
#include "dkbdbacklight_p.h"
#include "namespace.h"
#include "ddbusinterface.h"
#include <qdbusconnection.h>
#include <qdbuspendingreply.h>

DPOWER_BEGIN_NAMESPACE
DKbdBacklight::DKbdBacklight(QObject *parent)
    : QObject(parent)
    , d_ptr(new DKbdBacklightPrivate(this))
{
    const QString &Service = QStringLiteral("org.freedesktop.UPower");
    const QString &Path = QStringLiteral("/org/freedesktop/UPower/KbdBacklight");  
    const QString &Interface = QStringLiteral("org.freedesktop.UPower.KbdBacklight");

    Q_D(DKbdBacklight);
    d->m_inter = new DDBusInterface(Service, Path, Interface, QDBusConnection::systemBus(), d);
}

DKbdBacklight::~DKbdBacklight(){}

// pubilc slots
QString DKbdBacklight::lastError() const
{
    Q_D(const DKbdBacklight);
    return d->m_errorMessage;
}

uint DKbdBacklight::getBrightness()
{
    Q_D(DKbdBacklight);
    QDBusPendingReply<uint> reply = d->m_inter->asyncCall(QStringLiteral("GetBrightness"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return false;
    }
    return reply.value();
}

uint DKbdBacklight::getMaxBrightness()
{
    Q_D(DKbdBacklight);
    QDBusPendingReply<uint> reply = d->m_inter->asyncCall(QStringLiteral("GetMaxBrightness"));
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
        return false;
    }
    return reply.value();
}

void DKbdBacklight::setBrightness(uint value)
{
    Q_D(DKbdBacklight);
    QDBusPendingReply<> reply = d->m_inter->asyncCallWithArgumentList("SetBrightness", {QVariant::fromValue(value)});
    reply.waitForFinished();
    if (!reply.isValid()) {
        d->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d->m_errorMessage);
    }
}

DPOWER_END_NAMESPACE
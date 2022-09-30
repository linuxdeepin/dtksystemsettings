// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dkbdbacklight.h"
#include "dkbdbacklight_p.h"

#include <qdebug.h>
#include <qdbuspendingreply.h>

#include "dbus/upowerkbdbacklightinterface.h"
#include "namespace.h"
#include "dpowertypes.h"

DPOWER_BEGIN_NAMESPACE

void DKbdBacklightPrivate::connectDBusSignal()
{
    Q_Q(DKbdBacklight);
    connect(m_kb_inter, &UPowerKbdBacklightInterface::BrightnessChanged, q, &DKbdBacklight::brightnessChanged);
    connect(
        m_kb_inter, &UPowerKbdBacklightInterface::BrightnessChangedWithSource, q, [q](const uint value, const QString &source) {
            QMap<QString, KbdSource> sourceMap;
            sourceMap["internal"] = KbdSource::Internal;
            sourceMap["external"] = KbdSource::External;
            KbdSource realSource;
            if (sourceMap.contains(source))
                realSource = sourceMap[source];
            else
                realSource = KbdSource::Unknown;
            emit q->brightnessChangedWithSource(value, realSource);
        });
}

DKbdBacklight::DKbdBacklight(QObject *parent)
    : QObject(parent)
    , d_ptr(new DKbdBacklightPrivate(this))
{
    Q_D(DKbdBacklight);
    d->m_kb_inter = new UPowerKbdBacklightInterface(this);
}

DKbdBacklight::~DKbdBacklight() {}

// pubilc slots
uint DKbdBacklight::brightness() const
{
    Q_D(const DKbdBacklight);
    QDBusPendingReply<uint> reply = d->m_kb_inter->getBrightness();
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return false;
    }
    return reply.value();
}

uint DKbdBacklight::maxBrightness() const
{
    Q_D(const DKbdBacklight);
    QDBusPendingReply<uint> reply = d->m_kb_inter->getMaxBrightness();
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return false;
    }
    return reply.value();
}

void DKbdBacklight::setBrightness(const uint value)
{
    Q_D(DKbdBacklight);
    QDBusPendingReply<> reply = d->m_kb_inter->setBrightness(value);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

DPOWER_END_NAMESPACE

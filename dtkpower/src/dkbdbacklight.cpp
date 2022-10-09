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
    // qDebug() << connect(m_kb_inter, &UPowerKbdBacklightInterface::BrightnessChanged, this, [=](const qint32 value) {
    // });
    connect(
        m_kb_inter, &UPowerKbdBacklightInterface::BrightnessChangedWithSource, q, [q](const qint32 value, const QString &source) {
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
    d->connectDBusSignal();
}

DKbdBacklight::~DKbdBacklight() {}

// pubilc slots
qint32 DKbdBacklight::brightness() const
{
    Q_D(const DKbdBacklight);
    QDBusPendingReply<qint32> reply = d->m_kb_inter->getBrightness();
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return false;
    }
    return reply.value();
}

qint32 DKbdBacklight::maxBrightness() const
{
    Q_D(const DKbdBacklight);
    QDBusPendingReply<qint32> reply = d->m_kb_inter->getMaxBrightness();
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return false;
    }
    return reply.value();
}

void DKbdBacklight::setBrightness(const qint32 value)
{
    Q_D(DKbdBacklight);
    QDBusPendingReply<> reply = d->m_kb_inter->setBrightness(value);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

DPOWER_END_NAMESPACE

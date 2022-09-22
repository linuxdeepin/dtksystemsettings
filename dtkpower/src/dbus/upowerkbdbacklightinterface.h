// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "ddbusinterface.h"
#include "namespace.h"
#include <qdbuspendingreply.h>
#include <qscopedpointer.h>

DPOWER_BEGIN_NAMESPACE
class DKbdBacklightPrivate;

class UPowerKbdBacklightInterface : public QObject
{
    Q_OBJECT
public:
    explicit UPowerKbdBacklightInterface(QObject *parent = nullptr);
    virtual ~UPowerKbdBacklightInterface();

signals:
    void BrightnessChanged(const uint value);
    void BrightnessChangedWithSource(const uint value, const QString &source);

public slots:
    QDBusPendingReply<uint> getBrightness() const;
    QDBusPendingReply<uint> getMaxBrightness() const;
    QDBusPendingReply<> setBrightness(uint value);

private:
    QScopedPointer<DDBusInterface> m_inter;
};

DPOWER_END_NAMESPACE

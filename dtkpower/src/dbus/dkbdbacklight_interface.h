// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "ddbusinterface.h"
#include "namespace.h"
#include <cstddef>
#include <qdbuspendingreply.h>
#include <qobject.h>
#include <qobjectdefs.h>
#include <qscopedpointer.h>

DPOWER_BEGIN_NAMESPACE
class DKbdBacklightPrivate;

class DKbdBacklight_interface : public QObject
{
    Q_OBJECT
public:
    explicit DKbdBacklight_interface(QObject *parent = nullptr);
    virtual ~DKbdBacklight_interface();

signals:
    void errorMessageChanged(const QString &message);
    void BrightnessChanged(const uint value);
    void BrightnessChangedWithSource(const uint value, const QString &source);

public slots:
    QString lastError() const;
    QDBusPendingReply<uint> getBrightness();
    QDBusPendingReply<uint> getMaxBrightness();
    QDBusPendingReply<> setBrightness(uint value);

private:
    QScopedPointer<DDBusInterface> m_inter;
};

DPOWER_END_NAMESPACE
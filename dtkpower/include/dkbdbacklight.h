// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <qobject.h>
#include <qscopedpointer.h>
#include "namespace.h"

DPOWER_BEGIN_NAMESPACE
class DKbdBacklightPrivate;

class DKbdBacklight : public QObject
{
    Q_OBJECT
public:
    explicit DKbdBacklight(QObject *parent = nullptr);
    virtual ~DKbdBacklight();

signals:
    void brightnessChanged(const uint value);
    void brightnessChangedWithSource(const uint value, const QString &source);

public slots:
    uint brightness() const;
    uint maxBrightness() const;
    void setBrightness(uint value);

private:
    QScopedPointer<DKbdBacklightPrivate> d_ptr;
    Q_DECLARE_PRIVATE(DKbdBacklight)
};

DPOWER_END_NAMESPACE

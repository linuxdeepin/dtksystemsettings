// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <qobject.h>
#include <qscopedpointer.h>
#include "dtkpower_global.h"

DPOWER_BEGIN_NAMESPACE
class DKbdBacklightPrivate;
enum class KbdSource;

class DKbdBacklight : public QObject
{
    Q_OBJECT
public:
    virtual ~DKbdBacklight();

signals:
    void brightnessChanged(const qint32 value);
    void brightnessChangedWithSource(const qint32 value, const KbdSource &source);

public slots:
    qint32 brightness() const;
    qint32 maxBrightness() const;
    void setBrightness(const qint32 value);

private:
    QScopedPointer<DKbdBacklightPrivate> d_ptr;
    Q_DECLARE_PRIVATE(DKbdBacklight)

    explicit DKbdBacklight(QObject *parent = nullptr);
    Q_DISABLE_COPY(DKbdBacklight)

    friend class DPowerManager;
};

DPOWER_END_NAMESPACE

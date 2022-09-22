// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <QtGlobal>
#include <QList>
#include <QObject>
#include <QScopedPointer>
#include "ddbusinterface.h"
#include "daccountstypes.h"

DACCOUNTS_BEGIN_NAMESPACE

class DAccountsDDEInterface : public QObject
{
    Q_OBJECT

public:
    explicit DAccountsDDEInterface(QObject *parent = nullptr);
    virtual ~DAccountsDDEInterface() = default;

private:
    QScopedPointer<DDBusInterface> m_inter;
};

DACCOUNTS_END_NAMESPACE

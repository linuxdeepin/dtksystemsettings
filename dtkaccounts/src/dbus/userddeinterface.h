// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <QtGlobal>
#include <QList>
#include <QObject>
#include <QScopedPointer>
#include <qtmetamacros.h>
#include "ddbusinterface.h"
#include "daccountstypes.h"

DACCOUNTS_BEGIN_NAMESPACE

class DUserDDEInterface : public QObject
{
    Q_OBJECT

public:
    explicit DUserDDEInterface(const QString &path, QObject *parent = nullptr);
    virtual ~DUserDDEInterface() = default;

private:
    QScopedPointer<DDBusInterface> m_inter;
};

DACCOUNTS_END_NAMESPACE

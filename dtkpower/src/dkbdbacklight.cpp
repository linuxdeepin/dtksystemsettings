// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dkbdbacklight.h"
#include "dkbdbacklight_p.h"
#include "namespace.h"
#include <qdbusconnection.h>
#include <qdbuspendingreply.h>

DPOWER_BEGIN_NAMESPACE
DKbdBacklight::DKbdBacklight(QObject *parent)
    : QObject(parent)
    , d_ptr(new DKbdBacklightPrivate(this))
{
}

DKbdBacklight::~DKbdBacklight() {}

// pubilc slots
QString DKbdBacklight::lastError() const
{
    return d_ptr->m_errorMessage;
}

uint DKbdBacklight::getBrightness()
{
    QDBusPendingReply<uint> reply = d_ptr->m_kb_inter.getBrightness();
    reply.waitForFinished();
    if (!reply.isValid()) {
        d_ptr->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d_ptr->m_errorMessage);
        return false;
    }
    return reply.value();
}

uint DKbdBacklight::getMaxBrightness()
{
    QDBusPendingReply<uint> reply = d_ptr->m_kb_inter.getMaxBrightness();
    reply.waitForFinished();
    if (!reply.isValid()) {
        d_ptr->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d_ptr->m_errorMessage);
        return false;
    }
    return reply.value();
}

void DKbdBacklight::setBrightness(uint value)
{
    QDBusPendingReply<> reply = d_ptr->m_kb_inter.setBrightness(value);
    reply.waitForFinished();
    if (!reply.isValid()) {
        d_ptr->m_errorMessage = reply.error().message();
        emit errorMessageChanged(d_ptr->m_errorMessage);
    }
}

DPOWER_END_NAMESPACE
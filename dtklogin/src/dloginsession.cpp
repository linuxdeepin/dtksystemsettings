// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dloginsession.h"

#include "dloginsession_p.h"
#include <qdbuspendingreply.h>
#include <qdir.h>
#include <qobject.h>
#include <qprocess.h>
#include <qsettings.h>
#include <qvariant.h>
#include <qdebug.h>
#include <qdbusconnection.h>
#include <qdatetime.h>

#include "login1sessioninterface.h"
#include "dloginutils.h"
DLOGIN_BEGIN_NAMESPACE

DLoginSession::DLoginSession(const QString &path, QObject *parent)
    : QObject(parent)
    , d_ptr(new DLoginSessionPrivate(this))
{
    const QString &Service = QStringLiteral("org.freedesktop.login1");

    Q_D(DLoginSession);
    DBusSeatPath::registerMetaType();
    DBusUserPath::registerMetaType();
    d->m_inter = new Login1SessionInterface(Service, path, QDBusConnection::systemBus(), this);
    connect(d->m_inter, &Login1SessionInterface::locked, this, &DLoginSession::locked);
    connect(d->m_inter, &Login1SessionInterface::pauseDevice, this, &DLoginSession::pauseDevice);
    connect(d->m_inter, &Login1SessionInterface::resumeDevice, this, &DLoginSession::resumeDevice);
    connect(d->m_inter, &Login1SessionInterface::unlocked, this, &DLoginSession::unlocked);
}

DLoginSession::~DLoginSession(){};

bool DLoginSession::active() const
{
    Q_D(const DLoginSession);
    return d->m_inter->active();
}

bool DLoginSession::idleHint() const
{
    Q_D(const DLoginSession);
    return d->m_inter->idleHint();
}

bool DLoginSession::lockedHint() const
{
    Q_D(const DLoginSession);
    return d->m_inter->lockedHint();
}

bool DLoginSession::remote() const
{
    Q_D(const DLoginSession);
    return d->m_inter->remote();
}
SessionClass DLoginSession::sessionClass() const
{
    Q_D(const DLoginSession);
    return Utils::stringToSessionClass(d->m_inter->sessionClass());
}
QString DLoginSession::desktop() const
{
    Q_D(const DLoginSession);
    return d->m_inter->desktop();
}
QString DLoginSession::display() const
{
    Q_D(const DLoginSession);
    return d->m_inter->display();
}
QString DLoginSession::id() const
{
    Q_D(const DLoginSession);
    return d->m_inter->id();
}
QString DLoginSession::name() const
{
    Q_D(const DLoginSession);
    return d->m_inter->name();
}

QString DLoginSession::remoteHost() const
{
    Q_D(const DLoginSession);
    return d->m_inter->remoteHost();
}
QString DLoginSession::remoteUser() const
{
    Q_D(const DLoginSession);
    return d->m_inter->remoteUser();
}

QString DLoginSession::scope() const
{
    Q_D(const DLoginSession);
    return d->m_inter->scope();
}

QString DLoginSession::service() const
{
    Q_D(const DLoginSession);
    return d->m_inter->service();
}

SessionState DLoginSession::state() const
{
    Q_D(const DLoginSession);
    return Utils::stringToSessionState(d->m_inter->state());
}

QString DLoginSession::TTY() const
{
    Q_D(const DLoginSession);
    return d->m_inter->TTY();
}

SessionType DLoginSession::type() const
{
    Q_D(const DLoginSession);
    return Utils::stringToSessionType(d->m_inter->type());
}

QString DLoginSession::seat() const
{
    Q_D(const DLoginSession);
    const auto &result = d->m_inter->seat();
    return result.seatId;
}
quint32 DLoginSession::user() const
{
    Q_D(const DLoginSession);
    const auto &result = d->m_inter->user();
    return result.userId;
}

quint32 DLoginSession::audit() const
{
    Q_D(const DLoginSession);
    return d->m_inter->audit();
}

quint32 DLoginSession::leader() const
{
    Q_D(const DLoginSession);
    return d->m_inter->leader();
}
quint32 DLoginSession::VTNr() const
{
    Q_D(const DLoginSession);
    return d->m_inter->VTNr();
}

QDateTime DLoginSession::idleSinceHint() const
{
    Q_D(const DLoginSession);
    return QDateTime::fromMSecsSinceEpoch(d->m_inter->idleSinceHint());
}

QDateTime DLoginSession::idleSinceHintMonotonic() const
{
    Q_D(const DLoginSession);
    return QDateTime::fromMSecsSinceEpoch(d->m_inter->idleSinceHintMonotonic());
}

QDateTime DLoginSession::createdTime() const
{
    Q_D(const DLoginSession);
    return QDateTime::fromMSecsSinceEpoch(d->m_inter->timestamp());
}
QDateTime DLoginSession::createdTimeMonotonic() const
{
    Q_D(const DLoginSession);
    return QDateTime::fromMSecsSinceEpoch(d->m_inter->timestampMonotonic());
}

void DLoginSession::activate()
{
    Q_D(DLoginSession);
    QDBusPendingReply<> reply = d->m_inter->activate();
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DLoginSession::kill(const QString &who, const uint signalNumber)
{
    Q_D(DLoginSession);
    QDBusPendingReply<> reply = d->m_inter->kill(who, signalNumber);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}
void DLoginSession::lock()
{
    Q_D(DLoginSession);
    QDBusPendingReply<> reply = d->m_inter->lock();
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}
void DLoginSession::pauseDeviceComplete(const uint major, const uint minor)
{
    Q_D(DLoginSession);
    QDBusPendingReply<> reply = d->m_inter->pauseDeviceComplete(major, minor);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}
void DLoginSession::releaseControl()
{
    Q_D(DLoginSession);
    QDBusPendingReply<> reply = d->m_inter->releaseControl();
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}
void DLoginSession::releaseDevice(const uint major, const uint minor)
{
    Q_D(DLoginSession);
    QDBusPendingReply<> reply = d->m_inter->releaseDevice(major, minor);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DLoginSession::setBrightness(const QString &subsystem, const QString &name, const uint brightness)
{
    Q_D(DLoginSession);
    QDBusPendingReply<> reply = d->m_inter->setBrightness(subsystem, name, brightness);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DLoginSession::setIdleHint(const bool idle)
{
    Q_D(DLoginSession);
    QDBusPendingReply<> reply = d->m_inter->setIdleHint(idle);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}
void DLoginSession::setLockedHint(const bool locked)
{
    Q_D(DLoginSession);
    QDBusPendingReply<> reply = d->m_inter->setLockedHint(locked);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DLoginSession::setType(const QString &type)
{
    Q_D(DLoginSession);
    QDBusPendingReply<> reply = d->m_inter->setType(type);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

void DLoginSession::takeControl(const bool force)
{
    Q_D(DLoginSession);
    QDBusPendingReply<> reply = d->m_inter->takeControl(force);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

std::tuple<int,  // fd
           bool  // inactive
           >
DLoginSession::takeDevice(uint major, uint minor)
{
    Q_D(DLoginSession);
    QDBusPendingReply<int, bool> reply = d->m_inter->takeDevice(major, minor);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
        return std::tuple<int, bool>();
    }
    return std::make_tuple<int, bool>(reply.argumentAt<0>(), reply.argumentAt<1>());
}
void DLoginSession::terminate()
{
    Q_D(DLoginSession);
    QDBusPendingReply<> reply = d->m_inter->terminate();
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}
void DLoginSession::unlock()
{
    Q_D(DLoginSession);
    QDBusPendingReply<> reply = d->m_inter->unlock();
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

QStringList DLoginSession::autostartList()
{
    // Get autostart directories
    QStringList autostartPaths;
    QStringList autostartApps;
    // First get current login user's dir
    QString defaultUserConfigDir;
    QString homeDir = QProcessEnvironment::systemEnvironment().value("HOME");
    if (!homeDir.isEmpty()) {
        defaultUserConfigDir = homeDir + "/.config";
    }
    QString configuredUserConfigDir = QProcessEnvironment::systemEnvironment().value("XDG_CONFIG_HOME");
    if (!configuredUserConfigDir.isEmpty() && !QDir::isAbsolutePath(configuredUserConfigDir)) {
        autostartPaths.append(QDir::cleanPath(configuredUserConfigDir + "/autostart"));
    } else {
        autostartPaths.append(QDir::cleanPath(defaultUserConfigDir + "/autostart"));
    }
    // Get system config dir
    QString defaultSystemConfigDir("/etc/xdg");
    QString configuredSystemConfigDirsVar = QProcessEnvironment::systemEnvironment().value("XDG_CONFIG_DIRS");
    QStringList configuredSystemConfigDirs = configuredUserConfigDir.split(":", Qt::SkipEmptyParts);
    foreach (const QString &configuredSystemConfigDir, configuredSystemConfigDirs) {
        if (!QDir::isAbsolutePath(configuredSystemConfigDir)) {
            configuredSystemConfigDirs.removeAll(configuredSystemConfigDir);
        }
    }
    if (configuredSystemConfigDirs.isEmpty()) {
        autostartPaths.append(QDir::cleanPath(defaultSystemConfigDir + "/autostart"));
    } else {
        foreach (const QString &configuredSystemConfigDir, configuredSystemConfigDirs) {
            autostartPaths.append(QDir::cleanPath(configuredSystemConfigDir + "/autostart"));
        }
    }
    // Traverse directories, get autostart apps
    foreach (const QString &autostartPath, autostartPaths) {
        QDir autostartDir(autostartPath);
        if (autostartDir.exists()) {
            autostartDir.setNameFilters({"*.desktop"});
            QFileInfoList fileInfoList = autostartDir.entryInfoList(QDir::Files);
            foreach (const QFileInfo &fileInfo, fileInfoList) {
                bool addFlag = false;
                QSettings desktopFile(fileInfo.absoluteFilePath(), QSettings::IniFormat);
                desktopFile.beginGroup(MAIN_SECTION);
                bool hidden = desktopFile.value(KEY_HIDDEN).toBool();
                if (hidden) {
                    continue;
                }
                QString desktopEnv = QProcessEnvironment::systemEnvironment().value("XDG_CURRENT_DESKTOP");
                QStringList currentDesktops = desktopEnv.split(":", Qt::SkipEmptyParts);
                QStringList onlyShowIn = desktopFile.value(KEY_ONLY_SHOW_IN).toStringList();
                QStringList notShowIn = desktopFile.value(KEY_NOT_SHOW_IN).toStringList();
                if (!onlyShowIn.isEmpty()) {
                    foreach (const QString &currentDesktop, currentDesktops) {
                        if (onlyShowIn.contains(currentDesktop)) {
                            addFlag = true;
                            break;
                        }
                    }
                } else {
                    addFlag = true;
                    if (!notShowIn.isEmpty()) {
                        foreach (const QString &currentDesktop, currentDesktops) {
                            if (notShowIn.contains(currentDesktop)) {
                                addFlag = false;
                                break;
                            }
                        }
                    }
                }
                foreach (const QString &app, autostartApps) {
                    QFileInfo appFile(app);
                    if (appFile.fileName() == fileInfo.fileName()) {
                        addFlag = false;
                    }
                }
                if (addFlag) {
                    autostartApps.append(fileInfo.absoluteFilePath());
                }
                desktopFile.endGroup();
            }
        }
    }
    return autostartApps;
}

bool DLoginSession::isAutostart(const QString &fileName)
{
    Q_UNUSED(fileName);
    return false;
}

bool DLoginSession::removeAutostart(const QString &fileName)
{
    Q_UNUSED(fileName)
    return false;
}
bool DLoginSession::enableAutostartWatch()
{
    return false;
}

DLOGIN_END_NAMESPACE

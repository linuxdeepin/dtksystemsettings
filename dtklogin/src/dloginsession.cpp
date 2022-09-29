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
#include <qfilesystemwatcher.h>

#include "login1sessioninterface.h"
#include "startmanagerinterface.h"
#include "sessionmanagerinterface.h"
#include "dloginutils.h"
DLOGIN_BEGIN_NAMESPACE

DLoginSession::DLoginSession(const QString &path, QObject *parent)
    : QObject(parent)
    , d_ptr(new DLoginSessionPrivate(this))
{
#if defined(USE_FAKE_INTERFACE)  // for unit test
    const QString &Service = QStringLiteral("org.freedesktop.fakelogin1");
    QDBusConnection connection = QDBusConnection::sessionBus();
#else
    const QString &Service = QStringLiteral("org.freedesktop.login1");
    QDBusConnection connection = QDBusConnection::systemBus();
#endif

    const QString &StartManagerService = QStringLiteral("com.deepin.SessionManager");
    const QString &StartManagerPath = QStringLiteral("/com/deepin/StartManager");

    const QString &SessionManagerService = StartManagerService;
    const QString &SessionManagerPath = QStringLiteral("/com/deepin/SessionManager");

    Q_D(DLoginSession);
    DBusSeatPath::registerMetaType();
    DBusUserPath::registerMetaType();
    d->m_inter = new Login1SessionInterface(Service, path, connection, this);
    connect(d->m_sessionManagerInter, &SessionManagerInterface::LockedChanged, this, &DLoginSession::lockedChanged);
    d->m_startManagerInter =
        new StartManagerInterface(StartManagerService, StartManagerPath, QDBusConnection::sessionBus(), this);
    d->m_sessionManagerInter =
        new SessionManagerInterface(SessionManagerService, SessionManagerPath, QDBusConnection::sessionBus(), this);
    d->m_fileWatcher = new QFileSystemWatcher(this);
    if (!d->enableAutostartWatch()) {
        qWarning() << "Enable autostart watch failed.";
    }
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

bool DLoginSession::locked() const
{
    Q_D(const DLoginSession);
    return d->m_sessionManagerInter->Locked();
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

void DLoginSession::kill(const QString &who, const qint32 signalNumber)
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
void DLoginSession::setIdleHint(const bool idle)
{
    Q_D(DLoginSession);
    QDBusPendingReply<> reply = d->m_inter->setIdleHint(idle);
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}
void DLoginSession::setLocked(const bool locked)
{
    Q_D(DLoginSession);
    QDBusPendingReply<> reply = d->m_sessionManagerInter->SetLocked(locked);
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

void DLoginSession::terminate()
{
    Q_D(DLoginSession);
    QDBusPendingReply<> reply = d->m_inter->terminate();
    reply.waitForFinished();
    if (!reply.isValid()) {
        qWarning() << reply.error().message();
    }
}

static QString getUserAutostartDir()
{
    QString defaultUserConfigDir;
    QString homeDir = QProcessEnvironment::systemEnvironment().value("HOME");
    if (!homeDir.isEmpty()) {
        defaultUserConfigDir = homeDir + "/.config";
    }
    QString configuredUserConfigDir = QProcessEnvironment::systemEnvironment().value("XDG_CONFIG_HOME");
    if (!configuredUserConfigDir.isEmpty() && !QDir::isAbsolutePath(configuredUserConfigDir)) {
        return QDir::cleanPath(configuredUserConfigDir + "/autostart");
    } else {
        return QDir::cleanPath(defaultUserConfigDir + "/autostart");
    }
}

static QStringList getSystemAutostartDirs()
{
    QStringList autostartDirs;
    QString defaultSystemConfigDir("/etc/xdg");
    QString configuredSystemConfigDirsVar = QProcessEnvironment::systemEnvironment().value("XDG_CONFIG_DIRS");
    QStringList configuredSystemConfigDirs = configuredSystemConfigDirsVar.split(":");
    foreach (const QString &configuredSystemConfigDir, configuredSystemConfigDirs) {
        if (!QDir::isAbsolutePath(configuredSystemConfigDir)) {
            configuredSystemConfigDirs.removeAll(configuredSystemConfigDir);
        }
    }
    if (configuredSystemConfigDirs.isEmpty()) {
        autostartDirs.append(QDir::cleanPath(defaultSystemConfigDir + "/autostart"));
    } else {
        foreach (const QString &configuredSystemConfigDir, configuredSystemConfigDirs) {
            autostartDirs.append(QDir::cleanPath(configuredSystemConfigDir + "/autostart"));
        }
    }
    return autostartDirs;
}

static QStringList getAutostartDirs()
{
    QStringList result;
    result << getUserAutostartDir();
    result += getSystemAutostartDirs();
    return result;
}

static bool judgeAutostart(const QString &fullPath)
{
    const QString &MainSection = QStringLiteral("Desktop Entry");
    const QString &KeyHidden = QStringLiteral("Hidden");
    const QString &KeyOnlyShowIn = QStringLiteral("OnlyShowIn");
    const QString &KeyNotShowIn = QStringLiteral("NotShowIn");
    QFileInfo fileInfo(fullPath);
    if (!fileInfo.exists()) {
        return false;
    }
    QSettings desktopFile(fileInfo.absoluteFilePath(), QSettings::IniFormat);
    desktopFile.beginGroup(MainSection);
    bool hidden = desktopFile.value(KeyHidden).toBool();
    if (hidden) {
        return false;
    }
    QString desktopEnv = QProcessEnvironment::systemEnvironment().value("XDG_CURRENT_DESKTOP");
    QStringList currentDesktops = desktopEnv.split(":");
    QStringList onlyShowIn = desktopFile.value(KeyOnlyShowIn).toStringList();
    QStringList notShowIn = desktopFile.value(KeyNotShowIn).toStringList();
    if (!onlyShowIn.isEmpty()) {
        foreach (const QString &currentDesktop, currentDesktops) {
            if (onlyShowIn.contains(currentDesktop)) {
                return true;
            }
        }
        return false;
    } else {
        if (!notShowIn.isEmpty()) {
            foreach (const QString &currentDesktop, currentDesktops) {
                if (notShowIn.contains(currentDesktop)) {
                    return false;
                }
            }
        }
        return true;
    }
}

static QStringList getAutostartApps(const QString &dir)
{
    QStringList autostartApps;
    QDir autostartDir(dir);
    if (autostartDir.exists()) {
        autostartDir.setNameFilters({"*.desktop"});
        QFileInfoList fileInfos = autostartDir.entryInfoList(QDir::Files);
        foreach (const auto &fileInfo, fileInfos) {
            if (judgeAutostart(fileInfo.canonicalFilePath())) {
                autostartApps.append(fileInfo.canonicalFilePath());
            }
        }
    }
    return autostartApps;
}

QStringList DLoginSession::autostartList()
{
    QStringList autostartApps;
    QStringList autostartPaths = getAutostartDirs();
    foreach (const auto &autostartPath, autostartPaths) {
        auto apps = getAutostartApps(autostartPath);
        if (autostartApps.isEmpty()) {
            autostartApps += apps;
        } else {
            foreach (const QString &app, apps) {
                if (!autostartApps.contains(app)) {
                    autostartApps.append(app);
                }
            }
        }
    }
    return autostartApps;
}

bool DLoginSession::isAutostart(const QString &fileName)
{
    if (QDir::isAbsolutePath(fileName)) {
        return judgeAutostart(fileName);
    } else {
        if (fileName.contains("/")) {
            return false;
        } else {
            QStringList autostartDirs = getAutostartDirs();
            QString file = fileName;
            if (!file.endsWith("*.desktop")) {
                file += ".desktop";
            }
            foreach (QString autostartDir, autostartDirs) {
                if (judgeAutostart(QDir::cleanPath(autostartDir + "/" + file))) {
                    return true;
                }
            }
            return false;
        }
    }
}

bool DLoginSession::removeAutostart(const QString &fileName)
{
    Q_D(const DLoginSession);
    if (isAutostart(fileName)) {
        auto reply = d->m_startManagerInter->removeAutostart(fileName);
        reply.waitForFinished();
        if (!reply.isValid()) {
            qWarning() << reply.error().message();
            return false;
        } else {
            return reply.value();
        }
    } else {
        return false;
    }
}

bool DLoginSessionPrivate::enableAutostartWatch()
{
    Q_Q(DLoginSession);
    QStringList autostartDirs = getAutostartDirs();
    auto result = m_fileWatcher->addPaths(autostartDirs);
    // For desktop file handler
    connect(m_fileWatcher, &QFileSystemWatcher::directoryChanged, this, [=](const QString &path) {
        QStringList autostartApps = q->autostartList();
        QStringList fileUnderPath;
        foreach (const QString &autostartApp, autostartApps) {
            if (autostartApp.startsWith(path)) {
                fileUnderPath.append(autostartApp);
            }
        }
        QStringList newAutostartApps = getAutostartApps(path);
        foreach (const QString &app, newAutostartApps) {
            if (!fileUnderPath.contains(app)) {
                emit q->autostartAdded(app);
            } else {
                fileUnderPath.removeAll(app);
            }
        }
        foreach (const QString &app, fileUnderPath) {
            // removed
            emit q->autostartRemoved(app);
        }
    });
    // for directory itself to be removed.
    connect(m_fileWatcher, &QFileSystemWatcher::fileChanged, this, [=](const QString &path) {
        QStringList autostartApps = q->autostartList();
        foreach (const QString &autostartApp, autostartApps) {
            if (autostartApp.startsWith(path)) {
                emit q->autostartRemoved(autostartApp);
            }
        }
    });
    return result.size() == autostartDirs.size();
}

bool DLoginSession::addAutostart(const QString &fileName)
{
    Q_D(const DLoginSession);
    if (!isAutostart(fileName)) {
        auto reply = d->m_startManagerInter->addAutostart(fileName);
        reply.waitForFinished();
        if (!reply.isValid()) {
            qWarning() << reply.error().message();
            return false;
        } else {
            return reply.value();
        }
    }
    return false;
}

DLOGIN_END_NAMESPACE

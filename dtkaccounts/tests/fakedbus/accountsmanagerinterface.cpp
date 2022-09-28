#include "accountsmanagerinterface.h"
#include <QDebug>
#include <QDBusError>
#include <QDBusConnection>

FakeAccountsManagerInterface::FakeAccountsManagerInterface(QObject *parent)
    : QObject(parent)
{
    registerService();
}

FakeAccountsManagerInterface::~FakeAccountsManagerInterface()
{
    unregisterService();
}

void FakeAccountsManagerInterface::registerService()
{
    const QString &ddeService = QLatin1String("com.deepin.daemon.FakeAccounts");
    const QString &ddePath = QLatin1String("/com/deepin/daemon/FakeAccounts");
    QDBusConnection bus = QDBusConnection::sessionBus();
    if (!bus.registerService(ddeService)) {
        QString errorMsg = bus.lastError().message();
        if (errorMsg.isEmpty())
            errorMsg = "maybe it's running";
        qWarning() << QString("Can't register the %1 service, %2.").arg(ddeService).arg(errorMsg);
    }
    if (!bus.registerObject(ddePath, this, QDBusConnection::ExportScriptableContents)) {
        qWarning() << QString("Can't register %1 the D-Bus object.").arg(ddePath);
    }

    const QString &freedesktopService = QLatin1String("org.freedesktop.FakeAccounts");
    const QString &freedesktopPath = QLatin1String("/org/freedesktop/FakeAccounts");
    if (!bus.registerService(freedesktopService)) {
        QString errorMsg = bus.lastError().message();
        if (errorMsg.isEmpty())
            errorMsg = "maybe it's running";
        qWarning() << QString("Can't register the %1 service, %2.").arg(freedesktopService).arg(errorMsg);
    }
    if (!bus.registerObject(freedesktopPath, this, QDBusConnection::ExportScriptableContents)) {
        qWarning() << QString("Can't register %1 the D-Bus object.").arg(freedesktopPath);
    }
}

void FakeAccountsManagerInterface::unregisterService()
{
    QDBusConnection bus = QDBusConnection::sessionBus();
    bus.unregisterObject("/com/deepin/daemon/FakeAccounts");
    bus.unregisterService("com.deepin.daemon.FakeAccounts");

    bus.unregisterObject("/org/freedesktop/FakeAccounts");
    bus.unregisterService("org.freedesktop.FakeAccounts");
}

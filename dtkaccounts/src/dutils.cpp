// SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dutils.h"
#include <QDir>
#include "dglobalconfig.h"

DACCOUNTS_BEGIN_NAMESPACE

QString Dutils::getUserConfigValue(const QByteArray &username, keyType key)
{
    QString value;
    QFileInfo configpath(UserConfigDir + username);
    if (!configpath.exists() or !configpath.isFile()) {
        return value;
    }
    QFile config(configpath.absoluteFilePath());
    if (!config.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return value;
    }

    QString valueline;
    QTextStream stream(&config);
    const auto &keystr = getUserConfigKey(key);
    while (!stream.atEnd()) {
        stream.readLineInto(&valueline);
        const auto &splitline = valueline.split("=");
        if (splitline.size() != 2) {
            continue;
        }
        if (splitline[0] == keystr) {
            value = splitline[1];
            break;
        }
    }
    config.close();
    return value;
}

QString Dutils::getUserConfigKey(keyType key)
{
    switch (key) {
        case keyType::IconFile:
            return "Icon";
        case keyType::LayoutList:
            return "HistoryLayout";
        case keyType::Layout:
            return "Layout";
        case keyType::Locale:
            return "Locale";
        case keyType::UUID:
            return "UUID";
        default:
            break;
    }
    return "";
}

qint64 Dutils::setUserConfigValue(const QByteArray &username, keyType key, const QByteArray &value)
{
    QDir configDir;
    if (!configDir.exists(UserConfigDir)) {
        if (!configDir.mkpath(UserConfigDir))
            return 0;
    } else {
        QFileInfo info(UserConfigDir);
        if (!info.isDir())
            return 0;
    }
    QFileInfo configFileInfo(UserConfigDir + username);
    if (configFileInfo.exists() and !configFileInfo.isFile()) {
        return 0;
    }
    QFile configFile(configFileInfo.absoluteFilePath());
    if (!configFile.open(QIODevice::ReadWrite | QIODevice::Text)) {
        return 0;
    }
    QTextStream stream(&configFile);
    QString line;
    const auto &strkey = getUserConfigKey(key);
    while (!stream.atEnd()) {
        stream.readLineInto(&line);
        const auto &splitline = line.split("=");
        if (splitline.size() != 2) {
            continue;
        }
        if (splitline[0] == strkey) {
            if (splitline[1] == value) {
                configFile.close();
                return 0;
            }
        } else {
            break;
        }
    }
    if (!configFile.seek(-line.size())) {
        return 0;
    }
    if (configFile.write(QByteArray(line.size(), ' ')) != line.size()) {}
    QString newline = strkey + "=" + value;
    return configFile.write(newline.toUtf8());
}

DACCOUNTS_END_NAMESPACE

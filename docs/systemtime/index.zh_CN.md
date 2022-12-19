@page dtksystemtime dtksystemtime


## 项目介绍

`dtksystemtime` 是对于 `deepin/UOS` 系统上关于时间同步相关接口的封装

## 项目结构

对外暴露出 `dsystemtime.h` 这个头文件

## 如何使用项目

如果要使用此项目，可以阅读相关文档再参照以下示例进行调用

## 使用示例

可参考以下demo：
```cpp
#include "dsystemtime.h"
#include <QCoreApplication>
#include <iostream>
#include <qdebug.h>
#include <qobject.h>
#include <qeventloop.h>
DSYSTEMTIME_USE_NAMESPACE
int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    DSystemTime systemTime;
    qDebug() << systemTime.serverName();
    qDebug() << systemTime.fallbackNTPServers()[1];
    qDebug() << systemTime.systemNTPServers().isEmpty();
    qDebug() << systemTime.canNTP();
    qDebug() << systemTime.localRTC();
    qDebug() << systemTime.NTP();
    qDebug() << systemTime.NTPSynchronized();
    qDebug() << systemTime.timezone();
    qDebug() << systemTime.RTCTimeUSec();
    qDebug() << systemTime.timeDate();
    qDebug() << systemTime.fallbackNTPServers();
    qDebug() << systemTime.linkNTPServers();
    qDebug() << systemTime.systemNTPServers();
    qDebug() << systemTime.frequency();
    qDebug() << systemTime.serverName();
    systemTime.setTimezone("Asia/Yangon", 1);
}

```
@defgroup dtksystemtime
@brief dtk时间同步管理模块

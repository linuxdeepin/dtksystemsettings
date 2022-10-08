@~chinese

# 项目介绍

dtkpower是对于deepin/UOS系统上的upowerdbus接口和dde-daemon接口的封装，其目的是在于方便第三方开发者轻松且快速的调用接口进行开发。

## 项目结构

对外暴露出 `dkbdbacklight.h` `dpowerdevice.h` `dpowermanager.h`如果需要对键盘背光和电源信息获取，需要使用dpowermanager进行管理。见下方示例

# 如何使用项目

如果要使用此项目，可以阅读相关文档再参照以下示例进行调用

## dkbdbacklight使用示例

```c++
#include "dpowermanager.h"//为了创建manager对象需要调用此头文件
#include "dkbdbacklight.h" //为了管理键盘背光需要调用此头文件
#include <QCoreApplication>
#include <qdebug.h>

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    Dtk::Power::DPowerManager manager; //创建manager对象
    auto kb = manager.kbdBacklight();//使用manager对象创建键盘对象并获取
    qDebug() << kb->brightness();//调用对应方法，获取当前键盘灯亮度
    qDebug() << "*************************************************";
    kb->setBrightness(1);//调整键盘灯亮度
    return 0;
}
```

## dpowerdevice使用示例

和上方的使用方法类似

```cpp
#include "dpowermanager.h"
#include "dpowerdevice.h"
#include <QCoreApplication>
#include <qdebug.h>

int main(int argc, char **argv)
{
    QCoreApplication a(argc, argv);
    Dtk::Power::DPowerManager manager; //创建manager对象
    auto device = manager.displayDevice(); //由manager对象创建device对象
    qDebug() << device->energyFullDesign();
    return 0;
}
```

但是和上面的不同的是，manager提供了几种不同的方法创建device对象，分别为 `displayDevice` `findDeviceByName` 如果需要对比其用法，详见doxygen文档

## dpowersettings使用指南

dpowersetting是对于电脑的电源进行相关设置，这些设置是（目前）依赖于dde-daemon实现的，所以在不存在dde-daemon的电脑上是无法进行调用。这个的调用方法就很简单，只需要直接创建dpowersettings对象即可。

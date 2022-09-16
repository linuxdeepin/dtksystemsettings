# dtk
------------
基于Qt的开发模板库。

## 特性
1. 使用`cmake`进行项目管理。
2. 支持编译为`debian`包。

## 使用方式
1. 克隆本仓库；
2. 配置项目名称：
```shell
bash config.sh -n <name>
```
3. 修改其他配置文件, 例如：README.md

## 项目目录规范
 **目录**           | **描述**
------------------|---------------------------------------------------------
 .github/         | github相关文件，一般用来存储工作流
 .reuse/          | license声明文件，项目中应使用reuse工具进行license声明
 .gitignore       | git过滤列表，用来过滤不需要推送到仓库中的文件
 .clang-format    | 格式化声明文件，使用该文件进行格式化代码，以保持格式统一性
 README.md        | 项目概述文档
 LICENSE          | 许可协议文件，该文件给github这种仓库使用，项目应使用reuse工具，但协议必须统一，一般为LGPL-v3
 CMakeLists.txt   | 项目文件可放置在最外层
 [debian/]        | debian打包所需文件
 docs/            | 存放文档相关内容，目前作为doxygen生成文档目录
 include/         | 公共头文件目录，所有需要开放的头文件均应放置在此目录
 LINCENSES/       | 许可协议目录，存放该项目所有的许可协议
 misc/            | 存放项目独立的资源或配置文件，如.service .conf .in等
 src/             | 存放源码文件，如 .h .cpp
 [src/3rdparty/]  | 存放第三方库或组件。**请注意，如果仓库内包含对应项目，请使用仓库内的版本，不允许另行提供版本包含至项目内**
 [qml/]           | 专门存放qml源码文件，如 .qml
 [translations/ ] | 存放本地化相关文件，如 .ts
 [tests/]         | 单元测试相关代码存放目录
 [tools/]         | 小工具存放目录
 [examples/]      | 示例存放目录

## 风格指南
本风格指南遵循[deepin开源风格指南](https://github.com/linuxdeepin/deepin-styleguide/releases)，在其基础上进行细化拆分，形成适用于开发库的风格指南。

### 基本约定
1. 开发库必须基于`Qt`，可以依赖`dtkcore`，但不允许依赖`dtkgui`与`dtkwidget`，以最小化依赖为原则，若无需依赖`dtkcore`，则不应依赖`dtkcore`。
2. 尽量使用前置声明，此处与[deepin开源风格指南](https://github.com/linuxdeepin/deepin-styleguide/releases)不同，作为开发库，尽量使头文件的依赖最小化。

### 命名约定

#### 通用规则
1. 尽可能使用描述性的命名，尽可能使用全单词组合的命名，务必不要使用缩写或简写。

#### 项目命名
项目名应以`dtk`三个字母开头，并且全字母小写，不允许有任何连接符号，如：`dtkpower`, `dtkpowermanager`。

#### 文件命名
1. 头文件与源文件需使单词全小写，并且以`d`开头，如：`dpower.h`，`dpowermanager.h`，必要时，可使用加下划线组合的方式（一般指`private`类），如：`dpowermanager_p.h`。
2. 配置文件应使用项目名+后缀名进行命名，如：`dtkpower.conf` 或者 `dtkpowermanager.conf`

#### 命名空间与类
命名空间需有两层：<br>
顶级命名空间统一为`Dtk`，二级命名空间为项目命名空间，如：`Dtk::Power` 或`Dtk::PowerManager`。<br>
类命名需以`D`为首字母，如：`DPowerManager`,`DPowerManager`。

## doxygen 与 reuse
1. 项目需使用`doxygen`编写文档，尽可能多的编写示例，示例可写在`docs/*.md`，注释可写在`docs/*.dox`中。
2. 项目使用`SPDX`规范开源协议，请使用`reuse`工具进行检查，参考[这里](https://spdx.org/licenses/)。

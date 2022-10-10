# Deepin Tool Kit System Settings
------------
基于Qt风格的Deepin系统设置开发库。

## 依赖

### 编译依赖

* Qt >= 5.11
* cmake >= 3.13
* doxygen

## 安装

### 从源代码构建

```bash
git clone https://github.com/linuxdeepin/dtksystemsettings.git
cd dtksystemsettings
cmake -B build -DCMAKE_INSTALL_PREFIX=/usr
cmake --build build
```

### 安装

```bash
sudo cmake --build build --target install
```

## 帮助

任何使用问题都可以通过以下方式寻求帮助:

* [Gitter](https://gitter.im/orgs/linuxdeepin/rooms)
* [IRC channel](https://webchat.freenode.net/?channels=deepin)
* [Forum](https://bbs.deepin.org)
* [WiKi](https://wiki.deepin.org/)

## 参与贡献

我们鼓励您报告问题并作出更改

* [开发者代码贡献指南](https://github.com/linuxdeepin/developer-center/wiki/Contribution-Guidelines-for-Developers)

## 协议

DTK工具包遵循协议 [LGPL-3.0-or-later](LICENSE).


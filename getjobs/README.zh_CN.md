## 项目名称

getjobs是对cups的cupsGetJobs接口的封装。用于查询用户打印作业任务信息。

### 编译依赖

项目编译时所依赖的软件包: cmake,gcc,g++,libcups-dev

```bash
sudo apt install cmake libcups-dev
```

## 安装

### 构建过程

此步骤默认在项目目录下进行：

```bash
sudo apt install cmake libcups-dev
cmake -B build
cmake --build build/
cd build
sudo make install
```

## 帮助

- [官方论坛](https://bbs.deepin.org/)
- [开发者中心](https://github.com/linuxdeepin/developer-center)
- [Wiki](https://wiki.deepin.org/)

## 贡献指南

我们鼓励您报告问题并做出更改

- [开发者代码贡献指南](https://github.com/linuxdeepin/developer-center/wiki/Contribution-Guidelines-for-Developers)

## 开源许可证

本项目采用[LGPL-3.0-or-later](../LICENSE)授权。

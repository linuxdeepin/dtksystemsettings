## 项目名称

dtklogin1是对systemd-logind的DBus接口进行封装。用于观察和管理用户 login 以及 seat 的状态。

### 运行依赖

`systemd: >=241.36-1`  
本项目测试环境：`systemd 241.36-1`和`systemd 250.2.2-4`

### 编译依赖

项目编译时所依赖的软件包: qtbase5-dev,doxygen,cmake,qttools5-dev
```bash
sudo apt install qtbase5-dev qttools5-dev doxygen cmake 
```
## 安装

### 构建过程

此步骤默认在项目目录下进行：
```bash
sudo apt install qtbase5-dev qttools5-dev doxygen cmake 
cmake -B build
cmake --build build/
cd build
sudo make install
```
注意：打包时依赖编译生成的doxygen文档，所以不要在cmake阶段手动关闭文档编译
## 文档

暂时为空

## 帮助

- [官方论坛](https://bbs.deepin.org/) 
- [开发者中心](https://github.com/linuxdeepin/developer-center) 
- [Wiki](https://wiki.deepin.org/)
（按照项目实际情况放帮助链接）

## 贡献指南

我们鼓励您报告问题并做出更改

- [开发者代码贡献指南](https://github.com/linuxdeepin/developer-center/wiki/Contribution-Guidelines-for-Developers) 
（按照项目实际情况放贡献指南链接）

## 开源许可证

许可证说明，建议使用SPDX规范描述许可证。例如：
[项目名称] 在 [GPL-3.0-or-later]下发布。
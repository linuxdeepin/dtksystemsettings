@~chinese

## dtklogin1

dtklogin1是对systemd-logind的DBus接口进行封装。用于观察和管理用户 login 以及 seat 的状态。

### DLogin1Manager

管理器对象，对 org.freedesktop.login1.Manager 接口的封装。

### DLogin1Seat

Seat对象，对 org.freedesktop.login1.Seat 接口的封装。

### DLogin1Session

会话对象，对 org.freedesktop.login1.Session 接口的封装。

### DLogin1User

用户对象，对 org.freedesktop.login1.User 接口的封装。

## 配置管理
登录管理的配置文件存在于下列文件中：
```shell
/etc/systemd/logind.conf
/etc/systemd/logind.conf.d/*.conf
/run/systemd/logind.conf.d/*.conf
/usr/lib/systemd/logind.conf.d/*.conf
```

### 说明

这些文件配置了 systemd 登录管理器的各种参数，有关语法的描述，请参见[systemd.syntax](https://www-freedesktop-org.translate.goog/software/systemd/man/systemd.syntax.html)。

### 配置目录和优先级

默认配置是在编译期间设置的，因此只有在需要改变这些默认配置时才需要配置。主配置文件/etc/systemd/logind.conf包含注释掉的条目，其显示的默认值作为管理员的指南。可以通过编辑此文件或创建插件来进行本地覆盖。建议使用插件进行本地配置，而不是修改主配置文件。<br>

除了主配置文件之外，还从/usr/lib/systemd/*.conf.d/、/usr/local/lib/systemd/*.conf.d/和/etc/systemd/*.conf.d/这些目录中读取插件. 这些插件具有更高的优先级并覆盖主配置文件。*.conf.d/子目录中的配置文件按其文件名字典顺序排序，而不管它们位于哪个子目录中。当多个文件指定相同的选项时，对于仅接受单个值的选项，文件中最后排序的条目优先；对于接受列表值的选项，条目在排序文件中出现时被收集。<br>

当包需要自定义配置时，可以在/usr/中安装插件。/etc/的文件是为本地管理员保留的，他们可以使用此逻辑覆盖供应商软件包安装的配置文件。必须使用插件来覆盖包插件，因为主配置文件的优先级较低。建议在这些子目录中的所有文件名前加上一个两位数字和一个破折号，以简化文件的排序。<br>

要禁用供应商提供的配置文件，推荐的方法是在/etc目录中放置一个/dev/null符号链接，其文件名与供应商配置文件相同。


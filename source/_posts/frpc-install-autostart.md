---
title:  Windows下Frpc安装与自启动
date: 2022-10-27 17:00:57
tags: [frpc]
categories:
- [frpc]
---

Windows下安装Frpc，并在windows的任务计划程序里设置Frpc自启动。

<!--more-->

1、新建一个start.bat文件

```shell
@echo off
:home
frpc -c frpc.ini
goto home
```

2、 打开`任务计划程序`（`cmd`->`taskschd.msc`）

3、安装步骤如下截图：


![](http://file.uuxia.top:88/showdoc/img/frpc/install/frpc-install-autostart-001.png)

----


![](http://file.uuxia.top:88/showdoc/img/frpc/install/frpc-install-autostart-002.png)

----


![](http://file.uuxia.top:88/showdoc/img/frpc/install/frpc-install-autostart-003.png)

----


![](http://file.uuxia.top:88/showdoc/img/frpc/install/frpc-install-autostart-004.png)
---
title: CentOS下shadowsocks-libev一键安装脚本
date: 2016-05-11 05:23:03
tags: [shadowsocks,翻墙]
categories: 翻墙
---
一键安装 libev 版的 shadowsocks 最新版本。该版本的特点是内存占用小（600k左右），低 CPU 消耗，甚至可以安装在基于 OpenWRT 的路由器上。
友情提示：如果你有问题，请先参考这篇《[Shadowsocks Troubleshooting](https://teddysun.com/399.html)》后再问。
<!--more-->
## 系统要求
系统支持：CentOS 32或64位
内存要求：≥128M
日期：2015年08月01日

## 本脚本适用环境：
系统支持：CentOS 32或64位
内存要求：≥128M
日期：2015年08月01日

## 关于本脚本：
一键安装 libev 版的 shadowsocks 最新版本。该版本的特点是内存占用小（600k左右），低 CPU 消耗，甚至可以安装在基于 OpenWRT 的路由器上。
友情提示：如果你有问题，请先参考这篇《[Shadowsocks Troubleshooting](https://teddysun.com/399.html)》后再问。


## 默认配置：
服务器端口：自己设定（如不设定，默认为 8989）
客户端端口：1080
密码：自己设定（如不设定，默认为teddysun.com）

## 客户端下载：
http://sourceforge.net/projects/shadowsocksgui/files/dist/

## 使用方法：
使用root用户登录，运行以下命令：

 1. 获取安装文件

```
wget --no-check-certificate https://raw.githubusercontent.com/teddysun/shadowsocks_install/master/shadowsocks-libev.sh
```

 2. 设置执行权限

```
chmod +x shadowsocks-libev.sh
```

 3. 按照命令

```
./shadowsocks-libev.sh 2>&1 | tee shadowsocks-libev.log
```
***安装完成后，脚本提示如下：***

```
Congratulations, shadowsocks-libev install completed!
Your Server IP:your_server_ip
Your Server Port:your_server_port
Your Password:your_password
Your Local IP:127.0.0.1
Your Local Port:1080
Your Encryption Method:aes-256-cfb

Welcome to visit:https://teddysun.com/357.html
Enjoy it!
```

 4. 安装完成后即已后台启动 shadowsocks ，运行

```
ps -ef | grep ss-server | grep -v ps | grep -v grep
```

 5. 使用命令

> 启动：/etc/init.d/shadowsocks start
停止：/etc/init.d/shadowsocks stop
重启：/etc/init.d/shadowsocks restart
查看状态：/etc/init.d/shadowsocks status

 6. 卸载方法

```
./shadowsocks-libev.sh uninstall
```

 7. 更多版本 shadowsocks 安装

[ShadowsocksR 版一键安装脚本（CentOS，Debian，Ubuntu）](https://shadowsocks.be/9.html)
[Shadowsocks Python 版一键安装脚本（CentOS，Debian，Ubuntu）](https://teddysun.com/342.html)
[Debian 下 Shadowsocks-libev 一键安装脚本](https://teddysun.com/358.html)
[Shadowsocks-go 一键安装脚本（CentOS，Debian，Ubuntu）](https://teddysun.com/392.html)

更新说明（2015 年 08 月 01 日）：
1、新增自定义服务器端口功能（如不设定，默认为 8989）；
更新说明（2015 年 04 月 30 日）：
1、本脚本会始终安装最新版的 Shadowsocks；
2、修改配置文件 /etc/shadowsocks-libev/config.json 同时启用 IPv4 与 IPv6 支持：
```
{
    "server":["[::0]","0.0.0.0"],
    "server_port":your_server_port,
    "local_address":"127.0.0.1",
    "local_port":1080,
    "password":"your_password",
    "timeout":600,
    "method":"aes-256-cfb"
}
```
3、Shadowsocks libev 版不能通过修改配置文件来多端口（只能开启多进程），如果你需要多端口请安装 Python 或 Go 版；

特别说明：
1、已安装旧版本的 shadowsocks 需要升级的话，需下载本脚本的最新版，运行卸载命令

>./shadowsocks-libev.sh uninstall 
然后，再次执行本脚本即可安装最新版。

参考链接：
https://github.com/madeye/shadowsocks-libev

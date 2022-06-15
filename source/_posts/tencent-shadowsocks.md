---
title: 腾讯云【centos7/8】一键安装 shadowsocks-libev
date: 2021-09-08 17:29:21
tags: [centos,腾讯云,shadowsocks]
categories:
- [shadowsocks]
- [VPN]
- [centos7]
---

CentOS 7/8 一键安装 shadowsocks-libev, 本教程仅提供学习，请勿用于商业用途和不法行为。

由于 Google BBR 需要内核版本 4.9 以上，如果安装时内核版本低于 4.9 建议先升级内核版本。

提示：CentOS 7 自带内核版本为 3.10，CentOS 8 自带内核版本为 4.18。

查看内核版本命令：
```bash
    uname -r
```

### 1、下载脚本
一键脚本已集成TCP优化、自动开启Google BBR（限 4.9 或更高版本内核）、自动安装 shadowsocks-libev
```bash
    wget https://down.24kplus.com/linux/shadowsocks/centos-shadowsocks-libev.sh
```
### 2、执行脚本进行安装
```bash
    chmod +x centos-shadowsocks-libev.sh && ./centos-shadowsocks-libev.sh
```
### 3、根据shell脚本提示输入相关信息
1、提示设置SS密码，输入自定义密码后按回车，也可以直接按回车使用默认密码
2、接下来选择SS要使用的服务器端口，输入自己喜欢的端口， 也可以直接按回车使用默认端口
3、 然后选择加密方式（仅保留相对安全的加密方式），如果选择chacha20的话，就输入对应序号3，按回车继续
4、 安装完成后，会有如下图安装成功的提示，记住各项信息，在客户端连接时需要用到

### 4、shadowsocks管理

```bash

#!/bin/bash

function status() {
    systemctl status shadowsocks-libev.service
}

function restart() {
    systemctl restart shadowsocks-libev.service
}

function log() {
    journalctl -f -u shadowsocks-libev.service
}

function m() {
    echo "1. 重启"
    echo "2. 重看状态"
    echo "3. 查看日志"
    echo "请输入编号:"
    read index

    case "$index" in
    [1]) (restart);;
    [2]) (status);;
    [3]) (log);;
    *) echo "exit" ;;
  esac
}

m



```

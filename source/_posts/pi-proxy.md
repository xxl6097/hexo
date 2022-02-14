---
title: 树莓派设置代理科学上网
date: 2022-02-14 11:54:21
tags: [raspberry,proxy,shadowsocks]
---

树莓派设置代理科学上网

<!--more-->

    设置步骤：
    1. cd /etc/apt/apt.conf.d
    2. sudo nano 10proxy
    3. Acquire::http::Proxy "http://192.168.31.53:1090";
    4. reboot

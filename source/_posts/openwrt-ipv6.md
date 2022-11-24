---
title: 家庭宽带开启IPV6
date: 2022-11-24 21:20:30
tags: [ipv6]
categories:
- [ipv6]
---


# 常见的运营商超级管理员账号
## 中国移动
- 移动光猫账号∶CMCCAdmin 密码∶ aDm8H%MdA 
- 华为的∶telecomadmin 密码∶ admintelecom
- 中国移动光纤宽带ip∶192.168.100.1的超级账号∶telecomadmin 密码∶nE7jA%5m
## 中国电信
- 账号∶telecomadmin 密码∶ nE7jA%5m
# 设置光猫为桥接模式
打开IPV4/IPV6，如果设置不了，请截图保存，然后删除，再新建，然后按原来的设置（如何连接光猫，可观看前面的视频）


![ipv6-1.png](ipv6-1.png)



# 然后设置软路由或者路由器
## 有软路由情况下：
- 网络——接口——IPV6 ULA清空
- 网络——接口——WAN口——使用内置IPV6管理取消勾选——Obtain IPv6-Address项目确保是自动状态
- 网络——接口——lan口——DHCP——IPV6设置——高级设置——取消勾选使用内置IPV6管理——取消勾选强制链路
- 通告的DNS服务器（添加谷歌IPV6DNS）：
    1. 2001:4860:4860::8888
    2. 2001:4860:4860::8844




![ipv6-2.png](ipv6-2.png)

混合模式会根据配置自动选择使用中继还是服务器模式。<font color='red'>（这里如果是主路由请选择服务器模式，旁路由选择中继模式）</font>
何时采用无状态、何时采用有状态，关键看应用场景。核心在于是否需要控制IP地址，比如保持IP不变，如果需要控制，就采用有状态;如果无需控制，就采用无状态。


- 在DHCP/DNS——高级设置——取消勾选禁止解析IPV6 DNS记录
- 设置完成后一定要重启软路由


- 只有路由器的情况下：直接打开路由器的IPV6即可，如果有多个路由器，每个路由器都要打开
- 设置完成后，电脑要禁用网络然后重新启用（目的是为了获取IPV6地址）
- 测试IPV6：
 https://ipv6-test.com/
 https://test-ipv6.com/index.html.zh_CN



 <video src="ipv6.mp4" style="width: 100%; height: 100%;" controls="controls"></video>
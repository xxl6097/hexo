---
title: L2TP/IPSec一键安装脚本
date: 2018-04-02 11:04:50
tags: [shadowsocks,科学上网]
categories:
- [VPN]
---
基于 OpenVZ 虚拟化技术的 VPS 需要开启TUN/TAP才能正常使用，购买 VPS 时请先咨询服务商是否支持开启 TUN/TAP。

OpenVZ 虚拟的 VPS 需要系统内核支持 IPSec 才行。也就是说，母服务器的内核如果不支持的话那就没办法，只能换 VPS。
因此，一般不建议在 OpenVZ 的 VPS 上安装本脚本。脚本如果检测到该 VPS 为 OpenVZ 架构，会出现警告提醒。

如何检测是否支持TUN模块？
执行命令：
cat /dev/net/tun
如果返回信息为：cat: /dev/net/tun: File descriptor in bad state 说明正常

如何检测是否支持ppp模块？
执行命令：
cat /dev/ppp
如果返回信息为：cat: /dev/ppp: No such device or address 说明正常
当然，脚本在安装时也会执行检查，如果不适用于安装，脚本会予以提示。

<!--more-->
## 本脚本适用环境：
系统支持：CentOS6+，Debian7+，Ubuntu12+
内存要求：≥128M
<font color='red'>更新日期：2017 年 05 月 28 日</font>

## 关于本脚本：
名词解释如下
L2TP（Layer 2 Tunneling Protocol）
IPSec（Internet Protocol Security）
IKEv2 (Internet Key Exchange v2)
能实现 IPsec 的目前总体上有 openswan，libreswan，strongswan 这3种。
libreswan 是基于 openswan 的 fork，所以现在各个发行版基本已经看不到 openswan 的身影了。
当然也有使用 strongswan 的。

之所以要更新 L2TP 一键安装脚本，是因为随着各个 Linux 发行版不断推陈出新，原有的脚本已经不适应现在的需求。
本脚本通过编译安装最新版 libreswan 来实现 IPSec（CentOS7 下则是全部 yum 安装），yum 或 apt-get 来安装 xl2tpd，再根据各个发行版的使用方法不同，部署防火墙规则。


<font color='red'>1. 使用方法：</font>
---
root 用户登录后，运行以下命令：
```
wget --no-check-certificate https://raw.githubusercontent.com/teddysun/across/master/l2tp.sh
chmod +x l2tp.sh
./l2tp.sh
```


执行后，会有如下交互界面

![img1](L2TP-IPSec_sh/l2tp_1.png)


Please input IP-Range:
(Default Range: 192.168.18):
输入本地IP段范围（本地电脑连接到VPS后给分配的一个本地IP地址），直接回车意味着输入默认值192.168.18

Please input PSK:
(Default PSK: teddysun.com):
PSK意为预共享密钥，即指定一个密钥将来在连接时需要用到，直接回车意味着输入默认值teddysun.com

Please input Username:
(Default Username: teddysun):
Username意为用户名，即第一个默认用户。直接回车意味着输入默认值teddysun

Please input teddysun’s password:
(Default Password: Q4SKhu2EXQ):
输入用户的密码，默认会随机生成一个10位包含大小写字母和数字的密码，当然你也可以指定密码。

ServerIP:your_server_main_IP
显示你的 VPS 的主 IP（如果是多 IP 的 VPS 也只显示一个）

Server Local IP:192.168.18.1
显示你的 VPS 的本地 IP（默认即可）

Client Remote IP Range:192.168.18.2-192.168.18.254
显示 IP 段范围

PSK:teddysun.com
显示 PSK

Press any key to start…or Press Ctrl+c to cancel
按下任意按键继续，如果想取消安装，请按Ctrl+c键

安装完成后，脚本会执行 ipsec verify 命令并提示如下：

```
If there are no [FAILED] above, then you can connect to your
L2TP VPN Server with the default Username/Password is below:

ServerIP:your_server_IP
PSK:your PSK
Username:your usename
Password:your password

If you want to modify user settings, please use command(s):
l2tp -a (Add a user)
l2tp -d (Delete a user)
l2tp -l (List all users)
l2tp -m (Modify a user password)
Welcome to visit https://teddysun.com/448.html
Enjoy it!

```

如果你要想对用户进行操作，可以使用如下命令：
l2tp -a 新增用户
l2tp -d 删除用户
l2tp -m 修改现有的用户的密码
l2tp -l 列出所有用户名和密码
l2tp -h 列出帮助信息

<font color='red'>2. 注意事项：</font>
---

1、错误809：
解决：路由线路上有防火墙没有关闭（pptp穿透防火墙的能力较差）
2、错误代码619
解决：
```
rm -r /dev/ppp
mknod /dev/ppp c 108 0 
然后重启VPS即可。
```
如果还未解决，尝试重启机器。

3、要根据ppp的版本来选择对应的pptpd版本。
ppp-2.4.4  对应   pptpd-1.3.4
ppp-2.4.5  对应   pptpd-1.4.0


<font color='red'>3. 其他事项：</font>
---
1、脚本在安装完成后，已自动启动进程，并加入了开机自启动。
2、脚本会改写 iptables 或 firewalld 的规则。
3、脚本安装时，会即时将安装日志写到 /root/l2tp.log 文件里，如果你安装失败，可以通过此文件来寻找错误信息。

<font color='red'>4. 使用命令：</font>
---
ipsec status （查看 IPSec 运行状态）
ipsec verify （查看 IPSec 检查结果）
/etc/init.d/ipsec start|stop|restart|status （CentOS6 下使用）
/etc/init.d/xl2tpd start|stop|restart （CentOS6 下使用）
systemctl start|stop|restart|status ipsec （CentOS7 下使用）
systemctl start|stop|restart xl2tpd （CentOS7 下使用）
service ipsec start|stop|restart|status （Debian/Ubuntu 下使用）
service xl2tpd start|stop|restart （Debian/Ubuntu 下使用）


<font color='red'>5. 更新日志</font>
---
2017 年 05 月 28 日：
升级 libreswan 到版本 3.20。
修正 libreswan 的若干配置问题。
修正 xl2tpd 的端口监听配置问题。
修正在 CentOS 6 对 libevent2 的依赖问题，改为 yum 安装 libevent2-devel。
测试表明，在内网环境的 VPS 里（如AWS， IDCF，GCE，腾讯云，阿里云等）也可以正常使用了。

<font color='red'>2017 年 02 月 25 日：</font>
升级 libreswan 到版本 3.19。

<font color='red'>2016 年 09 月 12 日：</font>
修正了在 CentOS 6 下 libevent2 依赖的问题；
新增了一个 -m 选项，用以修改现有用户的密码。

<font color='red'>2016 年 08 月 13 日：</font>
修正 Debian 8 下的 sd-daemon.h: No such file or directory 问题，是由于缺少依赖包 libsystemd-daemon-dev 导致的。

<font color='red'>2016 年 08 月 05 日：</font>
升级 libreswan 到版本 3.18。

<font color='red'>2016 年 06 月 10 日：</font>
脚本在安装完成后，新增了几个命令，便于操作用户
l2tp -a 新增用户
l2tp -d 删除用户
l2tp -l 列出所有用户
l2tp -h 列出帮助信息



参考链接：
[https://libreswan.org/wiki/3.14_on_Debian_Wheezy](https://libreswan.org/wiki/3.14_on_Debian_Wheezy)
[https://github.com/libreswan/libreswan](https://github.com/libreswan/libreswan)

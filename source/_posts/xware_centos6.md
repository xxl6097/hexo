---
title: 在CentOS6.6(32位）下配置迅雷远程成功
date: 2018-04-039 18:13:57
tags: [迅雷,centos]
categories: 迅雷
---
安装配置好了一台CentOS6.6的服务器，以下为本人配置迅雷远程的记录，供雷友们借鉴。
环境：CentOS 6.6 32位 mini安装 无图形界面
以下操作均以系统管理员 root进行
参照了以下几篇文章而配置成功的。
http://luyou.xunlei.com/forum.php?mod=viewthread&tid=1902  你若不想让迅雷以root权限运行，用我这个脚本吧
http://luyou.xunlei.com/forum.php?mod=viewthread&tid=3290&extra=page%3D1%26filter%3Dtypeid%26typeid%3D3 Linux(x86)下安装教程，以及init.d服务脚本，可自启动  （这篇启发最大）
<!--more-->

1. 建立用户 thunder （不用设置密码） 
```
adduser thunder
```
2. 在根目录下创建TDDOWNLOAD文件夹(~/TDDOWNLOAD)
3. 下载文件 Xware1.0.31_x86_32_glibc  链接：
[http://uuxia.cn:8123/thunder/Xware1.0.31_x86_32_glibc.zip](http://uuxia.cn:8123/thunder/Xware1.0.31_x86_32_glibc.zip)
4. 解压Xware1.0.31_x86_32_glibc.zip为Xware，使用WinSCP上传文件夹至/home/thunder下
5. 给文件夹设置权限
```
chown -R thunder:thunder /home/thunder/Xware
```
6. 给~/TDDOWNLOAD设置为thunder权限

```

chown thunder:thunder /TDDOWNLOAD

```

7.修改迅雷默认下载目录启动后自动挂载至/TDDOWNLOAD

```
vi /etc/fstab 添加以下一条
TDDOWNLOAD /TDDOWNLOAD   none  bind  0 0
```

设置完成后



8.重启服务器

``` 

reboot

```

9.重启后使用mount 查看挂载情况，如挂载成功如下：

```
/dev/sda3 on / type ext4 (rw)
proc on /proc type proc (rw)
sysfs on /sys type sysfs (rw)
devpts on /dev/pts type devpts (rw,gid=5,mode=620)
tmpfs on /dev/shm type tmpfs (rw,rootcontext="system_ubject_r:tmpfs_t:s0")
/dev/sda1 on /boot type ext4 (rw)
TDDOWNLOAD on /TDDOWNLOAD type none (rw,bind)
none on /proc/sys/fs/binfmt_misc type binfmt_misc (rw)
sunrpc on /var/lib/nfs/rpc_pipefs type rpc_pipefs (rw)

```


从上面看出，已经挂载成功。
如果是分区挂载的话，则显示：
/dev/sdb1 on /TDDOWNLOAD type ext4 (rw,bind)


10. 启动迅雷远程下载。

```
cd /home/thunder/Xware/
./portal

```

记住最后的那个六位的码，然后使用浏览器登陆 [http://yuancheng.xunlei.com](http://yuancheng.xunlei.com) 输入六位的的字符进行绑定设备。

11. 如果绑定成功后，再次运行portal 的话会显示 绑定的用户名。
端口默认为9000

12. 配置为开机自动启动portal
在开机配置文件中增加以下行，如下：
    vi /etc/rc.d/rc.local
    /home/thunder/Xware/portal

文件内容如下：

```
#!/bin/sh
#
# This script will be executed *after* all the other init scripts.
# You can put your own initialization stuff in here if you don't
# want to do the full Sys V style init stuff.

/home/thunder/Xware/portal

ouch /var/lock/subsys/local

```


至此服务器重启后迅雷远程下载自动启动。

本人亲自配置成功。

希望能通过此平台与广大雷友们分享共成长。

后来对别的服务器重新配置过，也重新整理了一下。对于上面提到的建立thunder用户，其实非必需的，因为运行远程迅雷时是以root用户运行的。



## 遇到的问题

### 问题1：
在执行最后一步portal时，可能会产生各种各样的bug
bug1：-bash: ./portal: /lib/ld-linux.so.2: bad ELF interpreter: No such file or directory
原因是在64位系统装安装32位程序
解决办法：
    ```yum install glibc.i686```

### 问题2：
bug2：/home/Eli/xunlei/portal: error while loading shared libraries: libz.so.1: cannot open shared object file: No such file or directory

问题原因在于在64位系统中使用32位的库

解决办法：`yum -y install libz.so.1 --setopt=protected_multilib=false`

### 问题3：
bug3：home/xunlei目录下明明有portal等文件，但是就是提示说目录下没这文件

原因可能是解压过程中出错文件损坏，或者没有给予home/xunlei目录最高权限就解压文件

解决办法：先给予home/xunlei目录最高权限，然后再次解压文件


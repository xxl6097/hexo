---
title: 搬瓦工（bandwagon）搭建VPN
date: 2016-05-09 05:59:13
tags: [vpn,shadowsocks]
categories: 
- [VPN]
---
最近注册了一个搬瓦工，开始只为了翻墙，方便查资料和上网。后来发现了搬瓦工功能还比较强大，一年19美元10G流量（搬瓦工：[https://bandwagonhost.com/](https://bandwagonhost.com/)），我目前配合了shadowsocks使用，ios用的surge，by the way，surge相当的强大，搬瓦工还可以搭件个人网站。关于搬瓦工的注册，在这里就不再阐述了，很简单，百度google都有，好了，下面开工，搭建VPN吧。
<!--more-->


最近注册了一个搬瓦工，开始只为了翻墙，方便查资料和上网。后来发现了搬瓦工功能还比较强大，一年19美元10G流量（搬瓦工：[https://bandwagonhost.com/](https://bandwagonhost.com/)），我目前配合了shadowsocks使用，ios用的surge，by the way，surge相当的强大，搬瓦工还可以搭件个人网站。关于搬瓦工的注册，在这里就不再阐述了，很简单，百度google都有，好了，下面开工，搭建VPN吧。

安装服务（VPN-PPTP）
--------------
运行如下命令

```
wget http://www.5yun.org/Soft/linux/Openvz-vpn/openvps_vpn_centos-5-6.sh
chmod a+x openvps_vpn_centos-5-6.sh 
bash openvps_vpn_centos-5-6.sh

#如果以上地址不可用，可尝试以下命令，
#这个脚本只提供三个选项，一般选择1就可以自动完成全部过程
#去掉注释符号
#wget http://www.hi-vps.com/shell/vpn_centos6.sh
#chmod a+x vpn_centos6.sh
#bash vpn_centos6.sh
```
结果如下：
![这里写图片描述](http://img.blog.csdn.net/20160402163201595)

上边第一步是获取一个自动脚本，第二步是给它运行权限，第三步是运行。有时候会遇到第一步无法成功，这时候在本地先下载这个文件，再使用Putty或者SSH客户端上传到VPS也是可以的。 
执行以上命令后将会返回一个选择系统版本的提示信息，因为之前我们选择的是centos6 ，因此选择第2项，输入2，回车：

```
[root@localhost ~]# bash openvps_vpn_centos-5-6.sh
please select your operation system
which do you want to?input the number.
1. my system is centos5 32bit(only support 32bit)
2. my system is centos6 32bit or 64bit(they are support)
3. repaire VPN service
4. add VPN user
```

![这里写图片描述](http://img.blog.csdn.net/20160402163645159)

执行命令后将自动安装，成功后返回一下信息： 
VPN service is installed, your VPN username is vpn_name,VPN password is ** 
这句话提示成功创建了一个名为vpn_name的账户，密码为 **。

执行命令后报404错误，或者提示文件或目录不存在，是因为没能成功下载安装包。 
这里提供手动下载安装包的方法 
如果是centos6，执行以下命令：

```
wget http://linux.dell.com/dkms/permalink/dkms-2.0.17.5-1.noarch.rpm
wget https://acelnmp.googlecode.com/files/kernel_ppp_mppe-1.0.2-3dkms.noarch.rpm
wget https://qiaodahai.googlecode.com/files/pptpd-1.3.4-2.el6.i686.rpm
wget https://logdns.googlecode.com/files/ppp-2.4.5-17.0.rhel6.i686.rpm
```
如果是 centos5，则执行以下命令：

```
wget http://linux.dell.com/dkms/permalink/dkms-2.0.17.5-1.noarch.rpm
wget https://acelnmp.googlecode.com/files/kernel_ppp_mppe-1.0.2-3dkms.noarch.rpm
wget https://acelnmp.googlecode.com/files/pptpd-1.3.4-1.rhel5.1.i386.rpm
wget https://fastlnmp.googlecode.com/files/ppp-2.4.4-9.0.rhel5.i386.rpm
```

添加自己的VPN账号
----------
如何添加自己的vpn账户名？ 比如我想用 anonymous 这个帐号，密码设置为 abc@123 (注意，危险！仅作为演示用，千万别设置这样的密码！)

执行下面这句代码来添加vpn账户： 

```
bash openvps_vpn_centos-5-6.sh 
```
返回的信息选项中，选择第4项：4.add VPN user 
```
[root@localhost ~]# bash openvps_vpn_centos-5-6.sh
please select your operation system
which do you want to?input the number.
1. my system is centos5 32bit(only support 32bit)
2. my system is centos6 32bit or 64bit(they are support)
3. repaire VPN service
4. add VPN user

```
根据提示输入用户名，如 anonymous，再输入密码 即可完成vpn的架设了。 
使用时，在本地新建VPN连接，地址和端口填写VPS的地址和端口，用户名密码填写自己设置的VPN的用户名和密码，然后连接，就可以了。 
如有疑问，请留言讨论。

在Terminal里面添加VPN帐号：

```
vi /etc/ppp/chap-secrets
```
键盘选择插入键：Insert 进行编辑， 使用键盘上下左右将光标插入另一行按照以下格式输入
*vpn pptpd Xk0jk78f *
注释：vpn  用户名
Xk0jk78f   密码
pptpd 和 * 不变，字符中间必须用一个空格隔开。数字123，选用键盘字母键上方，不要用数字小键盘*
![这里写图片描述](http://img.blog.csdn.net/20160402170911906)
如上输入完成，按下键盘左上方ESC键盘，英文状态下输入红色字体  ：wq     即保存好了。
现在只要电脑设置好，就可以自由的畅享网络了。

reference
---------
[Centos6.X vpn pptp 搭建方法](http://www.jjhr.net/2013/12/centos6-x-vpn-pptp-build-method/) 
[搬瓦工vps vpn架设](http://www.phpsong.com/1.html)

[http://www.phpsong.com/1126.html](http://www.phpsong.com/1126.html)

[http://www.figotan.org/2016/05/04/cook-your-own-vpn/?ref=myread](http://www.figotan.org/2016/05/04/cook-your-own-vpn/?ref=myread)


Appendix
--------
最近妖风太盛，所以如果自己有能力的童鞋，请移步Github的这个项目MPTUN自己研究怎么搭建VPN吧，当然VPS还是必要的。 
单单这篇文章访问量超高，让我陷入了沉思…… 
补充一点东西：有能力的同学，可以研究一下ssh的端口流量转发，浏览器或网络连接的socks5代理，基本上可以解决VPN被封杀时候的情况。ssh的协议特征很明显，我觉得迟早还是会被解决，同学们如果不嫌麻烦，VPN还有几种通信协议，可以研究一下。希望不会被查水表吧，我也不喜欢喝茶。

如果只需要浏览器翻墙，而不需要全局翻墙，那么SSH代理配合SwitchyOmega插件使用chrome浏览器就可以做到。 
最近发现一个方便的工具，Chrome插件Secure Shell，在浏览器完成SSH代理。

---
title: OpenWrt开启i2c功能，并顺利编译风扇驱动
date: 2022-11-21 14:11:56
tags: [openwrt,i2c,pi]
categories:
- [openwrt]
- [i2c]
---

树莓派安装OpenWrt作为家庭主路由，并开启i2c编译风扇、led等驱动，cpu温度骤降！～～～

<!--more-->


### 1、编译风扇
/home/uuxia/openwrt/temp_control/WiringPi-master/wiringPi

```
/home/uuxia/openwrt/wrt/staging_dir/toolchain-aarch64_cortex-a72_gcc-8.4.0_musl/bin/aarch64-openwrt-linux-gcc \
-o feng feng.c ssd1306_i2c.c \
-I/home/uuxia/openwrt/temp_control/WiringPi-master/wiringPi \
-L/home/uuxia/openwrt/temp_control/WiringPi-master/wiringPi \
-lwiringPi
```

### 2、**Unable to open I2C device: No such file or directory** 问题解决

用lsmod命令可以看到i2c_bmc2708字样，但是没i2c_dev字样，那么还需要做如下处理
执行命令
`sudo nano /etc/modules`                # 使用nano打开文件
然后增加
i2c_dev
行，安Ctrl+X退出编辑，输入Y保存内容，然后重启即可。

### 3、在OpenWrt中开启树莓派I2C功能

##### 1、编辑 /boot/config.txt

```
dtparam=i2c_arm=on
dtparam=i2c0=on
dtparam=i2c1=on
dtparam=spi=on
dtparam=i2s=on
```

##### 2、通过opkg安装相关包

```
opkg install i2c-tools kmod-i2c-gpio kmod-i2c-algo-bit kmod-i2c-algo-pcf kmod-i2c-bcm2835 kmod-i2c-core kmod-i2c-gpio kmod-i2c-mux
```

##### 3、使用i2c命令行工具测试

```

#!/bin/bash
ls /dev/i2c*
i2cdetect -y 1
```
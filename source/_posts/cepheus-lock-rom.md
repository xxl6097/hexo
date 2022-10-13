---
title: 小米9刷 PixelExperience ROM教程
date: 2022-10-13 13:16:07
tags: [cepheus,PixelExperience,刷机,Recovery]
categories: 
- [PixelExperience]
- [小米9]
---

小米9刷入官方rom

<!--more-->

## 小米9解锁

1. 确保手机插入了一张SIM卡，并登陆小米账号，并断开Wi-Fi连接;
2. 开启`开发者调试模式`，`Settings` > `About Phone`， 连续点击 `MIUI Version` 5次；
3. 绑定设备到小米账号，`Settings` > `Additional settings` > `Developer options` > `Mi Unlock status`
4. 下载[小米解锁程序](http://file.uuxia.top:88/soft/mi9/miflash_unlock-en-6.5.224.28.zip)(仅支持windows)，[官方解锁网站；](http://www.miui.com/unlock/index.html)
5. 手动进入Bootloader模式（关机后，同时按住开机键和音量下键）；
6. 通过USB连接手机，点击 “解锁”按钮；
7. 遇到电脑识别不了手机，需要安装驱动，可以使用[小米刷机工具](https://xiaomirom.com/download-xiaomi-flash-tool-miflash/)自带驱动安装。


## 刷入 PixelExperience Recovery.

1. 下载[PixelExperience Recovery;](http://file.uuxia.top:88/soft/mi9/recovery_cepheus-12.1-20220611-0701-UNOFFICIAL.img)
2. 将小米9手机连接PC电脑，并运行一下指令进入bootloader模式：
```
adb reboot bootloader
```
3. 查看手机是否连接成功：
```
fastboot devices
```
4. 开始刷入`PixelExperience Recovery`
```
fastboot flash recovery recovery_cepheus-12.1-20220611-0701-UNOFFICIAL.img
```

## 开始 PixelExperience ROM 刷机


1. uuxia编译的[ROM包](http://file.uuxia.top:88/soft/mi9/PixelExperience_cepheus-12.1-20220611-0701-UNOFFICIAL.zip)下载
2. 按 `Volume Up` + `Power`;
3. 清空数据 `Format data / factory reset`;
4. `Apply Update` > `Apply from ADB`;
5. PC电脑端执行 `adb sideload PixelExperience_cepheus-12.1-20220611-0701-UNOFFICIAL.zip`


## [附小米9刷回官方ROM](https://wiki.pixelexperience.org/devices/cepheus/build/)


<video src="http://file.uuxia.top:88/movies/%E7%94%B5%E8%A7%86%E5%89%A7/%E5%87%A1%E4%BA%BA%E4%BF%AE%E4%BB%99%E4%BC%A0/%E5%87%A1%E4%BA%BA%E4%BF%AE%E4%BB%99%E4%BC%A0%E7%AC%AC%E4%B8%80%E8%BE%91%5B01-08%5D.mov" style="width: 100%; height: 100%;" controls="controls"></video>
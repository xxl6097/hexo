---
title: ADB保存Android日志
date: 2022-06-16 11:05:12
tags: [logcat,android,adb]
categories:
- [android]
- [logcat]
---

Macos、Windows、linux下如何使用adb保存android手机的日志

<!--more-->

## 一、MacOsX、Linux下使用adb保存Android日志

```bash
adb logcat -c && adb logcat -v time | grep "abss" > /Users/uuxia/Desktop/android.log
```


## 一、Windows下使用adb保存Android日志

```bash
adb logcat -c && adb logcat -v time | find "abss" > D:/android.log
```
---
title: 基于Linux(centos/ubuntu)搭建树莓派C/C++程序编译环境
date: 2022-06-15 18:01:41
tags: [linux,C/C++,树莓派]
categories:
- [C/C++]
- [树莓派]
---

记录在Linux系统下搭建树莓派C/C++程序环境搭建的过程。

<!--more-->

## 一、安装gcc/g++

```bash

yum install gcc-c++

```

## 二、 安装CMake

1. 下载文件到本地：
```bash
       wget https://github.com/Kitware/CMake/releases/download/v3.13.4/cmake-3.13.4.tar.gz
       tar -xzvf cmake-3.13.4.tar.gz
       cd cmake-3.13.4/
```
2. 逐个运行：
```bash
       ./bootstrap
       make
       sudo make install
```

## 三、下载交叉编译工具


https://developer.arm.com/downloads/-/gnu-a

```bash

wget https://armkeil.blob.core.windows.net/developer/Files/downloads/gnu-a/10.2-2020.11/binrel/gcc-arm-10.2-2020.11-x86_64-aarch64-none-linux-gnu.tar.xz

```
解压：xz -d gcc-arm-10.2-2020.11-x86_64-aarch64-none-linux-gnu.tar.xz
解压：tar -xf gcc-arm-10.2-2020.11-x86_64-aarch64-none-linux-gnu.tar.xz

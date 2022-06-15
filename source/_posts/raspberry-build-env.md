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
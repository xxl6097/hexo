---
title: Centos后台运行jar
date: 2018-04-05 16:24:57
tags: [Java,Jar]
categories: 
- [Centos]
---
jar后台运行
<!--more-->
# jar后台运行

    nohup java -jar xx.jar >/dev/null  &

>此处的“>/dev/null”作用是将终端输出信息输出到空洞中，即不保存输出信息，若要查看输出信息需指定输出到那个文件，例如“>/xxx/yyy.out”

# 关闭后台进程
先查看后台进程pid

    ps -aux

记住进程pid，然后kill命令关闭

    kill [pid]

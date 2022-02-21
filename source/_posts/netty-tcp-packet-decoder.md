---
title: netty粘包断包处理
date: 2022-02-18 13:22:58
tags: [netty,tcp,server]
categories: 
- [netty]
---

基于Netty的TCP Server，处理二进制数据断包和粘包，以及tcp发送字符串的截取处理！

<!--more-->


## 一、5A协议在Netty中处理断包粘包


       长度[2] 1  1    设备编码[8]       Mac地址[6]    帧序号[4] 保留[8]          命令字[2] Body                                                             CRC2[2]
    5A 0042   40 00   00000199000B0301 8C18D9FFEB9D 00000046 0000000000000000 0104     0000000001000301000000000000000000000003000200000000000000000000 050B

    说明：
       1.长度len=0042(HEX)=66=(34+32)不包含5A;
       2.空包长度total=35；
       3.5A这一个子节不算在len区；


    int maxFrameLength = 65535;   （len是两个子节，所以最大长度是无符号两个子节的最大值）
    int lengthFieldOffset = 1;    （len的索引下表是1，下表从0开始）
    int lengthFieldLength = 2;    （len是两个子节）
    int lengthAdjustment = -2;    （netty从len后面开始读取，5A这一子节又不再len中，len又是2子节，所以这里是-2）
    int initialBytesToStrip = 0;  （这个0表示完整的协议内容，如果不想要5A，那么这里就是1）

    socketChannel.pipeline().addLast(new LengthFieldBasedFrameDecoder(maxFrameLength, lengthFieldOffset, lengthFieldLength, lengthAdjustment, initialBytesToStrip));

    测试断包发送：
    完整数据包：5A0042400000000199000B03018C18D9FFEB9D00000046000000000000000001040000000001000301000000000000000000000003000200000000000000000000050B
    第一次发送（一包半）：5A0042400000000199000B03018C18D9FFEB9D00000046000000000000000001040000000001000301000000000000000000000003000200000000000000000000050B 5A0042400000000199000B03018C18D9FFEB9D0000004600000000000000000104
    第二次发送（补齐后半包）：0000000001000301000000000000000000000003000200000000000000000000050B



## 二、水机    
    
    起始码  功能码 数据长度      Body                         CRC
    A2      10     0E        0102030405060708091011121314 050B


    说明：
    1.len=0E(HEX)=14,这里的len仅仅是Body的长度，不包含head的长度;


    lengthFieldOffset=2
    lengthFieldLength=1
    lengthAdjustment=2   
    initialBytesToStrip=0
    maxFrameLength=255



https://blog.csdn.net/lzwglory/article/details/80242209

https://blog.csdn.net/zougen/article/details/79037675

https://www.jianshu.com/p/a0a51fd79f62

https://www.cnblogs.com/workharder/p/12325908.html

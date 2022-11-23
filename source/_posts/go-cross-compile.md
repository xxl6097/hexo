---
title: GoLang 全平台编译
date: 2022-11-23 19:16:38
tags: [go,cross]
categories:
- [go]
---
Golang的全平台编译简直太爽了，真的太适合我了，平时编译一些不同设备的跨平台程序，真的是爽的不行。
拥有一台windows电脑就能开发出在Linux、Windows、Mac上面直接运行的程序。
<!--more-->


## 一、三个平台编译示例:
1、Mac下编译Linux, Windows平台的64位可执行程序：
```
$ CGO_ENABLED=0 GOOS=linux GOARCH=amd64 go build test.go
$ CGO_ENABLED=0 GOOS=windows GOARCH=amd64 go build test.go

```

2、 Linux下编译Mac, Windows平台的64位可执行程序：
```
$ CGO_ENABLED=0 GOOS=darwin GOARCH=amd64 go build test.go
$ CGO_ENABLED=0 GOOS=windows GOARCH=amd64 go build test.go

```

3、 Windows下编译Mac, Linux平台的64位可执行程序：
```
$ set CGO_ENABLED=0 set GOOS=darwin3 set GOARCH=amd64 go build test.go
$ set CGO_ENABLED=0 set GOOS=linux s GOARCH=amd64 go build test.go

```


当然如果编译过其他平台后，程序 go run main.go 执行会有一些问题:
报错如下:

```
F:\github\syncFiles\goApi\ipDemo>go run main.go
warning: GOPATH set to GOROOT (C:\Program Files\Go) has no effect
exec: "C:\\Users\\dell\\AppData\\Local\\Temp\\go-build2490838331\\b001\\exe\\main": file does not exist

```

这里只需要:

```
F:\github\syncFiles\goApi\ipDemo>set GOOS=windows

F:\github\syncFiles\goApi\ipDemo>go run main.go
warning: GOPATH set to GOROOT (C:\Program Files\Go) has no effect
192.168.5.107

```

main.go 是一个显示本机IP地址的程序。
这样做就没有问题了。

## 二、包括三个设置的参数:

- GOARCH：编译目标平台的硬件体系架构（amd64, 386, arm, ppc64等）。
- GOOS：编译目标平台上的操作系统（darwin, freebsd, linux, windows）。
- CGO_ENABLED：代表是否开启CGO，1表示开启，0表示禁用。由于CGO不能支持交叉编译，所以需要禁用。
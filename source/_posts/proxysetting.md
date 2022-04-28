---
title: terminal代理设置
date: 2022-04-28 22:54:33
tags: [ubuntu,proxy,git]
---

ubuntu、linux下terminal终端http和git代理设置

<!--more-->


#http代理设置(只在当前 shell 生效)
	export http_proxy=http://127.0.0.1:1080
	export https_proxy=http://127.0.0.1:1080
	export http_proxy=socks5://127.0.0.1:1087
	export https_proxy=socks5://127.0.0.1:1087

#http代理查看
	export http_proxy
	export https_proxy

#git代理设置
	git config --global http.proxy http://127.0.0.1:1080
	git config --global https.proxy http://127.0.0.1:1080

#查看http、https代理配置情况
	git config --global --get http.proxy
	git config --global --get https.proxy
	
#取消http、https代理配置
	git config --global --unset http.proxy
	git config --global --unset https.proxy
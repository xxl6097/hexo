---
title: git使用SSH进行无密码身份验证
date: 2022-02-11 17:23:20
tags: [git,github,gitee,coding]
categories:
- [Git, SSH]
---

git使用SSH进行无密码身份验证

<!--more-->

## 一、生成key

#### ed25519方式

```

ssh-keygen -t ed25519 -C "uuxia@uuxia.cn"
cat ~/.ssh/id_ed25519.pub

```

#### rsa方式
```
ssh-keygen -t rsa -C "uuxia@uuxia.com"
cat ~/.ssh/id_rsa.pub
```
---

## 二、测试


#### 测试github服务器
```
ssh -T git@github.com
```
#### 测试gitee服务器
```
ssh -T git@gitee.com
```
#### 测试coding服务
```
ssh -T git@e.coding.net
```

## 注意
---
在个人设置里面添加前，必须删除单独项目中添加的ssh key！！！

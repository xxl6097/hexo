---
title: SSH公钥免密登录
date: 2022-07-01 20:23:16
tags: [ssh,pubkey,shell]
password: 6cf9d8a4f434262f7e0836d877608d48a6dcca8b681cf23ae1c3b93557fc3411
categories:
- [ssh]
---

ssh连接使用公钥免密登录

<!--more-->

## 1. 制作公钥

#### ed25519方式
```bash
[root@VM-4-12-centos ~]# ssh-keygen -t ed25519 -C "HongKong@uuxia.cn"
Generating public/private ed25519 key pair.
Enter file in which to save the key (/root/.ssh/id_ed25519): 
/root/.ssh/id_ed25519 already exists.
Overwrite (y/n)? y
Enter passphrase (empty for no passphrase): 
Enter same passphrase again: 
Your identification has been saved in /root/.ssh/id_ed25519.
Your public key has been saved in /root/.ssh/id_ed25519.pub.
The key fingerprint is:
SHA256:WOaLsCD+PTOpbs3DvEdlA/k4lepSQ/uXklT5Cv4sb/E HongKong@uuxia.cn
The key's randomart image is:
+--[ED25519 256]--+
|        . . .    |
|       + o o     |
|      . X . .    |
|       % B   .   |
|. . . + S + o    |
|.. . + + * =     |
| .  * = . = o    |
|  ...@ . . + E   |
|  o+.oB   +.     |
+----[SHA256]-----+
```

#### rsa方式
```bash
ssh-keygen -t rsa -C "HongKong@uuxia.cn"
```


## 2. 安装公钥

```bash
[root@VM-4-12-centos ~]# cat ~/.ssh/id_ed25519.pub > ~/.ssh/authorized_keys
[root@VM-4-12-centos ~]# chmod 600 ~/.ssh/authorized_keys 
[root@VM-4-12-centos ~]# chmod 700 ~/.ssh/
```

## 3. 修改SSH配置

```bash
sudo nano /etc/ssh/sshd_config


PubkeyAuthentication yes

禁用ssh密码登录,可以不禁用
PasswordAuthentication no

sudo service sshd restart

```



```id_ed25519_hetpi4s
-----BEGIN OPENSSH PRIVATE KEY-----
b3BlbnNzaC1rZXktdjEAAAAABG5vbmUAAAAEbm9uZQAAAAAAAAABAAAAMwAAAAtzc2gtZW
QyNTUxOQAAACBFXprOqGFkUMg3AJAlTEQQVCVbt+BTxDB1C5A+JMXQsgAAAJiA8NffgPDX
3wAAAAtzc2gtZWQyNTUxOQAAACBFXprOqGFkUMg3AJAlTEQQVCVbt+BTxDB1C5A+JMXQsg
AAAECeFUhNhKurVgYkIXYKhwZ4Y09bXs8Sln0WlTtY7+JYdUVems6oYWRQyDcAkCVMRBBU
JVu34FPEMHULkD4kxdCyAAAAD2hldHBpNEB1dXhpYS5jbgECAwQFBg==
-----END OPENSSH PRIVATE KEY-----

```



```id_ed25519_homepi4s
-----BEGIN OPENSSH PRIVATE KEY-----
b3BlbnNzaC1rZXktdjEAAAAABG5vbmUAAAAEbm9uZQAAAAAAAAABAAAAMwAAAAtzc2gtZW
QyNTUxOQAAACBi+wXwnH9fh0lebu9JzDG2hBoWEjueIGbnt+hvjnat3AAAAJi4l4PmuJeD
5gAAAAtzc2gtZWQyNTUxOQAAACBi+wXwnH9fh0lebu9JzDG2hBoWEjueIGbnt+hvjnat3A
AAAEBCPjafbpoYxx0iWNFSL0A3CHtSgmmDV/+Y46SAclqv9GL7BfCcf1+HSV5u70nMMbaE
GhYSO54gZue36G+Odq3cAAAAEWhvbWVwaTRzQHV1eGlhLmNuAQIDBA==
-----END OPENSSH PRIVATE KEY-----
```

```uuxia.cn
-----BEGIN OPENSSH PRIVATE KEY-----
b3BlbnNzaC1rZXktdjEAAAAABG5vbmUAAAAEbm9uZQAAAAAAAAABAAAAMwAAAAtzc2gtZW
QyNTUxOQAAACA8+LMAD9OzOFpu48I7k/J8PFQSPUxAl0V3O7yK0me2tAAAAJiG5lCFhuZQ
hQAAAAtzc2gtZWQyNTUxOQAAACA8+LMAD9OzOFpu48I7k/J8PFQSPUxAl0V3O7yK0me2tA
AAAEAADBNvYO8owdd0Nd1Jj1h5zB8SjP8LWex7fBVnwMgA1Tz4swAP07M4Wm7jwjuT8nw8
VBI9TECXRXc7vIrSZ7a0AAAAEHRlbmNlbnRAdXV4aWEuY24BAgMEBQ==
-----END OPENSSH PRIVATE KEY-----
```

```HongKong
-----BEGIN OPENSSH PRIVATE KEY-----
b3BlbnNzaC1rZXktdjEAAAAABG5vbmUAAAAEbm9uZQAAAAAAAAABAAAAMwAAAAtzc2gtZW
QyNTUxOQAAACBYr18zgN38cTW9Mohlyui72GjQbVwuHCfcMGlyiWqJQwAAAJhTAryrUwK8
qwAAAAtzc2gtZWQyNTUxOQAAACBYr18zgN38cTW9Mohlyui72GjQbVwuHCfcMGlyiWqJQw
AAAEDDLLNd7gQEYDoWS5d9iCWL5nV/93X8aAB0JX73PJKwblivXzOA3fxxNb0yiGXK6LvY
aNBtXC4cJ9wwaXKJaolDAAAAEUhvbmdLb25nQHV1eGlhLmNuAQIDBA==
-----END OPENSSH PRIVATE KEY-----
```

[id_ed25519_hetpi4s](id_ed25519_hetpi4s "公司树莓派4B+")

[id_ed25519_homepi4s](id_ed25519_homepi4s "HOME树莓派4B+")

[uuxia.cn](id_ed25519_uuxia.cn "uuxia.cn")

[HongKong](id_ed25519_hk "HongKong")

光猫登陆：
192.168.3.1
root/adminHW

宽带账户:202107592177，密码:096016

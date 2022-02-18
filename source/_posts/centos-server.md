---
title: centos服务器程序安装指南
date: 2022-02-11 15:34:03
tags: [centos,hexo,java,frp,nginx,mysql,gradle]
categories: 服务器配置
---

主要记录我的centos服务器上的服务环境安装，frp、nginx配置、java程序、mysql安装、个人博客hexo。

<!--more-->

## 1. nginx配置

    安装
    yum install nginx

    配置代码

    nano /etc/nginx/nginx.conf

---


#### nginx.conf


```

user root;
worker_processes auto;
error_log /var/log/nginx/error.log;
pid /run/nginx.pid;


include /usr/share/nginx/modules/*.conf;

events {
worker_connections 1024;
}

http {
log_format  main  '$remote_addr - $remote_user [$time_local] "$request" '
'$status $body_bytes_sent "$http_referer" '
'"$http_user_agent" "$http_x_forwarded_for"';

    access_log  /var/log/nginx/access.log  main;

    sendfile            on;
    tcp_nopush          on;
    tcp_nodelay         on;
    keepalive_timeout   65;
    types_hash_max_size 2048;
    client_max_body_size 500m;
    include             /etc/nginx/mime.types;
    default_type        application/octet-stream;

    include /etc/nginx/conf.d/*.conf;



}

```

#### admin.conf

```
server {
        listen       80;
        server_name  admin.uuxia.cn;
        
        location / {
           index index.html index.htm;
           proxy_set_header Host $host;
           proxy_pass https://127.0.0.1:8082/;
           proxy_set_header Upgrade $http_upgrade;
           proxy_http_version 1.1;
           proxy_set_header Connection "upgrade";
           proxy_redirect https://127.0.0.1/admin https://127.0.0.1:8080/;
       }
       
}

```

#### file.conf

```
autoindex on;# 显示目录
autoindex_exact_size off;# 显示文件大小
autoindex_localtime on;# 显示文件时间
server {
        listen       80;
        server_name  file.uuxia.cn;

        charset gbk,utf-8;
        

        location / {
            root /home/;
            index  index.html index.htm;
            charset utf-8;
        }

 }
```


#### cloud.conf
    
```
server {
        listen       80 default_server;
        server_name  cloud.uuxia.cn;

        location / {
            proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
            proxy_set_header Host $http_host;
            proxy_redirect off;
            proxy_pass http://127.0.0.1:5212;

            # 如果您要使用本地存储策略，请将下一行注释符删除，并更改大小为理论最大文件尺寸
            # client_max_body_size 20000m;
        }
    }

```

#### java.conf

```


server {
        listen       80;
        #listen       [::]:80 default_server;
        server_name  uuxia.cn;
        #root         /usr/share/nginx/html;
        #charset gbk,utf-8;
#        charset utf-8;
        location ^~ /frp_server_web/{
            proxy_set_header X-Real-IP $remote_addr;
            proxy_set_header Host $http_host;
            proxy_pass http://127.0.0.1:9090;
        }

        location / {
            root /home/file/xxl6097.github.io;
            index index.html index.htm;
            charset utf-8;
        }
        location /file {
            alias /home/file;
            autoindex on;
            autoindex_exact_size off;
            autoindex_localtime on;
            charset utf-8;
        }

        location /websocket{
            proxy_pass https://127.0.0.1:8082;
            proxy_http_version 1.1;
            proxy_set_header Upgrade $http_upgrade;
            proxy_set_header Connection "upgrade";
            proxy_read_timeout 3600s;
        }
        location /admin/ {
           index index.html index.htm;
           proxy_set_header Host $host;
           proxy_pass https://127.0.0.1:8082/;
           proxy_set_header Upgrade $http_upgrade;
           proxy_http_version 1.1;
           proxy_set_header Connection "upgrade";
           proxy_redirect https://127.0.0.1/admin https://127.0.0.1:8080/;
       }
       

       location ~* ^(/v2|/webjars|/swagger-resources|/swagger-ui.html){
         proxy_set_header Host $host;
         proxy_set_header  X-Real-IP  $remote_addr;
           proxy_set_header X-Forwarded-For $remote_addr;
         #proxy_set_header Host $host:$server_port;
         proxy_set_header X-Forwarded-Proto $scheme;
         proxy_set_header X-Forwarded-Port $server_port;
         proxy_pass https://127.0.0.1:8082; # 后端服务地址
       }

       location /v1 {
         proxy_set_header Host $host;
         add_header 'Access-Control-Allow-Origin' '*';
         add_header 'Access-Control-Allow-Headers' 'X-Requested-With';
         add_header 'Access-Control-Allow-Methods' 'GET,POST,OPTIONS';
         proxy_pass https://127.0.0.1:8082;
        }

        error_page 404 /404.html;
            location = /40x.html {
        }

        error_page 500 502 503 504 /50x.html;
            location = /50x.html {
        }
    }

# Settings for a TLS enabled server.
#
    server {
        listen       443 ssl http2 default_server;
       # listen       [::]:443 ssl http2 default_server;
        server_name  uuxia.cn;
       # root         /usr/share/nginx/html;
        ssl_certificate "/etc/pki/nginx/server.crt";
        ssl_certificate_key "/etc/pki/nginx/private/server.key";
        ssl_session_cache shared:SSL:1m;
        ssl_session_timeout  10m;
        ssl_protocols TLSv1 TLSv1.1 TLSv1.2;
        ssl_ciphers ECDHE-RSA-AES128-GCM-SHA256:HIGH:!aNULL:!MD5:!RC4:!DHE;
        #ssl_ciphers PROFILE=SYSTEM;
        ssl_prefer_server_ciphers on;
#        charset gbk,utf-8;


        client_max_body_size 500m;    
        location / {
            root /home/file/xxl6097.github.io;
            index index.html index.htm;
            #proxy_pass https://127.0.0.1:8082/;
            #proxy_redirect https://127.0.0.1/admin https://127.0.0.1:8082/;
            charset utf-8;
        }
        location /file {
            alias /home/file;
            autoindex on;
            autoindex_exact_size off;
            autoindex_localtime on;
            charset utf-8;
        }

        location /v1 {
            proxy_set_header Host $host;
            add_header 'Access-Control-Allow-Origin' '*';
            add_header 'Access-Control-Allow-Headers' 'X-Requested-With';
            add_header 'Access-Control-Allow-Methods' 'GET,POST,OPTIONS';
            proxy_pass https://127.0.0.1:8082;
        }
        location /admin/ {
           index index.html index.htm;
           proxy_set_header Host $host;
           proxy_pass https://127.0.0.1:8082/;
           proxy_set_header Upgrade $http_upgrade;
           proxy_http_version 1.1;
           proxy_set_header Connection "upgrade";
           proxy_redirect https://127.0.0.1/admin https://127.0.0.1:8080/;
       }
       

       location ~* ^(/v2|/webjars|/swagger-resources|/swagger-ui.html){
         proxy_set_header Host $host;
         proxy_set_header  X-Real-IP  $remote_addr;
           proxy_set_header X-Forwarded-For $remote_addr;
         #proxy_set_header Host $host:$server_port;
         proxy_set_header X-Forwarded-Proto $scheme;
         proxy_set_header X-Forwarded-Port $server_port;
         proxy_pass https://127.0.0.1:8082; # 后端服务地址
       }

        location /websocket{
            proxy_pass https://127.0.0.1:8082;
            proxy_http_version 1.1;
            proxy_set_header Upgrade $http_upgrade;
            proxy_set_header Connection "upgrade";
            proxy_read_timeout 3600s;
        }

        error_page 404 /404.html;
            location = /40x.html {
        }
#
        error_page 500 502 503 504 /50x.html;
            location = /50x.html {
        }
    }


```


## 2. mysql安装配置

    1.下载MySQL
    Red Hat Enterprise Linux / Oracle Linux
    2. 选择 `Red Hat Enterprise Linux 8 / Oracle Linux 8 (x86, 64-bit), RPM Bundle
---
    安装
    wget https://cdn.mysql.com//Downloads/MySQL-8.0/mysql-8.0.28-1.el8.x86_64.rpm-bundle.tar
    tar -xvf mysql-8.0.28-1.el8.x86_64.rpm-bundle.tar 
    rpm -ivh mysql-community-common-8.0.28-1.el8.x86_64.rpm --nodeps --force
    rpm -ivh mysql-community-libs-8.0.28-1.el8.x86_64.rpm --nodeps --force
    rpm -ivh mysql-community-client-8.0.28-1.el8.x86_64.rpm --nodeps --force
    rpm -ivh mysql-community-server-8.0.28-1.el8.x86_64.rpm --nodeps --force
    通过 rpm -qa | grep mysql 命令查看 mysql 的安装包

---

    通过以下命令，完成对 mysql 数据库的初始化和相关配置

    mysqld --initialize;
    chown mysql:mysql /var/lib/mysql -R;
    systemctl start mysqld.service;
    systemctl enable mysqld;


通过 `cat /var/log/mysqld.log | grep password` 命令查看数据库的密码


通过 `mysql -uroot -p` 敲回车键进入数据库登陆界面

通过 `ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY 'Xxl2475431305.';` 命令来修改密码
`ALTER USER 'root'@'%' IDENTIFIED WITH mysql_native_password BY 'Xxl2475431305.';`
这下密码改成了 root


通过 exit; 命令退出 MySQL，然后通过新密码再次登陆

通过以下命令，进行远程访问的授权

    create user 'root'@'%' identified with mysql_native_password by 'root';
    
    grant all privileges on *.* to 'root'@'%' with grant option;
    
    flush privileges;



sqlyog链接时出现2058异常

`ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY 'password';`
其中password为自己修改的密码。然后SQLyog中重新连接，则可连接成功，OK。

如果报错：ERROR 1396 (HY000): Operation ALTER USER failed for ‘root’@'localhost’则使用下面命令：

`ALTER USER 'root'@'%' IDENTIFIED WITH mysql_native_password BY 'Xxl2475431305.';`


## 3. JDK安装配置


### 方式一（推荐）

    查询安装的jdk版本
    yum -y list java*
    安装jdk1.8
    yum install -y java-11-openjdk.x86_64


### 方式二
#### 下载

    https://www.oracle.com/java/technologies/downloads/#java8

    选择 `jdk-8u321-linux-x64.tar.gz`

    解压 `tar -zxvf jdk-8u321-linux-x64.tar.gz`

---

    修改环境变量 `nano /etc/profile`

    export JAVA_HOME=/usr/lib/jdk1.8.0_321
    export CLASSPATH=.:$JAVA_HOME/jre/lib/rt.jar:$JAVA_HOME/lib/dt.jar:$JAVA_HOME/lib/tools.jar
    export PATH=$PATH:$JAVA_HOME/bin

    source /etc/profile


## 4. gralde安装

    wget https://services.gradle.org/distributions/gradle-6.7-bin.zip

    unzip gradle-6.7-bin.zip
    
    nano ~/.bash_profile
    
    PATH=$PATH:/usr/lib/gradle-6.7/bin
    
    source ~/.bash_profile



## 5. 安装frps安装

服务端配置

    [common]
    bind_port = 8000
    token = xxxxxxxxx
    dashboard_port=8888
    dashboard_user = admin
    dashboard_pwd = admin
    vhost_http_port = 9090
    vhost_https_port = 9091
    subdomain_host = uuxia.cn


客户端配置

    [common]
    tls_enable = true
    admin_addr = 0.0.0.0
    admin_port = 7400
    admin_user = admin
    admin_pwd = admin
    token = xxxxxx
    #server_addr = 127.0.0.1
    server_addr = uuxia.cn
    server_port = 8000
    
    [公司-树莓派3B]
    type = tcp
    local_ip = 0.0.0.0
    local_port = 22
    remote_port = 2222
    
    [公司-FRP客户端管理页面]
    type = tcp
    local_ip = 0.0.0.0
    local_port = 7400
    remote_port = 7401
    
    [公司-win]
    type = tcp
    local_ip = 192.168.31.53
    local_port = 3389
    remote_port = 7001
    
    [公司-iMac-VNC]
    type = tcp
    local_ip = 192.168.31.92
    local_port = 5900
    remote_port = 7002
    
    [公司-iMac-SSH]
    type = tcp
    local_ip = 192.168.31.92
    local_port = 22
    remote_port = 7003


## 6. 安装Node.js

    1 下载

    官网地址：https://nodejs.org/en/download/
    wget https://nodejs.org/dist/v10.24.0/node-v10.24.0-linux-x64.tar.gz
---
    安装

    tar -xvf node-v10.24.0-linux-x64.tar.gz
    mv node-v10.24.0-linux-x64 /opt/Nodejs
    NODE_HOME=/opt/Nodejs
    export PATH=$NODE_HOME/bin:$PATH
    source /etc/profile

    npm install -g hexo-cli

    npm uninstall hexo-cli -g  推荐这个，成功卸载


## 7. 页脚备案代码


    <div style="color:#666;text-align:center;margin-top:-10px;padding-bottom:35px;">
        <p><a style="color:#666;" text-decoration:underline;" href="http://beian.miit.gov.cn/">工业和信息化部备案管理系统网站 粤ICP备2022014941号</a></p>
        <p>主办单位：<a style="color:#666;" text-decoration:underline;" target="_blank" href="http://uuxia.cn">悠悠科技</a></p>
        <p>Operated by Guangzhou ChoMeng Computer System Co., Ltd.</p>
    </div>

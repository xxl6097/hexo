---
title: Android孤儿进程防止清理
date: 2016-05-09 01:47:57
tags: [Android,Service]
categories: 
- [Android, Service]
---
孤儿进程:因为父进程先退出而导致一个子进程被init进程收养的进程为孤儿进程
<!--more-->
孤儿进程:因为父进程先退出而导致一个子进程被init进程收养的进程为孤儿进程。
---


因此，可以通过创建孤儿进程，改变native进程的父进程，达到防止系统清理。

关键代码实现:

```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
   pid_t child_pid;
   child_pid=fork();
   if(child_pid<0)
   {
     perror("fork error");
     exit(EXIT_FAILURE);
   }
   if(child_pid==0)//子进程处理 事务
   {
      while(1)
      {
         printf("hello world\n");
         sleep(1);
      }
      return 0;
   }else
   {
     printf("father bye byte\n");
     exit(EXIT_SUCCESS);
   }
}
```

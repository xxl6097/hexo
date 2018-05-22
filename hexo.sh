#!/bin/sh +x
git pull

echo "hexo running"

hexo clean

hexo g

hexo d

git push -u origin master

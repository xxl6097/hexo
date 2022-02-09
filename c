git pull 
echo "hexo running"
hexo clean
hexo g
hexo d
git add .
git commit -m "chg"
git push -u origin master

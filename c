function builds() {
  echo "git pull"
  git pull
  echo "hexo clean"
  hexo clean
  echo "hexo g"
  hexo g
  echo "hexo d"
  hexo d
  chmod +x gitcommit.sh
  echo "sh gitcommit.sh"
  ./gitcommit.sh

  echo "cp -r public/* ../xxl6097.github.io/"
  cp -r public/* ../xxl6097.github.io/
  echo "cp -r gitcommit.sh ../xxl6097.github.io/"
  cp -r gitcommit.sh ../xxl6097.github.io/

  echo "cp -r /root/wechat-cloud/we-api/src/main/resources/web ../xxl6097.github.io/"
  cp -r /root/wechat-cloud/we-api/src/main/resources/web ../xxl6097.github.io/

  echo "cd ../xxl6097.github.io/"
  cd ../xxl6097.github.io/

  chmod +x gitcommit.sh
  echo "./gitcommit.sh"
  ./gitcommit.sh
}


function forcepull() {
  echo "git fetch --all && git reset --hard origin/master && git pull"
  git fetch --all && git reset --hard origin/master && git pull
}


echo "输入编号选择"
echo "1. 编译"
echo "2. 更新代码"
echo "******Enter nothing to exit*****"
read num

case "$num" in
[1]) (builds) ;;
[2]) (forcepull) ;;
*) echo "nothing,exit" ;;
esac

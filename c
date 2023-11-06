function builds() {
  echo "开始拉去代码"
  git pull
  echo "hexo clean 清空"
  hexo clean
  echo "hexo g  生成"
  hexo g
  echo "hexo d  编译"
  hexo d
  chmod +x gitcommit.sh
  echo "sh gitcommit.sh 提交代码"
  ./gitcommit.sh

  #sudo rm -rf ../xxl6097.github.io/*
  echo "复制代码到 github cp -r public/* ../xxl6097.github.io/"
  cp -r public/* ../xxl6097.github.io/
  echo "复制脚本 cp -r gitcommit.sh ../xxl6097.github.io/"
  cp -r gitcommit.sh ../xxl6097.github.io/

  echo "复制二维码 cp -r /root/wechat-cloud/we-api/src/main/resources/web ../xxl6097.github.io/"
  cp -r /root/wechat-cloud/we-api/src/main/resources/admin ../xxl6097.github.io/

  echo "进入github目录 cd ../xxl6097.github.io/"
  cd ../xxl6097.github.io/

  chmod +x gitcommit.sh
  echo "运行脚步，提交代码./gitcommit.sh"
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

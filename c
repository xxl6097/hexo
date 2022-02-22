echo "git pull"
git pull
echo "hexo running"
hexo clean
hexo g
hexo d
chmod +x gitcommit.sh
./gitcommit.sh

cp -r public/* ../xxl6097.github.io/
cp -r gitcommit.sh ../xxl6097.github.io/

cd ../xxl6097.github.io/

chmod +x gitcommit.sh
./gitcommit.sh


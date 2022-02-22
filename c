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

echo "cd ../xxl6097.github.io/"
cd ../xxl6097.github.io/

chmod +x gitcommit.sh
echo "./gitcommit.sh"
./gitcommit.sh


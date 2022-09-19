current=`date "+%Y-%m-%d %H:%M:%S"`  
timeStamp=`date -d "$current" +%s` 
echo "commit time is $current"
git add . || exit -1
git commit -m "$current" || exit -1
git push || exit -1
echo "commit successed!"
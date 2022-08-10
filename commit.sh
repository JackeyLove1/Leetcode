current=`date "+%Y-%m-%d %H:%M:%S"`  
timeStamp=`date -d "$current" +%s` 
echo $current
git add .
git commit -m "$current"
git push
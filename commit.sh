current=`date "+%Y-%m-%d %H:%M:%S"`  
# timeStamp=`date -d "$current" +%s` 
echo "commit time is $current"
git add .
git commit -m "$current"
git push
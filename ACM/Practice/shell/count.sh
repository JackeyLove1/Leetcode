[ $# -lt 1 ] && echo "Input Parameter is Error" && exit -1
[ ! -f $1 ] && echo "$1 is not a file" && exit -1
file=$1
sed -e "s/[^a-zA-Z]/\n/g" $file | grep -v ^$ | sort | uniq -c
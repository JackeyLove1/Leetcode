[ $# -lt 1 ] && echo "input error" && exit -1
[ ! -d $1 ] && echo "$1 is not exists" && exit -1
dir=$1
find . -name "*.sh" | xargs -I {} cp {} $dir && echo "copy done"
len=$#
start=$1
end=$2
step=$3

if [ $len -eq 1 ] && [ $start -gt 0 ]; then
  for ((i = 1; i <= $start; i++)); do
    echo $i
  done
elif [ $len -eq 2 ] && [ $start -gt 0 ] && [ $end -gt $start ]; then
  for ((i = $start; i <= $end; i++)); do
    echo $i
  done
elif [ $len -eq 3 ] && [ $start -gt 0 ] && [ $end -gt $start ]; then
  for ((i = $start; i <= $end; i += $step)); do
    echo $i
  done
else
  echo "input parameter is error!"
fi

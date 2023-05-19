#!/bin/bash
a=0
while [ "$a" -lt 10 ];
do
    b="$a"
    while [ "$b" -ge 0 ];
    do
        echo -n "$b"
        b=`expr $b - 1`
    done
    echo
    a=`expr $a + 1`
done

a=10
while [ $a -gt 5 ]; do
      echo $a
      a=`expr $a - 1`
done

# Declare an associative array
declare -A my_map

# Add key-value pairs
my_map=( ["key1"]="value1" ["key2"]="value2" ["key3"]="value3" )

# Access a specific value
echo "Value of key1 is: ${my_map["key1"]}"   # Output: Value of key1 is: value1

# Iterate over keys and values
for key in "${!my_map[@]}"; do
  echo "Key: $key, Value: ${my_map[$key]}"
done

# Output:
# Key: key1, Value: value1
# Key: key2, Value: value2
# Key: key3, Value: value3

for var1 in 1 2 3;do
  for var2 in $(seq 1 5);do
    if [ ${var1} -eq 1  -a ${var2} -eq 3 ]; then
        echo "Yes"
      else
        echo "${var1} ${var2}"
    fi
    done
done

echo -e "Hello, World!\n"

DATE=`date`
echo "Current data: $DATE"

Hello(){
  echo "Hello, World! $1 $2"
}
Hello A B

echo `date`
echo `who`

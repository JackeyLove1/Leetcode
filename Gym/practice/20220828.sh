#!/bin/zsh

s="Hello,World!"
echo s is ${s}
echo length of s is ${#s}
echo substring of s is ${s:0:3}

echo "--\$*---"
for i in "$*"; do
  echo $i
done

echo "--\$@--"
for i in "$@"; do
  echo $i
done

my_array=(A B "C" D)

echo ${my_array[0]}
echo ${my_array[1]}
echo ${my_array[2]}
echo ${my_array[3]}

declare -A site
site['A']="jacky"
site['B']="fan"
echo ${site}

echo ${my_array[*]}
echo ${my_array[@]}

val=`expr 2 + 2`
echo ${val}
a=10
b=20
val=`expr $a + $b`
echo ${val}
val=`expr ${a} \* ${b}`
echo ${val}

if [ $a -eq $b ]
then
  echo "a == b"
else
  echo "a != b"
fi

a="hello"
b="world"
if [ $a = $b ]
then
  echo "a == b"
else
  echo "a != b"
fi

echo -e "OK! \n"
echo "return"
echo "Hello, World" > hello

printf "Hello, World\n"

num1=100
num2=200
if test $[num1] -eq $[num2]
then
  echo "num1 == num2"
else
  echo "num1 != num2"
fi
echo "Hello, World!" > hello
if test -e hello
then
  echo "Y"
else
  echo "N"
fi

a=10
b=20
if [ $a -eq $b ]
then
  echo "a == b"
elif [ $a -gt $b ]
then
  echo "a > b"
else
  echo "a < b"
fi

for loop in 1 2 3 4 5
do
  echo ${loop}
done

for loop in Hello World, Jaky!
do
  echo ${loop}
done

i=1
while (($i < 5))
do
  echo $i
  let "i++"
done

demofunc(){
  echo "Hello, Demo!"
}
demofunc

echo 'Hello' | grep -e Hello
echo #?
echo "Hello" >> hello
who > users
cat users

a=1
let "a=a+1"
echo ${a}



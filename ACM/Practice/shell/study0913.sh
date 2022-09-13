VAR=$(echo hello)
echo $VAR

Countries=('Ubuntu' 'Debian' 'CentOS', "openSUSE", "Linuxmi.com")
echo "${Countries[*]}"

for i in {1..3}; do
  echo $i
done

for ((i = 1; i <= 10; i += 3)); do
  echo $i
done

echo $VAR | wc -l

echo -n $VAR | grep -c ^

echo "Hello" >&2

test -f "file"

test 3 -lt 6 && echo "3 < 6"

[ 3 -lt 6 ] && echo "[3 < 6]"

test 3 -gt 6 && echo "3 > 6"

if [ 3 -ne 6 ]; then echo "3 != 6"; fi

C=0
while
  echo "while C is $C"
  [ $C -lt 10 ]
do
  ((C++)) # Increase C
  echo "After In Loop C is $C"
done

for i in *.sh; do
  echo $i
done

for file in $(ls "dofile"); do
  echo $file
done

{
  echo "Hello"
  echo "World"
  echo "!"
} > dofile/hello
par=(pwd)|echo ${par}
a=int(input())
b=int(input())
l=0
r=1
while(r**a<=b):  #打2个乘号就是乘方的意思
    l=r;r=r*2  #先获得l,r初值
while(l+1<r):  #以下都是二分,可以注意一下while和if的用法
    mid=(l+r)//2
    if (mid**a<=b):
        l=mid
    else:
        r=mid
if (l**a<=b):
    print(l)
else:
    print(r)
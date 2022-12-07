//T：当前剩余时间
//T_min：日落时分，因为乘法永远无法使得T变为0，所以需要一个极小的数来代替0
//r：时间流逝速率
//dE：高度差
//now：当前所处位置
//next：随机选取的位置
//H(a)：a处的高度
//ans：当前最优解
while(T>T_min)
{
    next=randow();//随机选取一个位置
    dE=H(now)-H(next);//求取高度差
    if(dE<0) now=next;//如果更高，直接前往
    else
    {
        if(exp(-dE/T)>randow(0,1)) now=next;
    }//否则看概率
    ans=max(ans,H(now));
    T*=r;//时间流逝
}
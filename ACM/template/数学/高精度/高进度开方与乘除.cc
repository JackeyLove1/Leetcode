//大数乘法
//大数比较 
//大数开根
#include<bits/stdc++.h> 
using namespace std;

const int Max=1100;
string s1,s2;     //n,m;
int len1,len2;    //记录开根号后大数的位数；

int sqrtA[1100],sqrtB[1100];
int a[1100];
int temp[1100],ans[1100];

int Compare(int a[],int b[],int len1,int len2) //大数比较大小 
{
    if(len1>len2) return 1;
    else if(len1<len2) return -1;
    for(int i=len1-1;i>=0;i--){
        if(a[i]>b[i]) return 1;
        else if(a[i]<b[i]) return -1;
    }
    return 0;
}

//计算sqrtA[]*sqrtB[],len1,len2分别为sqrtA,sqrtB的长度
//返回结果位数；
int Mul(int ans[],int A[],int B[],int len1,int len2)
{
    for(int i=0;i<=1000;i++) ans[i]=0;  //对于传址ans，用memset没法初始化；
    for(int i=0;i<len1;i++)
        for(int j=0;j<len2;j++)
            ans[i+j]+=A[i]*B[j];
    for(int i=0;i<len1+len2;i++){
        ans[i+1]+=ans[i]/10;
        ans[i]%=10;
    }
    int i;
    for(i=len1+len2;i>=0;i--)
        if(ans[i]) break;
    return i+1;
}

//将s开根号,保存在a中,并且返回开根号后a的位数；
int sqrtNum(int *A,string s)
{
    memset(A,0,sizeof(A));
    int len=s.size();
    int Len=len/2;
    if(len%2) Len+=1;
    memset(a,0,sizeof(a));
    for(int i=0,j=s.size()-1;i<s.size();i++,j--) //顺序翻转；
        a[j]=s[i]-'0';

    for(int i=Len-1;i>=0;i--){                //从最高位开始试；
        int flag;
        memset(temp,0,sizeof(temp));
        int lenMul=1;
        while((flag=Compare(temp,a,lenMul,len))==-1){
            A[i]++;
            lenMul=Mul(temp,A,A,Len,Len);
        }
        if(flag==0) break;
        else if(flag==1) A[i]--;
    }
    return Len;
}
int main()
{
    memset(sqrtA,0,sizeof(sqrtA));
    memset(sqrtB,0,sizeof(sqrtB));

    cin>>s1>>s2;

    len1=sqrtNum(sqrtA,s1);
    len2=sqrtNum(sqrtB,s2);

    int len=Mul(ans,sqrtA,sqrtB,len1,len2);

    for(int i=len-1;i>=0;i--) cout<<ans[i];
    cout<<endl;
    return 0;
}

/*
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

string stringMultiply(string str1,string str2) //字符串相乘
{
    int len1 = str1.length();
    int len2 = str2.length();
    int i,j,num[500]={0};  //num[]储存开方数，对于数据最大也只是10^1000，所以其开方数位数最多500位
    string ans = "";
    for(i=0;i<len1;i++)
    {
        for(j=0;j<len2;j++)
        {
            num[len1-i-1 + len2-j-1] += (str1[i]-'0')*(str2[j]-'0');
            //因为字符串的最低位是数的最高位
            //len1和len2位数相乘其结果是len1+len2-1到len1+len2位数之间，而num[]从0开始，所以最高位是len1+len2-2或len1+len2-1
        }
    }
    for(i=0;i<len1+len2;i++)
    {
        //之前只是每位相加，现在实现进位
        num[i+1] += num[i]/10;
        num[i] %= 10;
    }
    for(i=len1+len2-1;i>=0;i--)
    {
        if(num[i]!=0) break; //找到最高位
    }
    for(j=i;j>=0;j--) ans += (num[j]+'0');
    return ans;
}

int stringCompare(string str1,string str2,int x) //大数比较，str1后加x个0后与str2比
{
    int len1 = str1.length();
    int len2 = str2.length();
    if(len1+x<len2) return 0;
    if(len1+x>len2) return 1;
    for(int i=0;i<len1;i++)
    {
        if(str1[i]>str2[i]) return 1;
        if(str1[i]<str2[i]) return 0;
    }
    return 0;
}

string stringSqrt(string str)  //大数开方
{
    int len = str.length();
    string ans="";
    string tmp="";
    if(len&1)
    {
        for(int i=0;i<len/2+1;i++)
        {
            for(int j=0;j<10;j++)
            {
                tmp = ans;
                tmp += (j+'0');
                if(stringCompare(stringMultiply(tmp,tmp),str,2*(len/2-i))) //tmp后少了len/2-i个零，平方后少了2*（len/2-i）个零
                {
                    ans += (j-1+'0');
                    break;
                }
                if(j==9)
                {
                    ans += '9';
                    break;
                }
            }
        }
    }
    else
    {
        for(int i=0;i<len/2;i++)
        {
            for(int j=0;j<10;j++)
            {
                tmp = ans;
                tmp += (j+'0');
                if(stringCompare(stringMultiply(tmp,tmp),str,2*(len/2-i-1))) //tmp少了len/2-i-1个零，tmp平方后少了2*（len/2-i-1）个零
                {
                    ans += (j-1+'0');
                    break;
                }
                if(j==9)
                {
                    ans += '9';
                    break;
                }
            }
        }
    }
    return ans;
}

int main()
{
    string str1,str2;
    cin>>str1>>str2;
    cout<<stringMultiply(stringSqrt(str1),stringSqrt(str2))<<endl;
    return 0;
}
*/
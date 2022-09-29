#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int data[101][101];
int map[101][101];
int m,n;
int f(int i,int j)
{
   int max1,max2;
   int max_right=0,max_left=0,max_up=0,max_down=0;
    if (data[i][j]>0) 
	 return data[i][j];
	  
   if (j+1<=n&&map[i][j]>map[i][j+1])   
    max_right=f(i,j+1); //右边
    
   if (j-1>=1&&map[i][j]>map[i][j-1])
    max_left=f(i,j-1);//左边
    
    if (i+1<=m&&map[i][j]>map[i+1][j])
    max_up=f(i+1,j);//上面
    
    if (i-1>=1&&map[i][j]>map[i-1][j])
    max_down=f(i-1,j);//下面
    
    max1=max(max_right,max_left);
    max2=max(max_up,max_down);
    data[i][j]=max(max1,max2)+1;//4个方向上的最大值
    return data[i][j];
}
 
int main()
{
	
    memset(data,0,sizeof(data));
    int k,max_all;
    while(cin>>m>>n)
    {
      max_all=0;
      for(int i=1;i<=m;i++)
         for(int j=1;j<=n;j++)
             cin>>map[i][j];
             
      for(int i=1;i<=m;i++)
          for(int j=1;j<=n;j++)
             k=f(i,j);
             
        for(int i=1;i<=m;i++)
           for(int j=1;j<=n;j++)
           
         if (max_all<data[i][j]) 
		   max_all=data[i][j]; 
		              
       cout<<max_all<<endl;             
     }
     
    return 0;
 
}
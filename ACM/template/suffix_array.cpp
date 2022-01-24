#include <bits/stdc++.h>
using namespace std;

const int N=1000010;

int n,m;
char s[N];
int sa[N], x[N], y[N], c[N], rk[N], height[N];

void get_sa(){
    for(int i=1; i<=n; i++)
        x[i]=s[i], c[x[i]]++; //x[i]=j:第i个的排名是j, 排名可以空缺
                            //c[i]=j:排名i的有j个
    for(int i=2; i<=m; i++)
        c[i]+=c[i-1];  //累加后，c[i]=j:原始排名i的最终最后排名是j（j排名连续）
    for(int i=n; i; i--)
        sa[ c[x[i]]-- ]=i;  //第i个的原始排名是x[i]，原始排名x[i]的最终排名是c[x[i]]
                            //最终排名c[x[i]]的是第i个，--是为了处理并列的，
                            //从后开始，是为了保持并列的原始顺序
    for(int k=1; k<=n; k<<=1){
        int num=0;
        for(int i=n-k+1; i<=n; i++)
            y[++num]=i;   //y[i]=j:第二关键字排名i的是第j个
                        //此处不足补充空格的排在前面
        for(int i=1; i<=n; i++)
            if(sa[i]>k) //其它第二关键字的排名取决于第一关键字的排名
                y[++num]=sa[i]-k; //前k位被不足的子串占据，所以
                                //第二关键字后面排名的是第一关键字排序位置-k
        for(int i=1; i<=m; i++)
            c[i]=0;
        for(int i=1; i<=n; i++)
            c[ x[i] ]++;
        for(int i=2; i<=m; i++)
            c[i]+=c[i-1];
        for(int i=n; i; i--)
            sa[ c[ x[ y[i] ] ]-- ] =y[i], y[i]=0;
                //排名i是y[i]，y[i]的原始排名是x[y[i]],
                //原始排名x[y[i]]的最终排名是c[x[y[i]]]
                //最终排名c[x[y[i]]]的是第y[i]个，--是为了处理并列的，
                //从后开始，是为了在第一关键字相同的情况下保持第二关键字的原始顺序
        swap(x, y); //现在y没有用,改存x，即y[i]=j，老的第i个位置排名j
        x[ sa[1] ]=1, num=1;
        for(int i=2; i<=n; i++){
            bool due=(y[sa[i]]==y[sa[i-1]] && y[sa[i]+k]==y[sa[i-1]+k]);
            //新的相邻排名，其位置的老排名相同，那它的新排名其实是并列的
            if(!due) num++; //只有不并列，排名才会向前走
            x[sa[i]]= num; //排名i的位置，其连续的排名是num，并列的相同
        }
        if(num==n) break;
        m=num;
    }
}

void get_height(){
    for(int i=1; i<=n; i++)
        rk[sa[i]]=i;  //rk[j]=i:第j位置排名i, sa[i]=j:排名i的位置为j
    for(int i=1, k=0; i<=n; i++){
        if(rk[i]==1) continue; //排名第1的不需计算，
        if(k)k--; //去掉前面已经比较的一个字符
        int j=sa[rk[i]-1]; //这个位置也许与前面比较的j位置不同，
                            //但是去掉前面一个字符后,相同部分不会少
        while(i+k<=n && s[i+k]==s[j+k])//从k位置开始比较
            k++;
        height[rk[i]]=k; //排名rk[i]的height
    }
}

int main(){
    scanf("%s", s+1);
    n=strlen(s+1), m='z';
    get_sa();
    get_height();

    for(int i=1; i<=n; i++) printf("%d ", sa[i]);
    puts("");
    for(int i=1; i<=n; i++) printf("%d ", height[i]);
    puts("");
    return 0;
}

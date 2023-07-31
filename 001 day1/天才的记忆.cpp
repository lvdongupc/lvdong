//本题的逻辑结构：RMQ
//本题的存储结构：顺序
/*解题思路和算法
(RMQ算法,也成为st表) O(nlogn)
题中数据量比较大，查询也比较多，寻常的平方复杂度一定会超时，这里采用RMQ算法，
实际上就是用动态规划预先处理数据，查询时时间复杂度是常数级。
*/
//效率:时间复杂度:O(NlogN)+O(MlogN) 空间复杂度 O(NlogN)
/*测试数据
输入：
6
34 1 8 123 3 2
4
1 2
1 5
3 4
2 3
输出：
34
123
123
8
*/
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAXN=2e5+10;
inline int read()
{
    char c=getchar();int x=0,f=1;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}
int Max[MAXN][19];
int Query(int l,int r)
{
    int k=log2(r-l+1);
    return max(Max[l][k],Max[r-(1<<k)+1][k]);//把拆出来的区间分别取最值
}
int main()
{
    int N=read();
    for(int i=1;i<=N;i++) Max[i][0]=read();
    for(int j=1;j<=log2(N);j++)
        for(int i=1;i+(1<<j)-1<=N;i++)//注意这里要控制边界
            Max[i][j]=max(Max[i][j-1],Max[i+(1<<(j-1))][j-1]);//如果看不懂边界的话建议好好看看图

   int M=read();
    for(int i=1;i<=M;i++)
    {
        int l=read(),r=read();
        printf("%d\n",Query(l,r));
    }
    return 0;
}

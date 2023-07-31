//本题的逻辑结构：树状数组
//本题的存储结构：顺序
/*
解题思路和算法:
树状数组只支持单点查询,但是这里我们要资瓷区间操作,那么就得来一点特殊操作.
首先我们可以开一个数组B,然后对于每条C操作,我们直接利用前缀和的思想.
把b[l]+=d;
把b[r+1]-=d;
然后我们就成功达成成就,把维护序列的具体值,转化为维护指令的累计影响,
每次操作的影响,在l处开始,然后在r+1处消除.然后就让单点修改可以维护区间修改。
*/
//效率:时间复杂度：O(n+mlogn) 空间复杂度 O(max(n,m))
/*测试数据：
输入：
10 5
1 2 3 4 5 6 7 8 9 10
Q 4
Q 1
Q 2
C 1 6 3
Q 2
输出：
4
1
2
5
*/
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
int input[500010];
int tree[500100];
int lowbit(int x)
{
    return x & -x;
}
void add(int x,int k)
{
    while(x<=n)
    {
        tree[x]+=k;
        x+=lowbit(x);
    }
}
int search(int x)
{
    int ans=0;
    while(x!=0)
    {
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}
signed main()
{
    cin>>n>>m;
    for(int i=1; i<=n; i++)
        cin>>input[i];
    for(int i=1; i<=m; i++)
    {
        char a;
         cin>>a;
        if(a=='C')
        {
            int x,y,z;
            cin>>x>>y>>z;
            add(x,z);
            add(y+1,-z);
        }
        if(a=='Q')
        {
            int x;
            cin>>x;
           cout<<input[x]+search(x)<<"\n";
        }
    }
    return 0;
}


//本题的逻辑结构：图论(并查集)
//本题的存储结构：顺序
/*
解题思路和算法:
观察题意：发现我们要判断画完线后有没有围成环
而如果能围成一个环，那么最后画的线的两个端点必然已经在一个连通块内
判断是否在一个连通块
使用并查集算法
并查集是一种树型的数据结构，用于处理一些不相交集合（disjointsetsdisjointsets）的合并及查询问题
*/
//效率:时间复杂度:O(n^2+m) 空间复杂度:O(N)
/*测试数据：
输入：
3 5
1 1 D
1 1 R
1 2 D
2 1 R
2 2 D

输出：
4
*/
#include<bits/stdc++.h>
using namespace std;
const int N=40010;
int n,m;
int p[N];
int get(int x, int y)
{
    return x*n+y;
}
int find(int x)
{
    if(p[x]!=x)return p[x]=find(p[x]);
    else
    {
        return x;
    }
}
int main()
{
    cin>> n>>m;

    for (int i=0; i<n*n;i++) p[i]=i;

   /*
   算法步骤如下：
   如果两个端点已经在同一个集合(find操作)，那么成环
   如果两个端点不在同一个集合内(find操作)，那么这两个集合连通，合并两个集合(merge操作)
  */
    int res=0;
    for (int i=1;i<=m;i++)
    {
        int x,y;
        char d;
        cin>>x>>y>>d;
        x--, y--;
        int a=get(x, y);
        int b;
        if (d=='D') b=get(x+1,y);
        else b=get(x,y+1);
        int pa=find(a), pb=find(b);
        if (pa==pb)
        {
            res=i;
            break;

        }
        p[pa]=pb;
    }

    if (!res)
    {
        cout<<"draw"<<"\n";
    }
    else cout<<res<<"\n";

    return 0;
}


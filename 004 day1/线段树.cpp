//本题的逻辑结构：线段树
//本题的存储结构：顺序
/*
解题思路和算法：
线段树（Segment Tree）是一种用于处理区间查询问题的数据结构。它可以有效地执行区间更新和区间查询操作，
尤其在数组上的范围求和、最小值、最大值等问题中非常常见和有用。
*/
//效率:时间复杂度：O(n+mlogn)空间复杂度：O(N)
/*测试数据：
输入：
5 5
1 5 4 2 3
2 2 4
1 2 3 2
2 3 4
1 1 5 1
2 1 4
输出：
11
8
20
  */
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<map>
using namespace std;
#define fp(i,a,b) for(int i=a;i<=b;++i)
#define int long long
const int N=1e5+10;
int n,m;
int a[N];
struct node
{
	int sum,lazy;
}t[N*4];
void pushup(int rt)
{
	t[rt].sum=t[rt<<1].sum+t[rt<<1|1].sum;
}
void build(int rt,int l,int r)
{
    if(l==r)
    {
        t[rt].lazy=0;
        t[rt].sum=a[l];
        return;
    }
    int mid=(l+r)>>1;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
    pushup(rt);
}
void pushdown(int rt,int l,int r)
{
    if(t[rt].lazy)
	{
		int mid=(l+r)>>1;
		t[rt<<1].sum+=(mid-l+1)*t[rt].lazy;
		t[rt<<1|1].sum+=(r-mid)*t[rt].lazy;
		t[rt<<1].lazy+=t[rt].lazy;
		t[rt<<1|1].lazy+=t[rt].lazy;
		t[rt].lazy=0;
	}
}
void update(int rt,int l,int r,int L,int R,int k)
{
	if(L<=l&&r<=R)
	{
		t[rt].lazy+=k;
		t[rt].sum+=(r-l+1)*k;
		return;
	}
	int mid=(l+r)>>1;
	pushdown(rt,l,r);
	if(L<=mid)update(rt<<1,l,mid,L,R,k);
	if(R>mid)update(rt<<1|1,mid+1,r,L,R,k);
	pushup(rt);
}
int query(int rt,int l,int r,int L,int R)
{
	if(L<=l&&r<=R)
	{
		return t[rt].sum;
	}
	pushdown(rt,l,r);
	int mid=(l+r)>>1;
	int ans=0;
	if(L<=mid)ans+=query(rt<<1,l,mid,L,R);
	if(R>mid)ans+=query(rt<<1|1,mid+1,r,L,R);
	return ans;
}
signed main()
{
   cin>>n>>m;

   fp(i,1,n)cin>>a[i];

   build(1,1,n);

   fp(i,1,m)
   {
   	 int op,x,y;
	 int k;
	 cin>>op;
	 if(op==1)
	 {
	 	cin>>x>>y>>k;
	 	update(1,1,n,x,y,k);
     }
     else
     {
     	cin>>x>>y;
     	cout<<query(1,1,n,x,y)<<"\n";
	 }
   }

   return 0;
}

//线段树、树状数组、阶乘、exgcd、二分

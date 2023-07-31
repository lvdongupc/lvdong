//本题的逻辑结构： 线段树
//本题的存储结构： 顺序
/*解题思路和算法：
考虑用一种好想又好写的做法：
sin(a+x)=sin a cos x+cos a sin x
sin(a+x)=sin a cos x+cos a sin x

cos(a+x)=cos a cos x-sin a sin x
cos(a+x)=cos a cos x−sin a sin x
*/
//效率:时间复杂度：O(T*n) 空间复杂度：O(n)
/*测试数据：
输入：
5
1 3 1 5 5
5
1 5 5 5
2 3 3
2 1 5
2 2 2
2 4 4
输出：
0.8
0.3
0.1
-1.0
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
typedef double db;
const int N=2e5+10;
int n;
int a[N];
struct node
{
   db a,b;//a´ú±ísinx,b´ú±ícosx

   int lazy;
}t[N*4];

void pushup(int rt)
{
    t[rt].a=t[rt<<1].a+t[rt<<1|1].a;
    t[rt].b=t[rt<<1].b+t[rt<<1|1].b;
}

void pushdown(int rt)
{

   if(t[rt].lazy)
   {
       int x=t[rt].lazy;
       double aa=t[rt<<1].a*cos(x)+t[rt<<1].b*sin(x);
       double bb=t[rt<<1].b*cos(x)-t[rt<<1].a*sin(x);
       t[rt<<1].lazy+=x;
       t[rt<<1].a=aa;
       t[rt<<1].b=bb;


        aa=t[rt<<1|1].a*cos(x)+t[rt<<1|1].b*sin(x);
        bb=t[rt<<1|1].b*cos(x)-t[rt<<1|1].a*sin(x);
       t[rt<<1|1].lazy+=x;
       t[rt<<1|1].a=aa;
       t[rt<<1|1].b=bb;



       t[rt].lazy=0;
   }

}
void build(int rt,int l,int r)
{
    if(l==r)
    {
        t[rt].a=sin(a[l]);
        t[rt].b=cos(a[l]);
        return;
    }
    int mid=(l+r)>>1;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
    pushup(rt);
}

void update(int rt,int l,int r,int L,int R,int val)
{
    if(L<=l&&R>=r)
    {
         double aa=t[rt].a*cos(val)+t[rt].b*sin(val);
         double bb=t[rt].b*cos(val)-t[rt].a*sin(val);
         t[rt].lazy+=val;
          t[rt].a=aa;
          t[rt].b=bb;
         return;
    }
    pushdown(rt);
    int mid=(l+r)>>1;
    if(L<=mid)update(rt<<1,l,mid,L,R,val);
    if(R>mid)update(rt<<1|1,mid+1,r,L,R,val);
    pushup(rt);
}


db query(int rt,int l,int r,int L,int R)
{
    if(L<=l&&R>=r)
    {
        return t[rt].a;
    }
    pushdown(rt);
    int mid=(l+r)>>1;
    db ans=0;
    if(L<=mid)ans+=query(rt<<1,l,mid,L,R);
    if(R>mid)ans+=query(rt<<1|1,mid+1,r,L,R);
    return ans;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);




    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    build(1,1,n);

    int T;
    cin>>T;
    while(T--)
    {
        int op,l,r;
        cin>>op>>l>>r;
        if(op==1)
        {
            int v;
            cin>>v;
            update(1,1,n,l,r,v);
        }
        else
        {
          cout<<fixed<<setprecision(1)<<query(1,1,n,l,r)<<"\n";
        }
    }
    return 0;
}

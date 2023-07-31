//本题的逻辑结构：线段树
//本题的存储结构：顺序
/*解题思路和算法：
对于sumsum区间和，我们先对儿子节点区间和×乘法标记+加法标记 ×区间长度
对于乘法标记，我们对儿子节点直接×乘法标记
对于加法标记，我们对儿子节点先×乘法标记+加法标记
*/
//效率:时间复杂度:O(nlogn) 空间复杂度：O(nlogn)
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+10;
int a[N];
struct node
{
    int sum,lazy[2];
} t[N*4];
int n,m,mod;
void pushup(int rt)
{
    t[rt].sum=(t[rt<<1].sum+t[rt<<1|1].sum)%mod;
}
void pushdown(int rt,int l,int r)
{
    if (t[rt].lazy[0] != 1)
    {

        t[rt<<1].sum*=t[rt].lazy[0];
        t[rt<<1].sum%=mod;

        t[rt<<1|1].sum*=t[rt].lazy[0];
        t[rt<<1|1].sum%=mod;

        t[rt<<1].lazy[0]*=t[rt].lazy[0];
        t[rt<<1].lazy[0]%=mod;

        t[rt<<1|1].lazy[0]*=t[rt].lazy[0];
        t[rt<<1|1].lazy[0]%=mod;

        t[rt<<1].lazy[1]*=t[rt].lazy[0];
        t[rt<<1].lazy[1]%=mod;

        t[rt<<1|1].lazy[1]*=t[rt].lazy[0];
        t[rt<<1|1].lazy[1]%=mod;

        t[rt].lazy[0] = 1;
    }
    if (t[rt].lazy[1])
    {
        int mid = l+r>>1;
        t[rt<<1].sum+= t[rt].lazy[1]*(mid-l+1);
        t[rt<<1].sum%=mod;

        t[rt<<1|1].sum+=t[rt].lazy[1]*(r-mid);
        t[rt<<1|1].sum%=mod;

        t[rt<<1].lazy[1]+=t[rt].lazy[1];
        t[rt<<1].lazy[1]%=mod;

        t[rt<<1|1].lazy[1]+=t[rt].lazy[1];
        t[rt<<1|1].lazy[1]%=mod;

        t[rt].lazy[1] = 0;
    }
}
void build(int rt,int l,int r)
{
    t[rt].sum=t[rt].lazy[1]=0;
    t[rt].lazy[0]=1;
    if(l==r)
    {
        t[rt].sum=a[l]%mod;
        return ;
    }
    int mid=(l+r)>>1;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
    pushup(rt);
}
void update1(int rt,int l,int r,int L,int R,int val)
{
    if(L<=l&&r<=R)
    {
        t[rt].sum=t[rt].sum*val%mod;
        t[rt].lazy[0]=t[rt].lazy[0]*val%mod;
        t[rt].lazy[1]=t[rt].lazy[1]*val%mod;
        return ;
    }
    pushdown(rt,l,r);
    int mid=(l+r)>>1;
    if(L<=mid) update1(rt<<1,l,mid,L,R,val);
    if(R>mid)update1(rt<<1|1,mid+1,r,L,R,val);
    pushup(rt);
}
void update2(int rt,int l,int r,int L,int R,int val)
{
    if(L<=l&&r<=R)
    {
        t[rt].sum=(t[rt].sum+val*(r-l+1))%mod;
        t[rt].lazy[1]=(t[rt].lazy[1]+val)%mod;
        return ;
    }
    pushdown(rt,l,r);
    int mid=(l+r)>>1;
    if(L<=mid) update2(rt<<1,l,mid,L,R,val);
    if(R>mid)update2(rt<<1|1,mid+1,r,L,R,val);
    pushup(rt);
}
int query(int rt,int l,int r,int L,int R)
{
    if(L<=l&&R>=r)
    {
        return t[rt].sum;
    }
    pushdown(rt,l,r);
    int mid=(l+r)>>1;
    int ans=0;
    if(mid >= R) ans=(ans+query(rt<<1, l, mid, L, R))%mod;
    else if(mid < L) ans=(ans+query(rt<<1|1, mid + 1, r, L, R))%mod;
    else
    {
        ans=(ans+query(rt<<1, l, mid, L, mid)+query(rt<<1|1, mid + 1, r, mid + 1, R))%mod;
    }
    return ans;
}

signed main()
{
    cin>>n>>m>>mod;
    for(int i=1; i<=n; i++)
    {
        cin>>a[i];
    }

    build(1,1,n);

    for(int i=1; i<=m; i++)
    {
        int op,l,r;
        cin>>op>>l>>r;
        if(op<=2)
        {
            int x;
            cin>>x;
            if(op==1)
            {
                update1(1,1,n,l,r,x);//乘法
            }
            else
            {
                update2(1,1,n,l,r,x);//加法
            }
        }
        else
        {
            cout<<query(1,1,n,l,r)<<"\n";
        }
    }
    return 0;
}

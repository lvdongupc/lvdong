//������߼��ṹ���߶���
//����Ĵ洢�ṹ�� ˳��
/*����˼·���㷨��
����������˼·������ĳһ����ĳ��ȼ�ȥ��������������Ŀ�������������һ���޸�������Ҫ�򿪵Ƶ���Ŀ��
��ô�򿪵Ƶ���Ŀ���ˣ���Ȼ������������sum�ĸı䣬
���������Ҫά�����׺Ͷ��ӵ�sumֵ��
*/
//Ч��:ʱ�临�Ӷȣ�O(n+m*logn) �ռ临�Ӷȣ�O(MAXN)
/*�������ݣ�
���룺
4 5
0 1 2
0 2 4
1 2 3
0 2 4
1 1 4
�����
1
2
*/
#include<bits/stdc++.h>
#define MAXN 1000001
#define ll long long
using namespace std;
unsigned ll n,m,a[MAXN],ans[MAXN<<2],tag[MAXN<<2];
inline ll ls(ll x)
{
    return x<<1;
}
inline ll rs(ll x)
{
    return x<<1|1;
}
void scan()
{
    cin>>n>>m;
}
inline void push_up(ll p)
{
    ans[p]=ans[ls(p)]+ans[rs(p)];
}
void build(ll p,ll l,ll r)
{
    if(l==r)
    {
        ans[p]=a[l];
        return ;
    }
    ll mid=(l+r)>>1;
    build(ls(p),l,mid);
    build(rs(p),mid+1,r);
    push_up(p);
}
inline void f(ll p,ll l,ll r)
{
    tag[p]^=1;
    ans[p]=r-l+1-ans[p];
}
inline void push_down(ll p,ll l,ll r)
{
    if(tag[p]==0)
        return ;
    ll mid=(l+r)>>1;
    f(ls(p),l,mid);
    f(rs(p),mid+1,r);
    tag[p]=0;
}
inline void update(ll nl,ll nr,ll l,ll r,ll p)
{
    if(nl<=l&&r<=nr)
    {
      f(p,l,r);
        return ;
    }
    push_down(p,l,r);
    ll mid=(l+r)>>1;
    if(nl<=mid)update(nl,nr,l,mid,ls(p));
    if(nr>mid) update(nl,nr,mid+1,r,rs(p));
    push_up(p);
}
ll query(ll q_x,ll q_y,ll l,ll r,ll p)
{
    ll res=0;
    if(q_x<=l&&r<=q_y)return ans[p];
    ll mid=(l+r)>>1;
    push_down(p,l,r);
    if(q_x<=mid)res+=query(q_x,q_y,l,mid,ls(p));
    if(q_y>mid) res+=query(q_x,q_y,mid+1,r,rs(p));
    return res;
}
int main()
{
    ll a1,b,c,d,e,f;
    scan();
    build(1,1,n);
    while(m--)
    {
        scanf("%lld",&a1);
        switch(a1)
        {
        case 0:
        {
            scanf("%lld%lld",&b,&c);
            update(b,c,1,n,1);
            break;
        }
        case 1:
        {
            scanf("%lld%lld",&e,&f);
            printf("%lld\n",query(e,f,1,n,1));
            break;
        }
        }
    }
    return 0;
}

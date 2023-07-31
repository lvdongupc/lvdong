//������߼��ṹ�� �����ʷ֡��߶���
//����Ĵ洢�ṹ�� ˳��
/*����˼·���㷨��
ÿ�ΰ�װ������ͰѸ��ڵ㵽x���·���ϵ�ֵȫ����Ϊ1
ͬ��ÿ��ж��������Ͱ�x�Լ�����������ֵ��Ϊ0
�����ǿ���������͵�˼�룬ÿ�β���֮ǰ��¼һ��tree[root].sum��ֵ��
����֮���ٲ�ѯһ��tree[root].sum��ֵ������֮��ľ���ֵ��Ϊ�𰸡�
*/
//Ч��:ʱ�临�Ӷ�: O(q*n) �ռ临�Ӷȣ�O(n)
/*�������ݣ�
���룺
7
0 0 0 1 1 5
5
install 5
install 6
uninstall 1
install 4
uninstall 0
�����
3
1
3
2
3
*/
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
#define fp(i,a,b) for(int i=a;i<=b;i++)
int e[N],ne[N],h[N],idx;
int tid[N],top[N],son[N],father[N],deep[N],size[N],tidnum;
int n,q;
char s[15];
void add(int x,int y)
{
    e[idx]=y;
    ne[idx]=h[x];
    h[x]=idx++;
}
struct node
{
    int sum,lazy;
} t[N*4];
void dfs1(int x,int fa,int depth)
{
    size[x]=1;

    father[x]=fa;

    deep[x]=depth;

    for(int i=h[x]; ~i; i=ne[i])
    {
        int j=e[i];

        if(j==fa) continue;

        dfs1(j,x,depth+1);

        size[x]+=size[j];

        if(!son[x]||size[j]>size[son[x]]) son[x]=j;
    }
}
void dfs2(int x,int tp)
{
    tid[x]=++tidnum;

    top[x]=tp;

    if(!son[x]) return;

    dfs2(son[x],tp);

    for(int i=h[x]; ~i; i=ne[i])
    {
        int j=e[i];
        if(j!=son[x]&&j!=father[x])
            dfs2(j,j);
    }
}
void pushup(int rt)
{
    t[rt].sum=t[rt<<1].sum+t[rt<<1|1].sum;
}
void pushdown(int rt,int l,int r)
{
    if(t[rt].lazy!=-1)
    {
        int mid=(l+r)>>1;
        t[rt<<1].sum=t[rt].lazy*(mid-l+1);
        t[rt<<1].lazy=t[rt].lazy;

        t[rt<<1|1].sum=t[rt].lazy*(r-mid);
        t[rt<<1|1].lazy=t[rt].lazy;

        t[rt].lazy=-1;
    }
}
void build(int rt,int l,int r)
{
    t[rt].lazy=-1;
    if(l==r)
    {
        t[rt].sum=0;
        return ;
    }
    int mid=(l+r)>>1;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
    pushup(rt);
}
void update(int rt,int l,int r,int L,int R,int val)
{
    if(L<=l && R>=r)
    {
        t[rt].sum=val*(r-l+1);
        t[rt].lazy=val;
        return;
    }
    pushdown(rt,l,r);

    int mid=(l+r)>>1;
    if(L<=mid) update(rt<<1,l,mid,L,R,val);
    if(R>mid)update(rt<<1|1,mid+1,r,L,R,val);
    pushup(rt);

}
void change(int u,int v,int val)
{
    while(top[u]!=top[v])
    {
        if(deep[top[u]]<deep[top[v]]) swap(u,v);
        update(1,1,n,tid[top[u]],tid[u],val);
        u=father[top[u]];
    }
    if(deep[u]>deep[v]) std::swap(u,v);
    update(1,1,n,tid[u],tid[v],val);
    return;
}
int main()
{
    memset(h,-1,sizeof h);

    scanf("%d",&n);

    fp(i,2,n)
    {
        int x;

        scanf("%d",&x);
        x++;

        add(x,i);
    }

    dfs1(1,1,1);

    dfs2(1,1);

    build(1,1,tidnum);

    scanf("%d",&q);

    fp(i,1,q)
    {
        scanf("%s",s);

        int x;

        scanf("%d",&x);
        x++;

        int t1=t[1].sum;
        if(s[0]=='i')
        {
            change(1,x,1);
            int t2=t[1].sum;
            printf("%d\n",abs(t2-t1));
        }
        else if(s[0]=='u')
        {
            update(1,1,n,tid[x],tid[x]+size[x]-1,0);
            int t2=t[1].sum;
            printf("%d\n",abs(t2-t1));
        }
    }

    return 0;
}

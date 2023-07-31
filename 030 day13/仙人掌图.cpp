//������߼��ṹ��ͼ��(������)
//����Ĵ洢�ṹ���ڽӱ�
/*����˼·���㷨��
�����Ƚ�������ת����һ��Բ������Ȼ�����ǿ�����Բ��������ԭ���⡣
Ȼ�����ǿ��������� dpdp ��˼���������⣬����ö��ÿһ������Ϊ������ߵ㣬
��ʱ�����õ��ֱ��Ӧ���Ǹõ������ܵ�����·�ʹγ�·�ĺ͡�Ȼ��ͳ�����е���Ϊ��ߵ�������ȡһ�����ֵ����ֱ����
*/
//Ч��:ʱ�临�Ӷȣ�O(n+m)�ռ临�Ӷȣ�O(n+m)
/*�������ݣ�
���룺
15 3
9 1 2 3 4 5 6 7 8 3
7 2 9 10 11 12 13 10
5 2 14 9 15 10
�����
8
*/
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int N=1e5+10,M=N<<2,INF=1e9;
int h1[N],h2[N],idx;
int e[M],ne[M],w[M];
int n,m,new_n;
void add(int h[],int x,int y,int z){
    e[idx]=y,ne[idx]=h[x],w[idx]=z,h[x]=idx++;
}
int dfn[N],low[N],ts;
int fu[N],fw[N],fe[N];
int s[N],stot[N];
void build_circle(int x,int y,int z){
    int sum=z;
    for(int i=y;i!=x;i=fu[i]){
        s[i]=sum;
        sum+=fw[i];
    }
    s[x]=stot[x]=sum;
    add(h2,x,++new_n,0);
    for(int i=y;i!=x;i=fu[i]){
        stot[i]=sum;
        add(h2,new_n,i,min(s[i],sum-s[i]));
    }
}
void tarjan(int u,int from){
    dfn[u]=low[u]=++ts;
    for(int i=h1[u];~i;i=ne[i]){
        if((i^1)==from)continue;
        int j=e[i];
        if(!dfn[j]){
            fu[j]=u,fw[j]=w[i],fe[j]=i;
            tarjan(j,i);
            low[u]=min(low[u],low[j]);
            if(low[j]>dfn[u])
                add(h2,u,j,1);
        }
        else
            low[u]=min(low[u],dfn[j]);
    }
    for(int i=h1[u];~i;i=ne[i]){
        if((i^1)==from)continue;
        int j=e[i];
        if(dfn[u]<dfn[j]&&fe[j]!=i)
            build_circle(u,j,w[i]);
    }
}
int f[N],d[N];
int ans;
int q[N],hh,tt;
int dfs(int u){
    int d1=0,d2=0;
    for(int i=h2[u];~i;i=ne[i]){
        int j=e[i];
        int d=dfs(j)+w[i];
        if(d>=d1)d2=d1,d1=d;
        else if(d>d2)d2=d;
    }
    f[u]=d1;
    if(u<=n)
        ans=max(ans,d1+d2);
    else{
        int sz=0;
        d[sz++]=-INF;
        for(int i=h2[u];~i;i=ne[i])
            d[sz++]=f[e[i]];
        for(int i=0;i<sz;i++)
            d[i+sz]=d[i];
        hh=0,tt=-1;
        for(int i=0;i<sz<<1;i++){
            if(hh<=tt&&i-q[hh]>sz/2)hh++;
            if(hh<=tt)ans=max(ans,d[q[hh]]+d[i]+i-q[hh]);
            while(hh<=tt&&d[i]-i>=d[q[tt]]-q[tt])
                tt--;
            q[++tt]=i;
        }
    }
    return f[u];
}
int main(){
    memset(h1,-1,sizeof h1);
    memset(h2,-1,sizeof h2);
    scanf("%d%d",&n,&m);
    new_n=n;
    while(m--){
        int k,x,y;
        scanf("%d%d",&k,&x);
        for(int i=k;--i;){
            scanf("%d",&y);
            add(h1,x,y,1);
            add(h1,y,x,1);
            x=y;
        }
    }
    tarjan(n,-1);
    dfs(n);
    printf("%d\n",ans);
    return 0;
}



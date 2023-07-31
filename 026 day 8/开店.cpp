//本题的逻辑结构：点分树
//本题的存储结构： 邻接表
/*解题思路和算法：
找出重心，然后对子树分治统计。
由于每一层的所有递归过程合计对每个点处理一次。
*/
//效率:时间复杂度：O(n+Qlog(n))空间复杂度：O(N)
/*测试数据：
输入：
10 10 10
0 0 7 2 1 4 7 7 7 9
1 2 270
2 3 217
1 4 326
2 5 361
4 6 116
3 7 38
1 8 800
6 9 210
7 10 278
8 9 8
2 8 0
9 3 1
8 0 8
4 2 7
9 7 3
4 7 0
2 2 7
3 2 1
2 3 4
输出：
1603
957
7161
9466
3232
5223
1879
1669
1282
0
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
const int N=1.5e5+10,INF=1e9+10;
int ela[N],idx=1;
struct path{
    int en,len,nex;
}edge[N<<1];
void add(int x,int y,int w){
    edge[idx]=(path){y,w,ela[x]};
    ela[x]=idx++;
}
bool st[N];
int get_sz(int u,int fa){
    if(st[u])return 0;
    int res=1;
    for(int i=ela[u];i;i=edge[i].nex)
        if(edge[i].en!=fa)
            res+=get_sz(edge[i].en,u);
    return res;
}
int get_wc(int u,int fa,int tot,int &wc){
    if(st[u])return 0;
    int sum=1,ms=1;
    for(int i=ela[u];i;i=edge[i].nex){
        int j=edge[i].en;
        if(j==fa)continue;
        int t=get_wc(j,u,tot,wc);
        sum+=t;
        ms=max(ms,t);
    }
    ms=max(ms,tot-sum);
    if(ms<<1<=tot)
        wc=u;
    return sum;
}
struct Son{
    int age;
    ll dist;
    bool operator<(const Son &t)const{
        return age<t.age;
    }
};
vector<Son>son[N][3];
struct father{
    int u,num;
    ll dist;
};
int age[N];
vector<father>f[N];
void get_dist(int u,int fa,int wc,ll dist,int k,vector<Son>&p){
    if(st[u])return;
    p.push_back((Son){age[u],dist});
    f[u].push_back((father){wc,k,dist});
    for(int i=ela[u];i;i=edge[i].nex){
        int j=edge[i].en;
        if(j==fa)continue;
        get_dist(j,u,wc,dist+edge[i].len,k,p);
    }
}
int n,Q,A;
void calc(int u){
    if(st[u])return;
    get_wc(u,-1,get_sz(u,-1),u);
    st[u]=1;
    for(int i=ela[u],k=0;i;i=edge[i].nex){
        int j=edge[i].en;
        if(st[j])continue;
        vector<Son>&p=son[u][k];
        get_dist(j,-1,u,edge[i].len,k,p);
        p.push_back((Son){-1,0});
        p.push_back((Son){INF,0});
        sort(p.begin(),p.end());
        for(int i=1;i<p.size();i++)
            p[i].dist+=p[i-1].dist;
        k++;
    }
    for(int i=ela[u];i;i=edge[i].nex)
        calc(edge[i].en);
}
int find(int x,vector<Son>&p){
    int l=0,r=p.size()-1,mid;
    while(l<=r){
        mid=l+r>>1;
        if(p[mid].age<x)
            l=mid+1;
        else
            r=mid-1;
    }
    return l;
}
ll query(int u,int l,int r){
    ll res=0;
    for(vector<father>::iterator it=f[u].begin();it!=f[u].end();it++){
        father &t=(*it);
        int g=age[t.u];
        if(g>=l&&g<=r)
            res+=t.dist;
        for(int i=0;i<3;i++){
            if(t.num==i)continue;
            vector<Son>&p=son[t.u][i];
            if(p.empty())continue;
            int a=find(l,p)-1,b=find(r+1,p)-1;
            res+=t.dist*(b-a)+p[b].dist-p[a].dist;
        }
    }
    for(int i=0;i<3;i++){
        vector<Son>&p=son[u][i];
        if(p.empty())continue;
        int a=find(l,p)-1,b=find(r+1,p)-1;
        res+=p[b].dist-p[a].dist;
    }
    return res;
}
inline int read(){
    int x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9')
        ch=getchar();
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x;
}
int main(){
    n=read(),Q=read(),A=read();
    for(int i=1;i<=n;i++)
        age[i]=read();
    for(int i=n-1,x,y,z;i--;){
        x=read(),y=read(),z=read();
        add(x,y,z),add(y,x,z);
    }
    calc(n);
    ll ans=0;
    int u,l,r;
    while(Q--){
        u=read(),l=read(),r=read();
        l=(l+ans)%A,r=(r+ans)%A;
        if(l>r)swap(l,r);
        printf("%lld\n",ans=query(u,l,r));
    }
    return 0;
}

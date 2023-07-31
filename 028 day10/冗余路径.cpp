//本题的逻辑结构：双连通分量
//本题的存储结构： 邻接表
/*解题思路和算法：
①如何判断x到y是不是桥?
搜完y之后 dfn[x]<low[y]dfn[x]<low[y] yy无论如何也走不到xx或xx的祖先
②如何找到所有边的双连通分量？
1.将所有桥删掉
2.用一个栈，如果dfn[x]==low[x]dfn[x]==low[x] 说明以xx为根节点的子树中，还在栈中的节点就是连通块中的节点
*/
//效率:时间复杂度：O(N+M)空间复杂度：O(N+M)
/*测试数据：
输入：
7 7
1 2
2 3
3 4
2 5
4 5
5 6
5 7
输出：
2
*/

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF =0x3f3f3f3f;
const int N=5e5+10;
const int M=2e6+10;
int n,m,cnt;
ll idx,idf,e[M*2],h[N],ne[2*M];
int u[N],v[N];
int d[N];
vector<int>ans[N];
int vis[N];
bool bridge[M*2];
ll dfn[N],low[N];
void add(int x,int y)
{
    e[idf]=y;
    ne[idf]=h[x];
    h[x]=idf++;
}
void tarjan(int u,int in_edge)
{
    low[u]=dfn[u]=++idx;
    for(int i=h[u]; ~i; i=ne[i])
    {
        int j=e[i];
        if(!dfn[j])
        {
            tarjan(j,i);
            low[u] = min(low[u],low[j]);
            if(low[j]>dfn[u])
            {
               bridge[i]=bridge[i^1]=true;
            }
        }
        else if(i!=(in_edge^1)) low[u]=min(low[u],dfn[j]);
    }
}
void dfs(int x)
{
    vis[x]=cnt;
    if(x)
    {
        ans[cnt].push_back(x);
    }
    for(int i=h[x];~i;i=ne[i])
    {
        int j=e[i];
        if(vis[j]||bridge[i])continue;
        dfs(j);
    }
}
int  main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    memset(h,-1,sizeof h);
    for(int i=1; i<=m; i++)
    {
        cin>>u[i]>>v[i];
        add(u[i],v[i]);
        add(v[i],u[i]);
    }
    for(int i=1; i<=n; i++)
    {
        if(!dfn[i])
        {
            tarjan(i,0);
        }
    }
    for(int i=1; i<=n; i++)
    {
        if(vis[i]==0)
        {
            cnt++;
            dfs(i);
        }
    }

    int cnt1=0;

    for(int i=1;i<=m;i++)
    {
        if(vis[u[i]]!=vis[v[i]])
        {
            d[vis[u[i]]]++;
            d[vis[v[i]]]++;
        }
    }
    for(int i=1;i<=cnt;i++)
    {
        if(d[i]==1)
        {
            cnt1++;
        }
    }
    cout<<(cnt1+1)/2<<"\n";

    return 0;
}


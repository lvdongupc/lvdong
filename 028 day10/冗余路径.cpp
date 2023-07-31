//������߼��ṹ��˫��ͨ����
//����Ĵ洢�ṹ�� �ڽӱ�
/*����˼·���㷨��
������ж�x��y�ǲ�����?
����y֮�� dfn[x]<low[y]dfn[x]<low[y] yy�������Ҳ�߲���xx��xx������
������ҵ����бߵ�˫��ͨ������
1.��������ɾ��
2.��һ��ջ�����dfn[x]==low[x]dfn[x]==low[x] ˵����xxΪ���ڵ�������У�����ջ�еĽڵ������ͨ���еĽڵ�
*/
//Ч��:ʱ�临�Ӷȣ�O(N+M)�ռ临�Ӷȣ�O(N+M)
/*�������ݣ�
���룺
7 7
1 2
2 3
3 4
2 5
4 5
5 6
5 7
�����
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


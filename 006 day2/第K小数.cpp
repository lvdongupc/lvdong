//本题的逻辑结构：权值线段树
//本题的存储结构：顺序
/*
解题思路和算法：
我们可以建立一颗权值线段树，每个点存储的信息为该值域区间存在的数的个数。
*/
//效率:时间复杂度：O(nlogn) 空间复杂度：O(nlogn)
/*测试数据：
输入：
7 3
1 5 2 6 3 7 4
2 5 3
4 4 1
1 7 3
输出：
5
6
3
*/
#include<bits/stdc++.h>
#define mid (l+r)/2
using namespace std;
#define int long long
const int N=100010,LOG=20;
int n,m,q,tot = 0;
int a[N],b[N];
int T[N],sum[N*LOG],L[N*LOG],R[N*LOG];
inline int build(int l, int r)
{
    int rt = ++ tot;
    if (l < r)
    {
        L[rt] = build(l, mid);
        R[rt] = build(mid+1, r);
    }
    return rt;
}
inline int update(int pre, int l, int r, int x)
{
    int rt = ++ tot;
    L[rt] = L[pre];
    R[rt] = R[pre];
    sum[rt] = sum[pre] + 1;
    if (l < r)
    {
        if (x <= mid) L[rt] = update(L[pre], l, mid, x);
        else R[rt] = update(R[pre], mid+1, r, x);
    }
    return rt;
}
inline int query(int u, int v, int l, int r, int k)
{
    if (l == r) return l;
    int x = sum[L[v]] - sum[L[u]];
    if (x >= k) return query(L[u], L[v], l, mid, k);
    else return query(R[u], R[v], mid+1, r, k-x);
}
/*
我们要用[li,ri]区间的数建立权值线段树。
我们发现可以用前缀和来维护：
只要用预处理大法分别以[1,li][1,li]和[1,ri][1,ri]的数建立权值线段树，每个点的值对位相减即可
*/
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    tot = 0;
    cin>>n>>q;
    for(int i=1; i<=n; i++)
    {
        cin>>a[i];
        b[i] = a[i];
    }
    sort(b+1, b+1+n);
    m = unique(b+1, b+1+n)-b-1;//由于值域很大，我们需要离散化一下。
    T[0] = build(1, m);
    for(int i=1;i<=n;i++)
    {
        a[i] = lower_bound(b+1, b+1+m, a[i]) - b;
        T[i] = update(T[i-1], 1, m, a[i]);
    }
    while (q --)
    {
        int x, y, z;
        cin>>x>>y>>z;
        int p = query(T[x-1], T[y], 1, m, z);
        cout<<b[p]<<"\n";
    }
    return 0;
}


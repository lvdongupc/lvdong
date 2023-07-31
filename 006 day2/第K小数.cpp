//������߼��ṹ��Ȩֵ�߶���
//����Ĵ洢�ṹ��˳��
/*
����˼·���㷨��
���ǿ��Խ���һ��Ȩֵ�߶�����ÿ����洢����ϢΪ��ֵ��������ڵ����ĸ�����
*/
//Ч��:ʱ�临�Ӷȣ�O(nlogn) �ռ临�Ӷȣ�O(nlogn)
/*�������ݣ�
���룺
7 3
1 5 2 6 3 7 4
2 5 3
4 4 1
1 7 3
�����
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
����Ҫ��[li,ri]�����������Ȩֵ�߶�����
���Ƿ��ֿ�����ǰ׺����ά����
ֻҪ��Ԥ����󷨷ֱ���[1,li][1,li]��[1,ri][1,ri]��������Ȩֵ�߶�����ÿ�����ֵ��λ�������
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
    m = unique(b+1, b+1+n)-b-1;//����ֵ��ܴ�������Ҫ��ɢ��һ�¡�
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


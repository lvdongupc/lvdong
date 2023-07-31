//本题的逻辑结构：图(差分约束)
//本题的存储结构： 邻接表
/*解题思路和算法：
1. 先将每个不等式 xi≤xj+ck，转化成一条从 xj 走到 xi，长度为 ck 的边。
2. 找到一个超级源点，使得该源点一定可以遍历到所有边
3. 从源点求一遍单源最短路
*/
//效率:时间复杂度：O(nm) 空间复杂度：O(n+m)
/*测试数据：
输入：
5 7
1 1 2
2 3 2
4 4 1
3 4 5
5 4 5
2 3 5
4 5 1
输出：
11
*/

#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 100010, M = 300010;
int n, m;
int h[N], e[M], w[M], ne[M], idx;
int dist[N];
int cnt[N];//统计到当前点总共有多少条边了
bool st[N];
void add(int a, int b, int c)
{
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx ++;
}
bool spfa()
{
    deque<int> q;
    q.push_back(0);
    st[0] = true;
    memset(dist,-0x3f,sizeof dist);
    dist[0] = 0;
    while(q.size())
    {
        int t = q.back();
        q.pop_back();
        st[t] = false;
        for (int i = h[t]; i!=-1; i = ne[i])
        {
            int j = e[i];
            if (dist[j] < dist[t] + w[i])
            {
                dist[j] = dist[t] + w[i];
                cnt[j] = cnt[t] + 1;
                if (cnt[j] >= n + 1) return false;//有负环 无解
                if (!st[j])
                {
                    q.push_back(j);
                    st[j] = true;
                }
            }
        }
    }
    return true;
}

signed main()
{
    cin >> n >> m;
    memset(h, -1, sizeof h);
    while (m -- )
    {
        int x, a, b;
        cin >> x >> a >> b;
        if (x == 1) add(b, a, 0), add(a, b, 0);//A=B
        else if (x == 2) add(a, b, 1);//B≥A+1
        else if (x == 3) add(b, a, 0);//A≥B
        else if (x == 4) add(b, a, 1);//A≥B+1
        else add(a, b, 0);//B≥A
    }
    for (int i = 1; i <= n; i ++ ) add(0, i, 1);

    if (!spfa()) cout << "-1" << "\n";
    else
    {
        int res = 0;
        for (int i = 1; i <= n; i ++ ) res += dist[i];
        cout << res << "\n";
    }
    return 0;
}


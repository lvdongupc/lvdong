//������߼��ṹ��ͼ(���Լ��)
//����Ĵ洢�ṹ�� �ڽӱ�
/*����˼·���㷨��
1. �Ƚ�ÿ������ʽ xi��xj+ck��ת����һ���� xj �ߵ� xi������Ϊ ck �ıߡ�
2. �ҵ�һ������Դ�㣬ʹ�ø�Դ��һ�����Ա��������б�
3. ��Դ����һ�鵥Դ���·
*/
//Ч��:ʱ�临�Ӷȣ�O(nm) �ռ临�Ӷȣ�O(n+m)
/*�������ݣ�
���룺
5 7
1 1 2
2 3 2
4 4 1
3 4 5
5 4 5
2 3 5
4 5 1
�����
11
*/

#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 100010, M = 300010;
int n, m;
int h[N], e[M], w[M], ne[M], idx;
int dist[N];
int cnt[N];//ͳ�Ƶ���ǰ���ܹ��ж���������
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
                if (cnt[j] >= n + 1) return false;//�и��� �޽�
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
        else if (x == 2) add(a, b, 1);//B��A+1
        else if (x == 3) add(b, a, 0);//A��B
        else if (x == 4) add(b, a, 1);//A��B+1
        else add(a, b, 0);//B��A
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


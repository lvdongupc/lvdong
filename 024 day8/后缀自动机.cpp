//������߼��ṹ����׺�Զ���
//����Ĵ洢�ṹ�� ��ʽ
/*����˼·���㷨��
SAM�Ǹ�״̬����һ����㣬�����յ㡣
ԭ���������Ӵ��ʹ�SAM��㿪ʼ������·��һһ��Ӧ��
���ز�©�������յ���ǰ�����׺�ĵ㡣 ÿ������������Ӵ�
ÿ���Ӵ���һһ��Ӧһ������㵽�õ��·����
����Щ�Ӵ�һ����������Ӵ���������׺��
*/
//Ч��:ʱ�临�Ӷȣ�O(n) �ռ临�Ӷȣ�O(n)
/*�������ݣ�
���룺
aabab
�����
4
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

typedef long long LL;
const int N = 2e6 + 10;

int tot = 1, last = 1;
struct Node{
    int len, fa;
    int ch[26];
}node[N];

char str[N];
LL f[N], ans;
int h[N], e[N], ne[N], idx;

void extend(int c){
    int p = last, np = last = ++ tot;
    f[tot] = 1;
    node[np].len = node[p].len + 1;
    for(; p && !node[p].ch[c]; p = node[p].fa)
        node[p].ch[c] = np;
    if(!p)
        node[np].fa = 1;
    else{
        int q = node[p].ch[c];
        if(node[q].len == node[p].len + 1)
            node[np].fa = q;
        else{
            int nq = ++ tot;
            node[nq] = node[q], node[nq].len = node[p].len + 1;
            node[q].fa = node[np].fa = nq;
            for(; p && node[p].ch[c] == q; p = node[p].fa)
                node[p].ch[c] = nq;
        }
    }
}

void add(int a, int b){
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void dfs(int u){
    for(int i = h[u]; i != -1; i = ne[i]){
        int j = e[i];
        dfs(j);
        f[u] += f[j];
    }
    if(f[u] > 1)
        ans = max(ans, f[u] * node[u].len);
}

int main(){
    scanf("%s", str);
    for(int i = 0; str[i]; i ++)
        extend(str[i] - 'a');
    memset(h, -1, sizeof h);
    for(int i = 2; i <= tot; i ++)
        add(node[i].fa, i);
    dfs(1);
    printf("%lld", ans);
}


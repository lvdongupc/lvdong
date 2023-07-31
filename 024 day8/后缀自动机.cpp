//本题的逻辑结构：后缀自动机
//本题的存储结构： 链式
/*解题思路和算法：
SAM是个状态机。一个起点，若干终点。
原串的所有子串和从SAM起点开始的所有路径一一对应，
不重不漏。所以终点就是包含后缀的点。 每个点包含若干子串
每个子串都一一对应一条从起点到该点的路径。
且这些子串一定是里面最长子串的连续后缀。
*/
//效率:时间复杂度：O(n) 空间复杂度：O(n)
/*测试数据：
输入：
aabab
输出：
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


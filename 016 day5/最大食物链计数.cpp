//本题的逻辑结构：图
//本题的存储结构：链式
/*解题思路和算法：
记忆化搜索，从入度为0且非孤立点进行搜索
*/
//效率:时间复杂度：O(n*(n+m)) 空间复杂度：O(M)
/*测试数据：
输入：
5 7
1 2
1 3
2 3
3 5
2 5
4 5
3 4
输出：
5
*/
#include<stdio.h>
#include<stdlib.h>
typedef long long ll;
typedef struct Node {
    int value;
    struct Node* next;
} Node;
ll n,m;
const int M=5e5+5;
const int mod=80112002;
ll* out;
ll* in;
ll ans;
Node** adjacencyList;
ll* dp;
ll cnt;
void addEdge(int from, int to) {
    Node* newNode=(Node*)malloc(sizeof(Node));
    newNode->value=to;
    newNode->next=NULL;

    if (adjacencyList[from]==NULL) {
        adjacencyList[from]=newNode;
    }
    else {
        Node* current=adjacencyList[from];
        while (current->next!=NULL) {
            current=current->next;
        }
        current->next=newNode;
    }
}

int dfs(ll x) {
    if (dp[x])
        return dp[x];
    ll abc=0;
    if (out[x]==0)
        return 1;
    Node* current=adjacencyList[x];
    while (current!=NULL) {
        abc=(abc+dfs(current->value))%mod;
        current=current->next;
    }
    dp[x]=abc;
    return abc;
}

int main() {
    scanf("%lld%lld", &n, &m);

    out=(ll*)malloc((n + 1) * sizeof(ll));
    in=(ll*)malloc((n + 1) * sizeof(ll));
    adjacencyList=(Node**)malloc((n + 1) * sizeof(Node*));
    dp=(ll*)malloc((n + 1) * sizeof(ll));

    for (int i=0; i<=n;i++) {
        out[i]=0;
        in[i]=0;
        adjacencyList[i]=NULL;
        dp[i]=0;
    }

    for (int i=1;i<=m;i++) {
        ll a, b;
        scanf("%lld%lld", &a, &b);
        addEdge(a, b);
        out[a]++;
        in[b]++;
    }

    for (int i=1; i<=n; i++) {
        if (in[i]==0 && out[i]!=0) {
            ans=(ans+dfs(i))%mod;
        }
    }

    printf("%lld", ans);

    return 0;
}

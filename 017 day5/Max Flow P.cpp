//本题的逻辑结构： 树链剖分
//本题的存储结构： 链式
/*解题思路和算法：
例如有一次操作是把红点（u）到绿点（v）之间的路径全部加x。那么我就标记dlt[u]+=x,dlt[v]+=x。
这样在最后求解的时候，回溯的时候顺便算一下答案就出来了。
然后我们要在lca(u,v)处标记dlt[lca(u,v)]-=2x。这样就使得加x的效果只局限在u v，
不会向lca(u,v)的爸爸蔓延。
*/
//效率:时间复杂度：O(V+E) 空间复杂度：O(V)
/*测试数据：
输入：
5 10
3 4
1 5
4 2
5 4
5 4
5 4
3 5
4 3
4 3
1 3
3 5
5 4
1 5
3 4
输出：
9
*/

#include<bits/stdc++.h>
const int N = 100010, M = N * 2;
struct Node {
    int val;
    struct Node* next;
};
struct Node* createNode(int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->val = val;
    newNode->next = NULL;
    return newNode;
}
struct Node* h[N];
int depth[N], fa[N][17];
int d[N];
int q[N];
int n, m;
int idx;
int ans;
void addEdge(int a, int b) {
    struct Node* newNode = createNode(b);
    newNode->next = h[a];
    h[a] = newNode;
}
void bfs() {
    memset(depth, 0x3f, sizeof depth);
    depth[0]=0;
    depth[1]=1;
    int hh=0, tt=0;
    q[0]=1;

    while (hh<=tt) {
        int t=q[hh++];
        struct Node* curr=h[t];
        while (curr!=NULL) {
            int j=curr->val;
            if (depth[j]>depth[t]+1) {
                depth[j]=depth[t]+1;
                q[++tt]=j;
                fa[j][0]=t;
                for (int k=1; k<=16; k++) {
                    fa[j][k]=fa[fa[j][k-1]][k-1];
                }
            }
            curr=curr->next;
        }
    }
}

int lca(int a, int b) {
    if (depth[a] < depth[b])
        a^=b, b^=a, a^=b;
    for (int k=16;k>=0;k--) {
        if (depth[fa[a][k]]>=depth[b]) {
            a=fa[a][k];
        }
    }
    if (a==b) return a;
    for (int k=16; k>=0;k--) {
        if (fa[a][k]!=fa[b][k]) {
            a=fa[a][k];
            b=fa[b][k];
        }
    }
    return fa[a][0];
}

void dfs(int u, int father) {
    struct Node* curr=h[u];
    while (curr!=NULL) {
        int j=curr->val;
        if (j!=father) {
            dfs(j, u);
            d[u]+=d[j];
        }
        curr=curr->next;
    }
}

int main() {
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++) {
        h[i]=NULL;
    }

    for (int i=0;i<n-1;i++) {
        int a, b;
        scanf("%d%d",&a,&b);
        addEdge(a,b);
        addEdge(b,a);
    }

    bfs();

    for (int i=0;i<m;i++) {
        int a, b;
        scanf("%d%d",&a,&b);
        int p=lca(a,b);
        d[a]++, d[b]++, d[p]--, d[fa[p][0]]--;
    }

    dfs(1, -1);

    for (int i=1;i<=n;i++) {
        if (d[i]>ans) {
            ans=d[i];
        }
    }

    printf("%d\n", ans);

    return 0;
}








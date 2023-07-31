//本题的逻辑结构：图
//本题的存储结构：链式
/*解题思路和算法：
匈牙利算法是由匈牙利数学家Edmonds于1965年提出，因而得名。匈牙利算法是基于Hall定理中充分性证明的思想，
它是部图匹配最常见的算法，该算法的核心就是寻找增广路径，它是一种用增广路径求二分图最大匹配的算法。
*/
//我把它理解我对象匹配，更容易理解

//效率:时间复杂度：O((n1+n2)*m) 空间复杂度：O(N+M)
/*测试数据：
输入：
2 2 4
1 1
1 2
2 1
2 2
输出：
2
*/
#include <stdio.h>
#include <stdlib.h>
#include<cstring>
#include<cstdio>
#include<string.h>
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
void addEdge(struct Node** head, int x, int y) {
    // 添加边x->y
    struct Node* newNode = createNode(y);
    newNode->next = head[x];
    head[x] = newNode;
}
int min(int a, int b) {
    return (a < b) ? a : b;
}
int max(int a, int b) {
    return (a > b) ? a : b;
}
int find(int x, struct Node** head, int* st, int* match) {
    struct Node* curr=head[x];
    while (curr!=NULL) {
        int j=curr->val;
        if (!st[j]) {
            st[j]=1;
            if (!match[j] || find(match[j], head, st, match)) {
                match[j]=x;
                return 1;
            }
        }
        curr=curr->next;
    }
    return 0;
}

int main() {
    int n1, n2, m;
    scanf("%d%d%d", &n1, &n2, &m);

    struct Node** head=(struct Node**)malloc((n1 + 1)*sizeof(struct Node*));
    for (int i=0;i<=n1;i++) {
        head[i]=NULL;
    }

    for (int i=0;i<m;i++) {
        int a,b;
        scanf("%d%d",&a,&b);
        addEdge(head,a,b);
    }

    int* st=(int*)calloc(n2+1, sizeof(int));
    int* match=(int*)calloc(n2+1, sizeof(int));
    int res=0;

    for (int i=1;i<=n1;i++) {
        memset(st, 0, sizeof(int) * (n2 + 1));
        if (find(i, head, st, match)) {
            res++;
        }
    }

    printf("%d\n", res);

    return 0;
}



//������߼��ṹ������DFS
//����Ĵ洢�ṹ����ʽ
/*����˼·���㷨:�����ҵ��������ģ�
�����������ɾ����ʣ�������ͨ���е��������ֵ��*/
//Ч��:ʱ�临�Ӷ�:O(n) �ռ临�Ӷ�:O(n)
/*�������ݣ�
���룺
9
1 2
1 7
1 4
2 8
2 5
4 3
3 9
4 6
�����
4
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long
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
    // ��ӱ�x->y
    struct Node* newNode = createNode(y);
    newNode->next = head[x];
    head[x] = newNode;

    // ��ӱ�y->x
    newNode = createNode(x);
    newNode->next = head[y];
    head[y] = newNode;
}
int min(int a, int b) {
    return (a < b) ? a : b;
}
int max(int a, int b) {
    return (a > b) ? a : b;
}
int minSubtreeSize(int u, struct Node** head, int* vis, int n, int* ans) {
    vis[u]=1;
    int size=0;
    int sum=1;

    struct Node* curr=head[u];
    while (curr!=NULL) {
        int v=curr->val;
        if (!vis[v]) {
            int s=minSubtreeSize(v, head, vis, n, ans);
            size=max(size, s);
            sum+=s;
        }
        curr=curr->next;
    }
    size=max(size, n-sum);
    *ans=min(*ans, size);

    return sum;
}

int main() {
    int n;
    scanf("%d",&n);

    struct Node** head=(struct Node**)malloc((n+1)*sizeof(struct Node*));
    for (int i=0;i<=n;i++){
        head[i]=NULL;
    }

    for (int i=1;i<=n-1;i++){
        int x,y;

        scanf("%d%d",&x,&y);

        addEdge(head,x,y);
    }


    int ans=n;

    int* vis=(int*)calloc(n+1,sizeof(int));

    minSubtreeSize(1, head, vis, n, &ans);

    printf("%d\n",ans);

    return 0;
}

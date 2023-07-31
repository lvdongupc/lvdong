//������߼��ṹ��ͼ
//����Ĵ洢�ṹ����ʽ
/*����˼·���㷨��
�������㷨������������ѧ��Edmonds��1965�����������������������㷨�ǻ���Hall�����г����֤����˼�룬
���ǲ�ͼƥ��������㷨�����㷨�ĺ��ľ���Ѱ������·��������һ��������·�������ͼ���ƥ����㷨��
*/
//�Ұ�������Ҷ���ƥ�䣬���������

//Ч��:ʱ�临�Ӷȣ�O((n1+n2)*m) �ռ临�Ӷȣ�O(N+M)
/*�������ݣ�
���룺
2 2 4
1 1
1 2
2 1
2 2
�����
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
    // ��ӱ�x->y
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



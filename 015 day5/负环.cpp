//本题的逻辑结构： 图论
//本题的存储结构： 链式
/*解题思路和算法：
用SPFA（Shortest Path Faster Algorithm）算法判断图中是否存在负环
*/
//效率:时间复杂度：O(nE) 空间复杂度：O(maxn)
/*测试数据：
输入：
2
3 4
1 2 2
1 3 4
2 3 1
3 1 -3
3 3
1 2 3
2 3 4
3 1 -8
输出：
NO
YES
*/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#define maxn 2010
struct EdgeNode
{
    int to;
    int w;
    struct EdgeNode *next;
};
typedef struct EdgeNode EdgeNode;
typedef struct
{
    EdgeNode *head;
} EdgeList;
int n, m;
EdgeList edge[maxn]; // 邻接表
int tot;
void Init()
{
    for (int i=0;i<maxn;i++)
        edge[i].head=NULL;
    tot=0;
}
void addEdgeNode(EdgeNode **head, int to, int w)
{
    EdgeNode *newNode=(EdgeNode *)malloc(sizeof(EdgeNode));
    newNode->to=to;
    newNode->w=w;
    newNode->next=*head;
    *head=newNode;
}
void addedge(int u, int v, int w)
{
    addEdgeNode(&edge[u].head, v, w);
}
typedef struct QueueNode
{
    int data;
    struct QueueNode *next;
} QueueNode;
typedef struct
{
    QueueNode *front;
    QueueNode *rear;
} Queue;
void initQueue(Queue *q)
{
    q->front=NULL;
    q->rear=NULL;
}
bool isEmpty(Queue *q)
{
    return (q->front==NULL);
}
void enqueue(Queue *q, int data)
{
    QueueNode *newNode=(QueueNode *)malloc(sizeof(QueueNode));
    newNode->data=data;
    newNode->next=NULL;
    if (isEmpty(q))
    {
        q->front=q->rear = newNode;
        return;
    }
    q->rear->next=newNode;
    q->rear=newNode;
}
int dequeue(Queue *q)
{
    if (isEmpty(q))
        return -1;

    QueueNode *temp=q->front;
    int data=temp->data;
    q->front=q->front->next;

    if (q->front == NULL)
        q->rear = NULL;
    free(temp);
    return data;
}
Queue Q;
int dis[maxn], vis[maxn], cnt[maxn];
bool spfa()
{
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    memset(cnt, 0, sizeof(cnt));
    dis[1]=0;
    vis[1]=1;
    enqueue(&Q, 1);

    while (!isEmpty(&Q))
    {
        int x=dequeue(&Q);
        vis[x]=0;
        EdgeNode *cur=edge[x].head;
        while (cur != NULL)
        {
            int y=cur->to, z=cur->w;
            if (dis[y] > dis[x]+z)
            {
                dis[y]=dis[x]+z;
                cnt[y]=cnt[x]+1;
                if (cnt[y]>=n)
                    return true;
                if (!vis[y])
                {
                    enqueue(&Q, y);
                    vis[y] = 1;
                }
            }
            cur=cur->next;
        }
    }
    return false;
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        Init();
        scanf("%d%d", &n, &m);
        int i;
        for (i=1; i<=m; i++)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            addedge(u, v, w);
            if (w>=0)
                addedge(v, u, w);
        }
        puts(spfa() ? "YES" : "NO");
    }
    return 0;
}


//本题的逻辑结构：栈
//本题的存储结构：链式
/*
解题思路和算法：用广度优先搜索的思想，每当队列pop出一个元素时，
将于其距离为1的节点都加到队列中（即层次遍历的思想）
*/
//效率:时间复杂度:O(n+m) 空间复杂度：O(maxn)
/*测试数据：
输入：
4 5
1 2
2 3
3 4
1 3
1 4
输出：
1
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const int maxn=1e5+5;
int n,m;
vector<int>G[maxn];
int dis[maxn];
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 定义链式队列结构
typedef struct {
    Node* front; // 队头指针
    Node* rear;  // 队尾指针
    int size;    // 队列中当前元素个数
} Queue;

// 初始化队列
Queue* initQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
    return queue;
}

// 判断队列是否为空
int isEmpty(Queue* queue) {
    return queue->size == 0;
}

// 入队
void enqueue(Queue* queue, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = NULL;

    if (isEmpty(queue)) {
        queue->front = new_node;
    } else {
        queue->rear->next = new_node;
    }
    queue->rear = new_node;
    queue->size++;
}

// 出队
int dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("队列为空，无法出队。\n");
        return -1; // 队列为空，返回一个特定值
    }

    int value = queue->front->data;
    Node* temp = queue->front;
    queue->front = queue->front->next;
    free(temp);
    queue->size--;

    if (isEmpty(queue)) {
        queue->rear = NULL; // 队列为空，重置rear指针
    }

    return value;
}

// 销毁队列
void destroyQueue(Queue* queue) {
    while (!isEmpty(queue)) {
        dequeue(queue);
    }
    free(queue);
}
 Queue* queues ;
int bfs()
{
    memset(dis,-1,sizeof dis);
    dis[1]=0;
    enqueue(queues,1);
    while(!isEmpty(queues))
    {
        int x=dequeue(queues);
        for(int i=0;i<G[x].size();i++)
        {
            int p=G[x][i];
            if(dis[p]==-1)
            {
                dis[p]=dis[x]+1;
                enqueue(queues,p);
            }
        }
    }
    return  dis[n] ;
}
int main()
{

   queues = initQueue();

    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        int u,v;
        cin>>u>>v;
        G[u].push_back(v);
    }
    cout<<bfs()<<endl;
    return 0;
}




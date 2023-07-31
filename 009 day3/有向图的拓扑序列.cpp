//本题的逻辑结构：栈
//本题的存储结构：链式
/*解题思路和算法：
一个有向图，如果图中有入度为 0 的点，就把这个点删掉，同时也删掉这个点所连的边。
一直进行上面出处理，如果所有点都能被删掉，则这个图可以进行拓扑排序。
*/
//效率:时间复杂度：O(n+m) 空间复杂度：O(N)
/*测试数据：
输入：
3 3
1 2
2 3
1 3
输出：
1 2 3
*/
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
#define fp(i,a,b) for(int i=a;i<=b;i++)
#define int long long
vector<int>G[N];
int n,m;
int d[N],cnt;
int t[N];
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
Queue* queues;
bool flag=false;
void toposort()
{
    for(int i=1; i<=n; i++)
    {
        if(d[i]==0)enqueue(queues,i);
    }
    while(!isEmpty(queues))
    {
        int x=dequeue(queues);
        t[++cnt]=x;
        for(int i=0; i<G[x].size(); i++)
        {
            d[G[x][i]]--;
            if(d[G[x][i]]==0)
            {
                enqueue(queues,G[x][i]);
            }
        }
    }
    if(cnt==n)
    {
        flag=true;
    }
}
/*
首先记录各个点的入度
然后将入度为 0 的点放入队列
将队列里的点依次出队列，然后找出所有出队列这个点发出的边，删除边，同事边的另一侧的点的入度 -1。
如果所有点都进过队列，则可以拓扑排序，输出所有顶点。否则输出-1，代表不可以进行拓扑排序。
*/
signed main()
{

    queues=initQueue();

    cin>>n>>m;

    fp(i,1,m)
    {
        int x,y;
        cin>>x>>y;
        G[x].push_back(y);
        d[y]++;
    }

    toposort();

    if(flag)
    {
        fp(i,1,cnt)
        {
            cout<<t[i]<<" ";
        }
    }
    else
    {
        cout<<-1<<"\n";
    }

    return 0;
}




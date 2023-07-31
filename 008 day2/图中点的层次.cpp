//������߼��ṹ��ջ
//����Ĵ洢�ṹ����ʽ
/*
����˼·���㷨���ù������������˼�룬ÿ������pop��һ��Ԫ��ʱ��
���������Ϊ1�Ľڵ㶼�ӵ������У�����α�����˼�룩
*/
//Ч��:ʱ�临�Ӷ�:O(n+m) �ռ临�Ӷȣ�O(maxn)
/*�������ݣ�
���룺
4 5
1 2
2 3
3 4
1 3
1 4
�����
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

// ������ʽ���нṹ
typedef struct {
    Node* front; // ��ͷָ��
    Node* rear;  // ��βָ��
    int size;    // �����е�ǰԪ�ظ���
} Queue;

// ��ʼ������
Queue* initQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
    return queue;
}

// �ж϶����Ƿ�Ϊ��
int isEmpty(Queue* queue) {
    return queue->size == 0;
}

// ���
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

// ����
int dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("����Ϊ�գ��޷����ӡ�\n");
        return -1; // ����Ϊ�գ�����һ���ض�ֵ
    }

    int value = queue->front->data;
    Node* temp = queue->front;
    queue->front = queue->front->next;
    free(temp);
    queue->size--;

    if (isEmpty(queue)) {
        queue->rear = NULL; // ����Ϊ�գ�����rearָ��
    }

    return value;
}

// ���ٶ���
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




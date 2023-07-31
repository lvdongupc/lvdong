//������߼��ṹ��ջ
//����Ĵ洢�ṹ����ʽ
/*����˼·���㷨��
һ������ͼ�����ͼ�������Ϊ 0 �ĵ㣬�Ͱ������ɾ����ͬʱҲɾ������������ıߡ�
һֱ�������������������е㶼�ܱ�ɾ���������ͼ���Խ�����������
*/
//Ч��:ʱ�临�Ӷȣ�O(n+m) �ռ临�Ӷȣ�O(N)
/*�������ݣ�
���룺
3 3
1 2
2 3
1 3
�����
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
���ȼ�¼����������
Ȼ�����Ϊ 0 �ĵ�������
��������ĵ����γ����У�Ȼ���ҳ����г���������㷢���ıߣ�ɾ���ߣ�ͬ�±ߵ���һ��ĵ����� -1��
������е㶼�������У��������������������ж��㡣�������-1���������Խ�����������
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




//������߼��ṹ��ǿ��ͨ����
//����Ĵ洢�ṹ����ʽ
/*����˼·���㷨��
��һ�����ʱ�����׷��ֵ��ȣ��ʹ����������ڵ�ǿ��ͨ�����е���ߵ㡣
��ʱ�ʹ������ǿ���˳�������ҳ�����ǿ��ͨ�����ˡ�
*/
//Ч��:ʱ�临�Ӷȣ�O(N+M+C*K) �ռ临�Ӷȣ�O(N)
/*�������ݣ�
���룺
3 3
1 2
2 1
2 3
�����
1
*/
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
vector<int>G[N];
int n,m;
int sum,low[N],ins[N],dfn[N],col,a,cmpi[N],F[N],cmp[N];
bool D[N];
typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* top;
    int size;
} LinkedStack;

LinkedStack* createStack() {
    LinkedStack* stack = (LinkedStack*)malloc(sizeof(LinkedStack));
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

int isEmpty(LinkedStack* stack) {
    return stack->size == 0;
}

int getSize(LinkedStack* stack) {
    return stack->size;
}

void push(LinkedStack* stack, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;
}

int pop(LinkedStack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty. Cannot pop.\n");
        return -1; // Return a sentinel value to indicate error
    }

    int poppedValue = stack->top->data;
    Node* temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
    stack->size--;

    return poppedValue;
}

LinkedStack* stacks;
int find()
{
    int ans=0;
    for(int i=1; i<=a; i++)
    {
        for(int j=0; j<G[F[i]].size(); j++) //�о������������ڽӵ�
        {
            if(!D[G[F[i]][j]])
            {
                ans++;   //����������ڽӵ㲻������һ��ǿ��ͨ�����Ļ�����ô���Ǿͷ��������ڵķ������˳���
            }
        }
    }

    return ans;
}//��һ��ǿ��ͨ�����ĳ���
void tarjan(int x)
{
    sum++;
    dfn[x]=low[x]=sum;
    push(stacks,x);
    ins[x]=1;
    for(int i=0; i<G[x].size(); i++)
    {
        if(ins[G[x][i]]==0)
        {
            tarjan(G[x][i]);
            low[x]=min(low[x],low[G[x][i]]);
        }
        else if(ins[G[x][i]]==1)
            low[x]=min(low[x],dfn[G[x][i]]);
    }
    if(dfn[x]==low[x])
    {
        col++;
        int node;
        do
        {
            node=pop(stacks);
            ins[node]=-1;
            D[node]=true;
            F[++a]=node;
            cmpi[col]++;
        }
        while(node!=x);
        cmp[col]=find();
        a=0;
        memset(D,false,sizeof D);
    }
    return ;
}
int main()
{
    stacks=createStack();
    cin>>n>>m;
    for(int i=1; i<=m; i++)
    {
        int a,b;
        cin>>a>>b;
        G[a].push_back(b);
    }
    for(int i=1; i<=n; i++)
    {
        if(!dfn[i])tarjan(i);
    }
    int c=0,ans;
    for(int i=1; i<=col; i++)
    {
        if(!cmp[i])
        {
            c++,ans=i;
        }
    }
    if(c==1)
    {
        cout<<cmpi[ans];
    }
    else
    {
        cout<<0;
    }

    return 0;
}

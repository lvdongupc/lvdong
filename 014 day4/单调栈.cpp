//������߼��ṹ�� ����ջ
//����Ĵ洢�ṹ�� ��ʽ
/*����˼·���㷨��
����ջ������һ��ջ������ջ��Ԫ�ر�֤�����ԡ�����ջ��Ԫ��Ҫô��С����Ҫô�Ӵ�С��
������ջά���ľ���һ����ǰ/���һ������/С����������
*/
//Ч��:ʱ�临�Ӷȣ�O(n) �ռ临�Ӷȣ�O(maxn)
/*�������ݣ�
���룺
5
1 4 2 3 5
�����
2 5 4 5 0
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=3e6+5;
ll n,a[maxn],f[maxn];
typedef struct Node {
    ll data;
    struct Node* next;
} Node;

typedef struct {
    Node* top;
} Stack;

void initialize(Stack* stack) {
    stack->top = NULL;
}

int isEmpty(Stack* stack) {
    return (stack->top == NULL);
}

void push(Stack* stack, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = stack->top;
    stack->top = newNode;
}

int pop(Stack* stack) {
    if (isEmpty(stack)) {
        return 0;  // ����һ�������ֵ��ʾջΪ��
    }

    Node* temp = stack->top;
    int poppedValue = temp->data;
    stack->top = temp->next;
    free(temp);
    return poppedValue;
}

int peek(Stack* stack) {
    if (isEmpty(stack)) {
        return 0;  // ����һ�������ֵ��ʾջΪ��
    }

    return stack->top->data;
}
int main()
{

  cin>>n;

  for(ll i=1;i<=n;i++)cin>>a[i];

  //����ѭ��
  Stack stack;

  initialize(&stack);

  for(ll i=n;i>=1;i--)
  {
      while(!isEmpty(&stack)&&a[peek(&stack)]<=a[i])pop(&stack);
      f[i]=isEmpty(&stack)?0:peek(&stack);
      push(&stack,i);
  }
  for(int i=1;i<=n;i++)
  {
      cout<<f[i]<<" ";
  }

    return 0;
}


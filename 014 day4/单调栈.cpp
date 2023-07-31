//本题的逻辑结构： 单调栈
//本题的存储结构： 链式
/*解题思路和算法：
单调栈，就是一个栈，不过栈内元素保证单调性。即，栈内元素要么从小到大，要么从大到小。
而单调栈维护的就是一个数前/后第一个大于/小于他的数。
*/
//效率:时间复杂度：O(n) 空间复杂度：O(maxn)
/*测试数据：
输入：
5
1 4 2 3 5
输出：
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
        return 0;  // 返回一个特殊的值表示栈为空
    }

    Node* temp = stack->top;
    int poppedValue = temp->data;
    stack->top = temp->next;
    free(temp);
    return poppedValue;
}

int peek(Stack* stack) {
    if (isEmpty(stack)) {
        return 0;  // 返回一个特殊的值表示栈为空
    }

    return stack->top->data;
}
int main()
{

  cin>>n;

  for(ll i=1;i<=n;i++)cin>>a[i];

  //倒序循环
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


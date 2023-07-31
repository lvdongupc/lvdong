//������߼��ṹ�����ȶ���
//����Ĵ洢�ṹ����ʽ
/*
����˼·���㷨��
(̰��,��������,��,���ȶ���) O(nlogn)
�������������ģ�ͣ�ÿ�κϲ�������С�����ѹ��Ӽ��ɡ�
ʹ��С����ά�����й��ӣ�ÿ�ε����Ѷ������ѹ��ӣ�������ϲ���
�ϲ�֮����������֮���ٴβ���С�����С�
ÿ�β����Ὣ���ӵĶ�����һ��һ������ n-1 �μ��ɽ����й��Ӻϲ���1�ѡ�
ÿ�β����漰��2�ζѵ�ɾ��������1�ζѵĲ���������������� O(logn)��
�����ʱ�临�Ӷ��� O(nlogn)��
*/
//Ч��:ʱ�临�Ӷ�:O(nlogn) �ռ临�Ӷȣ�O(nlogn)
/*�������ݣ�
���룺
3
1 2 9
�����
15
*/
#include <stdio.h>
#include <stdlib.h>
typedef long long ll;
typedef struct {
    int* heap;
    int size;
    int capacity;
} PriorityQueue;
PriorityQueue* createPriorityQueue(int capacity) {
    PriorityQueue* pque = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pque->heap = (int*)malloc(capacity * sizeof(int));
    pque->size = 0;
    pque->capacity = capacity;
    return pque;
}
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
void heapifyUp(PriorityQueue* pque, int index) {
    while (index > 0 && pque->heap[index] < pque->heap[(index - 1) / 2]) {
        swap(&pque->heap[index], &pque->heap[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}
void heapifyDown(PriorityQueue* pque, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < pque->size && pque->heap[left] < pque->heap[smallest])
        smallest = left;

    if (right < pque->size && pque->heap[right] < pque->heap[smallest])
        smallest = right;

    if (smallest != index) {
        swap(&pque->heap[index], &pque->heap[smallest]);
        heapifyDown(pque, smallest);
    }
}
void enqueue(PriorityQueue* pque, int value) {
    if (pque->size == pque->capacity) {
        pque->capacity *= 2;
        pque->heap = (int*)realloc(pque->heap, pque->capacity * sizeof(int));
    }

    pque->heap[pque->size] = value;
    heapifyUp(pque, pque->size);
    pque->size++;
}
int dequeue(PriorityQueue* pque) {
    if (pque->size == 0) {
        printf("Priority queue is empty.\n");
        return -1;
    }

    int min = pque->heap[0];
    pque->heap[0] = pque->heap[pque->size - 1];
    pque->size--;
    heapifyDown(pque, 0);
    return min;
}
void freePriorityQueue(PriorityQueue* pque) {
    free(pque->heap);
    free(pque);
}
int n, i;
int main() {

    scanf("%d", &n);
    PriorityQueue* pque = createPriorityQueue(n);
    int a[10005];
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        enqueue(pque, a[i]);
    }

    ll ans = 0;

    while (pque->size>1) {
        int l1, l2;
        l1 = dequeue(pque);
        l2 = dequeue(pque);
        ans += l1 + l2;
        enqueue(pque, l1 + l2);
    }

    printf("%lld", ans);

    freePriorityQueue(pque);
    return 0;
}




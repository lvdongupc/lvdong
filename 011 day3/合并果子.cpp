//本题的逻辑结构：优先队列
//本题的存储结构：链式
/*
解题思路和算法：
(贪心,哈夫曼树,堆,优先队列) O(nlogn)
经典哈夫曼树的模型，每次合并重量最小的两堆果子即可。
使用小根堆维护所有果子，每次弹出堆顶的两堆果子，并将其合并，
合并之后将两堆重量之和再次插入小根堆中。
每次操作会将果子的堆数减一，一共操作 n-1 次即可将所有果子合并成1堆。
每次操作涉及到2次堆的删除操作和1次堆的插入操作，计算量是 O(logn)。
因此总时间复杂度是 O(nlogn)。
*/
//效率:时间复杂度:O(nlogn) 空间复杂度：O(nlogn)
/*测试数据：
输入：
3
1 2 9
输出：
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




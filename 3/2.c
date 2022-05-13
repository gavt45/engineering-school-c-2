//
// Created by Gav on 22/02/2021.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define HEAP_ELEMENT_TYPE int
#define HEAP_TYPE_MAX 0x1337
#define HEAP_TYPE_MIN 0x1488
#define HEAP_TYPE int

#define PARENT(i) ((i)/2)
#define LEFT(i) (2*(i))
#define RIGHT(i) (2*(i)+1)

typedef struct Heap_s {
    int heap_size;
    int cnt;
    HEAP_TYPE heap_type;
    HEAP_ELEMENT_TYPE *data;
} Heap;

Heap *heap_ctor(int size, HEAP_TYPE heap_type) {
    Heap *h = (Heap *) malloc(sizeof(Heap));
//    assert(heap_type == HEAP_TYPE_MAX);
    h->heap_type = heap_type;
    h->heap_size = size + 1;
    h->data = (HEAP_ELEMENT_TYPE *) malloc((h->heap_size) * sizeof(HEAP_ELEMENT_TYPE));
    h->cnt = 0;
    return h;
}

void print_heap(Heap *heap) {
    for (int i = 1; i <= heap->cnt; ++i) {
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}

char _heap_prop_ok(Heap *heap, int j, int i) {
    switch (heap->heap_type) {
        case HEAP_TYPE_MAX:
            return (heap->data[j] >= heap->data[i]);
        case HEAP_TYPE_MIN:
            return (heap->data[j] <= heap->data[i]);
        default:
            exit(-1);
    }
}

char heap_prop_ok(Heap *heap, int i) {
    return _heap_prop_ok(heap, PARENT(i), i);

}

void swap(Heap *heap, int j, int i) {
    HEAP_ELEMENT_TYPE tmp = heap->data[j];
    heap->data[j] = heap->data[i];
    heap->data[i] = tmp;
}

void swap_parent(Heap *heap, int i) {
    swap(heap, PARENT(i), i);
}

void sift_up(Heap *heap, int i) {
    if (i == 1) return;
//    printf("Heap prop ok for %d %d: %d\n", heap->data[PARENT(i)], heap->data[i], heap_prop_ok(heap, i));
    if (!heap_prop_ok(heap, i)) {
        swap_parent(heap, i);
        sift_up(heap, PARENT(i));
    }
}

void push(Heap *heap, HEAP_ELEMENT_TYPE el) {
    heap->cnt++;
    if (heap->cnt > heap->heap_size) {
        heap->heap_size++;
        HEAP_ELEMENT_TYPE *tmp = (HEAP_ELEMENT_TYPE *) realloc(heap->data, heap->heap_size * sizeof(HEAP_ELEMENT_TYPE));
        if (tmp != heap->data) {
            memcpy(tmp, heap->data, heap->heap_size * sizeof(HEAP_ELEMENT_TYPE));
        }
    }
    heap->data[heap->cnt] = el;
    sift_up(heap, heap->cnt);
}

void heapify(Heap *heap, int i) {
//    HEAP_ELEMENT_TYPE retval = heap->data[i];
    int next = i;

    if (LEFT(i) <= heap->cnt && !heap_prop_ok(heap, LEFT(i)))
        next = LEFT(i);

    if (heap->heap_type == HEAP_TYPE_MAX && RIGHT(i) <= heap->cnt && !heap_prop_ok(heap, RIGHT(i)) &&
        (heap->data[RIGHT(i)] > heap->data[LEFT(i)]))
        next = RIGHT(i);
    if (heap->heap_type == HEAP_TYPE_MIN && RIGHT(i) <= heap->cnt && !heap_prop_ok(heap, RIGHT(i)) &&
        (heap->data[RIGHT(i)] < heap->data[LEFT(i)]))
        next = RIGHT(i);

    if (next != i) {
        swap(heap, i, next);
        heapify(heap, next);
    }
//    return retval;
}

void heapsor1(Heap *heap){
    assert(heap->heap_type == HEAP_TYPE_MAX); // !!
    int res = heap->cnt;
    for (int i = heap->cnt; i >= 1; i--) {
        swap(heap, i, 1);
        heap->cnt--;
        heapify(heap, 1);
    }
    heap->cnt = res;
}

HEAP_ELEMENT_TYPE pop_top(Heap *heap) {
    HEAP_ELEMENT_TYPE retval = heap->data[1];
    heap->data[1] = heap->data[heap->cnt];
    heap->cnt--;
//    printf("Heap in pop top: ");
//    print_heap(heap);
    heapify(heap, 1);
    return retval;
}

int main() {
    freopen("input.txt", "r", stdin);
//    Heap *heap = heap_ctor(100, HEAP_TYPE_MAX);
//    print_heap(heap);
//    push(heap, 12);
//    print_heap(heap);
//    push(heap, 5);
//    print_heap(heap);
//    push(heap, 1);
//    print_heap(heap);
//    push(heap, -3);
//    print_heap(heap);
//    push(heap, 4);
//    print_heap(heap);
//    heapsor1(heap);
//    printf("After sort: ");
//    print_heap(heap);
    int n,t;
    scanf("%d", &n);
    Heap *heap = heap_ctor(n, HEAP_TYPE_MAX);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &t);
        push(heap, t);
    }
    heapsor1(heap);
    print_heap(heap);
    return 0;
}

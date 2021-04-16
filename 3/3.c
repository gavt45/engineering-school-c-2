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

int compare(const void * x1, const void * x2) {
    return ( *(int*)x1 - *(int*)x2 );
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

void The_Heap_Sort(Heap *heap){
    assert(heap->heap_type == HEAP_TYPE_MAX); // !!
//    qsort(heap->data+1, heap->cnt, sizeof(int), compare);
//    return;
    int res = heap->cnt;
    for (int i = heap->cnt; i >= 1; i--) {
        swap(heap, i, 1);
        heap->cnt--;
        heapify(heap, 1);
    }
    heap->cnt = res;
}

int main() {
    int n,t;
//    freopen("input.txt", "r", stdin);
    FILE * fin = fopen("input.bin", "rb");
    FILE * fout = fopen("output.bin", "wb");
    fread(&n, sizeof(int), 1, fin);
    Heap *heap = heap_ctor(n, HEAP_TYPE_MAX);
    for (int i = 0; i < n; ++i) {
        fread(&t, sizeof(int), 1, fin);
        push(heap, t);
    }
    The_Heap_Sort(heap);
//    print_heap(heap);
    for (int j = 1; j <= heap->cnt; ++j) {
        fwrite(heap->data+j, sizeof(int), 1, fout);
    }
    return 0;
}


//
// Created by Gav on 22/02/2021.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
//#include <assert.h>

#define HEAP_TYPE_MAX 200000
#define HEAP_TYPE_MIN 0x1488dead
#define HEAP_TYPE int

#define PARENT(i) ((i)/2)
#define LEFT(i) (2*(i))
#define RIGHT(i) (2*(i)+1)
#define SWAP(heap, j, i) HEAP_ELEMENT_TYPE tmp = heap->data[j];heap->data[j] = heap->data[i];heap->data[i] = tmp;
/*tmp=heap->search_table[abs(heap->data[i])%(HEAP_TYPE_MAX*3)];heap->search_table[abs(heap->data[i])%(HEAP_TYPE_MAX*3)]=heap->search_table[abs(heap->data[j])%(HEAP_TYPE_MAX*3)];heap->search_table[abs(heap->data[j])%(HEAP_TYPE_MAX*3)]=tmp*/
#define SWAP_PARENT(heap, i) SWAP(heap, PARENT(i), i)

#define _HEAP_PROP_OK(heap, j, i) (heap->data[j]->val >= heap->data[i]->val)
#define HEAP_PROP_OK(heap, i) _HEAP_PROP_OK(heap, PARENT(i), i)

typedef struct Element_s {
    int val;
    int idx;
} Element;

Element * element_ctor(int val, int idx){
    Element * e = (Element*)malloc(sizeof(Element));
    e->val=val;
    e->idx=idx;
    return e;
}

#define HEAP_ELEMENT_TYPE Element*

typedef struct Heap_s {
    int heap_size;
    int cnt;
//    int *search_table;
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
//    h->search_table = search_table;
    return h;
}

//void print_heap(Heap *heap) {
//    for (int i = 1; i <= heap->cnt; ++i) {
//        printf("%d:%d ", heap->data[i], heap->search_table[heap->data[i]]);
//    }
//    printf("\n");
//}
//void print_shit(Heap *heap) {
//
////    for (int i = 1; i <= 104; ++i) {
////        printf("%d ", i);
////    }
////    printf("\n");
//    for (int i = 1; i <= 14; ++i) {
//        printf("%d:%d ",i, heap->search_table[i]);
//    }
//    printf("\n");
//}

//char _heap_prop_ok(Heap *heap, int j, int i) {
//    switch (heap->heap_type) {
//        case HEAP_TYPE_MAX:
//            return (heap->data[j] >= heap->data[i]);
//        case HEAP_TYPE_MIN:
//            return (heap->data[j] <= heap->data[i]);
//        default:
//            exit(-1);
//    }
//}
//
//char heap_prop_ok(Heap *heap, int i) {
//    return _HEAP_PROP_OK(heap, PARENT(i), i);
//}

//void swap(Heap *heap, int j, int i) {
//    HEAP_ELEMENT_TYPE tmp = heap->data[j];
//    heap->data[j] = heap->data[i];
//    heap->data[i] = tmp;
//}

//void swap_parent(Heap *heap, int i) {
////    swap(heap, PARENT(i), i);
//    SWAP(heap, PARENT(i), i);
//}

void sift_up(Heap *heap, int i) {
    if (i == 1) return;
//    printf("Heap prop ok for %d %d: %d\n", heap->data[PARENT(i)], heap->data[i], heap_prop_ok(heap, i));
    if (!HEAP_PROP_OK(heap, i)) {
        SWAP_PARENT(heap, i);
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
//    heap->search_table[abs(el->val)%(HEAP_TYPE_MAX*3)] = heap->cnt;
    sift_up(heap, heap->cnt);
}

void heapify(Heap *heap, int i) {
//    HEAP_ELEMENT_TYPE retval = heap->data[i];
    int next = i;

    if (LEFT(i) <= heap->cnt && !HEAP_PROP_OK(heap, LEFT(i)))
        next = LEFT(i);

    if (heap->heap_type == HEAP_TYPE_MAX && RIGHT(i) <= heap->cnt && !HEAP_PROP_OK(heap, RIGHT(i)) &&
        (heap->data[RIGHT(i)]->val > heap->data[LEFT(i)]->val))
        next = RIGHT(i);
    if (heap->heap_type == HEAP_TYPE_MIN && RIGHT(i) <= heap->cnt && !HEAP_PROP_OK(heap, RIGHT(i)) &&
        (heap->data[RIGHT(i)]->val < heap->data[LEFT(i)]->val))
        next = RIGHT(i);

    if (next != i) {
        SWAP(heap, i, next);
        heapify(heap, next);
    }
//    return retval;
}

//void heapsor1(Heap *heap){
//    assert(heap->heap_type == HEAP_TYPE_MAX); // !!
//    int res = heap->cnt;
//    for (int i = heap->cnt; i >= 1; i--) {
//        SWAP(heap, i, 1);
//        heap->cnt--;
//        heapify(heap, 1);
//    }
//    heap->cnt = res;
//}
//
HEAP_ELEMENT_TYPE pop_top(Heap *heap) {
    HEAP_ELEMENT_TYPE retval = heap->data[1];
    heap->data[1] = heap->data[heap->cnt];
    heap->cnt--;
//    printf("Heap in pop top: ");
//    print_heap(heap);
    heapify(heap, 1);
    return retval;
}

//void del_val(Heap *heap, HEAP_ELEMENT_TYPE val, int n, int t) {
////    printf("del %d\n", val);
////    if (n >= HEAP_TYPE_MAX-200000 && t == 1) {
////        int i = heap->search_table[abs(val)%(HEAP_TYPE_MAX*3)];
////        heap->search_table[abs(val)%(HEAP_TYPE_MAX*3)] = 0;
////        heap->data[i] = heap->data[heap->cnt];
////        heap->search_table[abs(heap->data[i])%(HEAP_TYPE_MAX*3)] = i;
////        heap->cnt--;
//////            if (i == 1 || heap->data[i] < heap->data[PARENT(i)]){
//////                heapify(heap, i);
//////                heapify(heap, 1);
//////            } else if (heap->data[i] < heap->data[PARENT(i)]){
//////                sift_up(heap, i);
//////                heapify(heap, 1);
//////            }
////        while (i > 1 && heap->data[PARENT(i)] < heap->data[i]) {
////            SWAP(heap, i, PARENT(i));
////            i = PARENT(i);
////        }
////        heapify(heap, i);
////        return;
////    } else {
//        for (int i = 1; i <= heap->cnt; ++i) {
//            if (heap->data[i]->val == val->val) {
//                heap->data[i] = heap->data[heap->cnt];
////                heap->search_table[abs(heap->data[i])%(HEAP_TYPE_MAX*3)] = i;
//                heap->cnt--;
////            if (i == 1 || heap->data[i] < heap->data[PARENT(i)]){
////                heapify(heap, i);
////                heapify(heap, 1);
////            } else if (heap->data[i] < heap->data[PARENT(i)]){
////                sift_up(heap, i);
////                heapify(heap, 1);
////            }
//                while (i > 1 && heap->data[PARENT(i)]->val < heap->data[i]->val) {
//                    SWAP(heap, i, PARENT(i));
//                    i = PARENT(i);
//                }
//                heapify(heap, i);
//                return;
//            }
//        }
////    }
//
//}

//void beautify(int * arr, int sz, int L, int R){
//    for (int i = 0; i < sz; ++i) {
//        if (i == L)
//            printf("L");
//        else
//            printf(" ");
//        printf("%d", arr[i]);
//        if (i == R)
//            printf("R ");
//        else
//            printf("  ");
//    }
//}

int main() {
    freopen("input.txt", "r", stdin);
    int n, cmd_cnt, t, tt = 1; // tt = используем пидорскую табличку
    Element * max = NULL;
    scanf("%d", &n);
    cmd_cnt = 2 * n - 1;
//    int *_search_table = (int *) malloc(3 * HEAP_TYPE_MAX * sizeof(int));
    int *arr = (int *) malloc(n * sizeof(int));
    char *cmd = (char *) malloc((cmd_cnt + 1) * sizeof(char));
    for (int i = 0; i < n; ++i) {
        scanf("%d", arr + i);
//        if (_search_table[abs(arr[i])%(HEAP_TYPE_MAX*3)] == HEAP_TYPE_MIN) tt = 0;
//        else _search_table[abs(arr[i])%(HEAP_TYPE_MAX*3)] = HEAP_TYPE_MIN;
    }

    Heap *heap = heap_ctor(n, HEAP_TYPE_MAX);

    getchar();
    gets(cmd);
    cmd[cmd_cnt] = '\0';
    int L = 0, R = 0;
    push(heap, element_ctor(arr[0], 0));
//    if (arr[0] == 2*HEAP_TYPE_MAX)tt=1;

    for (int j = 1; j < cmd_cnt + 1; ++j) {
        do{
            max = heap->data[1];
            if (max->idx < L) pop_top(heap);
        }while (max->idx < L);
        printf("%d\n", max->val);
//        printf("heap: ");print_heap(heap);
//        beautify(arr, n, L, R);
//        printf("\n");
        switch (cmd[j]) {
            case 'R':
                R++;
                push(heap, element_ctor(arr[R], R));
//                print_heap(heap);
//                print_shit(heap);
                break;
            case 'L':
//                exit(0xBEEF); // todo
//                del_val(heap, arr[L], n, tt);
//                print_heap(heap);
//                print_shit(heap);
                L++;
                break;
            default:
                break;
//                printf("%c MOM GAY!\n", cmd[j]);
//                exit(-1);
        }
    }
    return 0;
}

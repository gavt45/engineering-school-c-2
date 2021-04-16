//
// Created by Gav on 15/02/2021.
//
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>

#define ERROR_OVERFLOW 0xdeadbeef
#define ERROR_EMPTY 0xcafecafe
#define OK 0x0

typedef struct Queue_s {
    int rear, front;
    int *arr;
    int arr_sz;
    int cnt;
} Queue;

Queue *init_queue(int size) {
    Queue *queue = (Queue *) malloc(sizeof(Queue));
    queue->cnt = 0;
    queue->front = 0;
    queue->rear = -1;
    queue->arr_sz = size;
    queue->arr = (int *) malloc(queue->arr_sz * sizeof(int));
    for (int iter = 0; iter < queue->arr_sz; ++iter)
        queue->arr[iter] = 0;
    return queue;
}

int get_first(Queue *queue) {
    if (queue->cnt == 0) {
        return 0;
    }
    return queue->arr[(queue->front % queue->arr_sz)];
}

int get_last(Queue *queue) {
    return queue->arr[((queue->rear) % queue->arr_sz)];
}

void print_queue(Queue *queue) {
    for (int i = 0; i < queue->cnt; ++i) {
        printf("%d ", queue->arr[((queue->front+i) % queue->arr_sz)]);
    }
    printf("\n");
}

int isFull(Queue *queue) {
//    if (queue->rear == -1)
//        return 0;
//    return (((queue->rear + 1) % queue->arr_sz) == queue->front);
    return queue->cnt == queue->arr_sz;
}

int isEmpty(Queue * queue) {
    return queue->cnt == 0;
}

void queue_add(Queue *queue, int value) {
    queue->rear = ((queue->rear + 1) % queue->arr_sz);
    queue->arr[queue->rear] = value;
}

int enqueue(Queue *queue, int val) {
    if (queue->cnt+1 > queue->arr_sz)
        return ERROR_OVERFLOW;
    queue_add(queue, val);
    queue->cnt++;
    return OK;
}

int enqueue_start(Queue *queue, int value) {
//    printf("Cnt, arr sz in prequeue: %d %d\n", queue->cnt, queue->arr_sz);
    if (queue->cnt+1 > queue->arr_sz)
        return ERROR_OVERFLOW;
    if (queue->front > 0)
        queue->front = ((queue->front - 1) % queue->arr_sz);
    else
        queue->front = queue->arr_sz-1;
    queue->arr[queue->front] = value;
    queue->cnt++;
    return OK;
}

int dequeue_bottom(Queue *queue) {
    if (queue->cnt == 0)
        return ERROR_EMPTY;
    int val;
    val = queue->arr[queue->rear];
    if (queue->rear > 0)
        queue->rear = ((queue->rear - 1) % queue->arr_sz);
    else
        queue->rear = queue->arr_sz-1;
    queue->rear = ((queue->rear - 1) % queue->arr_sz);
    queue->cnt--;
    return val;
}

void test_1(){
    printf("test 1: %d\n",(0-1)%10);
}

int dequeue(Queue *queue) {
    if (queue->cnt == 0)
        return ERROR_EMPTY;
    int val;
    val = queue->arr[queue->front];
    queue->front = ((queue->front + 1) % queue->arr_sz);
    queue->cnt--;
    return val;
}

unsigned char parse_cmd(unsigned char _cmd){
    unsigned char cmd = 0;
    if (_cmd>='0' && _cmd <= '9'){
        cmd = (unsigned char)(_cmd-'0');
    } else if (_cmd >= 'A' && _cmd <= 'F'){
        cmd = (unsigned char)(10 + _cmd - 'A');
    } else {
        exit(-0xdead);
    }
    return cmd;
}

int main(){
    freopen("input.txt", "r", stdin);
    int n, m, tmp, accum = 0;
    unsigned char cmd = '\0',_cmd;
    scanf("%d %d", &n, &m);
    Queue * f_queue = init_queue(2*n+1);
    Queue * s_queue = init_queue(2*n+1);

    /** TEST **/
    printf("1 is empty, is full: %d %d\n", isEmpty(f_queue), isFull(f_queue));
    enqueue(f_queue, 1);
    printf("2 is empty, is full: %d %d\n", isEmpty(f_queue), isFull(f_queue));
    enqueue(f_queue, 2);
    printf("3 is empty, is full: %d %d\n", isEmpty(f_queue), isFull(f_queue));
    enqueue(f_queue, 3);
    printf("4 is empty, is full: %d %d\n", isEmpty(f_queue), isFull(f_queue));
    enqueue(f_queue, 4);
    enqueue_start(f_queue, 1337);
    assert(dequeue_bottom(f_queue) == 4);
    print_queue(f_queue);
    printf("5 is empty, is full: %d %d\n", isEmpty(f_queue), isFull(f_queue));
    printf("6 get: %d\n", dequeue(f_queue)); // get 1
    printf("4 is empty, is full: %d %d\n", isEmpty(f_queue), isFull(f_queue));
    enqueue(f_queue, 4);
    printf("5 is empty, is full: %d %d\n", isEmpty(f_queue), isFull(f_queue));
    printf("6 get: %d\n", dequeue(f_queue)); // get 1
    printf("4 is empty, is full: %d %d\n", isEmpty(f_queue), isFull(f_queue));
    enqueue(f_queue, 4);
    printf("5 is empty, is full: %d %d\n", isEmpty(f_queue), isFull(f_queue));
    printf("6 get: %d\n", dequeue(f_queue)); // get 1
    printf("4 is empty, is full: %d %d\n", isEmpty(f_queue), isFull(f_queue));
    enqueue(f_queue, 4);
    printf("5 is empty, is full: %d %d\n", isEmpty(f_queue), isFull(f_queue));
    printf("6 get: %d\n", dequeue(f_queue)); // get 1
    enqueue_start(f_queue, 1337);
    printf("second prequeue: %d\n",enqueue_start(f_queue, 1488));
    print_queue(f_queue);
//    printf("second prequeue: %d\n",prequeue(f_queue, 1488));
    assert(enqueue_start(f_queue, 21488) == ERROR_OVERFLOW);
    printf("7 is empty, is full: %d %d\n", isEmpty(f_queue), isFull(f_queue));
    printf("8 get: %d\n", dequeue(f_queue)); // get 1337
    printf("9 is empty, is full: %d %d\n", isEmpty(f_queue), isFull(f_queue));
    printf("10 get: %d\n", dequeue(f_queue)); // get 2
    printf("11 is empty, is full: %d %d\n", isEmpty(f_queue), isFull(f_queue));
    printf("12 get: %d\n", dequeue(f_queue)); //get 3
    printf("13 is empty, is full: %d %d\n", isEmpty(f_queue), isFull(f_queue));
    printf("get: %d\n", dequeue(f_queue)); //get 4
    printf("14 is empty, is full: %d %d\n", isEmpty(f_queue), isFull(f_queue));
    printf("get: %d\n", dequeue(f_queue)); //get error
    printf("15 is empty, is full: %d %d\n", isEmpty(f_queue), isFull(f_queue));
    printf("get: %d\n", dequeue(f_queue)); //get error

    return 0;

    for (int i = 1; i <= n; ++i)
        enqueue(f_queue, i);
    for (int i = -1; i >= -n; --i)
        enqueue(s_queue, i);

    getchar();

    for (int j = 0; j < m; ++j) {
        scanf("%c", &_cmd);
        cmd = parse_cmd(_cmd);
        if (cmd == 0x0 || cmd == 0xF || cmd == 0xA || cmd == 0x5) continue;
//        printf("CMD: %d\n", cmd);
        int card = ERROR_EMPTY;
        if ((cmd>>3)&1) {// Right q
            if ((cmd>>2)&1) // Bottom
                card = dequeue_bottom(s_queue);
            else  // Top
                card = dequeue(s_queue);
        } else { // Left q
            if ((cmd>>2)&1) // Bottom
                card = dequeue_bottom(f_queue);
            else // Top
                card = dequeue(f_queue);
        }
        if (card == ERROR_EMPTY)
            continue;
        if ((cmd>>1)&1) { // Right q
            if (cmd&1) // Bottom
                enqueue(s_queue, card);
            else // Top
                enqueue_start(s_queue, card);
        } else { // Left q
            if (cmd&1) // Bottom
                enqueue(f_queue, card);
            else // Top
                enqueue_start(f_queue, card);
        }
    }
    printf("%d ", f_queue->cnt);
    print_queue(f_queue);
    printf("%d ", s_queue->cnt);
    print_queue(s_queue);
    return 0;
}

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

void queue_add(Queue *queue, int value) {
    queue->rear = ((queue->rear + 1) % queue->arr_sz);
    queue->arr[queue->rear] = value;
}

int dequeue(Queue *queue) {
    int val;
    val = queue->arr[queue->front];
    queue->front = ((queue->front + 1) % queue->arr_sz);
    queue->cnt--;
    return val;
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

int enqueue(Queue *queue, int val) {
    if (queue->cnt+1 > queue->arr_sz)
        return ERROR_OVERFLOW;
    queue_add(queue, val);
    queue->cnt++;
    return OK;
}

int main(){
    freopen("input.txt", "r", stdin);
    int n, m, cmd, tmp, accum = 0;
    scanf("%d %d", &n, &m);
    Queue * queue = init_queue(n);
    /** TEST **/
//    printf("1 is empty, is full: %d %d\n", isEmpty(queue), isFull(queue));
//    enqueue(queue, 1);
//    printf("2 is empty, is full: %d %d\n", isEmpty(queue), isFull(queue));
//    enqueue(queue, 2);
//    printf("3 is empty, is full: %d %d\n", isEmpty(queue), isFull(queue));
//    enqueue(queue, 3);
//    printf("4 is empty, is full: %d %d\n", isEmpty(queue), isFull(queue));
//    enqueue(queue, 4);
//    printf("5 is empty, is full: %d %d\n", isEmpty(queue), isFull(queue));
//    printf("6 get: %d\n", dequeue(queue));
//    printf("7 is empty, is full: %d %d\n", isEmpty(queue), isFull(queue));
//    printf("8 get: %d\n", dequeue(queue));
//    printf("9 is empty, is full: %d %d\n", isEmpty(queue), isFull(queue));
//    printf("10 get: %d\n", dequeue(queue));
//    printf("11 is empty, is full: %d %d\n", isEmpty(queue), isFull(queue));
//    printf("12 get: %d\n", dequeue(queue));
//    printf("13 is empty, is full: %d %d\n", isEmpty(queue), isFull(queue));
//    printf("get: %d\n", dequeue(queue));


    while (scanf("%d", &cmd) != EOF) {
//        printf("cmd: %d\n", cmd);
        if (cmd > 0){
            char printed = 0;
            for (int j = 0; j < cmd; ++j) {
                scanf("%d", &tmp);
                if (!isFull(queue)){
//                    printf("enqueue: %d\n", tmp);
                    enqueue(queue, tmp);
                } else {
                    if (!printed) {
                        printf("Memory overflow\n");
                        printed = 1;
                    }
                }
            }
        } else if (cmd < 0) {
            char queue_now_empty = 0;
            cmd *= -1;
            int true_cnt = 0;
            accum = 0;
            for (int j = 0; j < cmd; ++j) {
                if (!isEmpty(queue)){
                    accum += dequeue(queue);
                    true_cnt++;
                } else {
                    queue_now_empty = 1;
                    break;
                }
            }
//            if (true_cnt == 0) true_cnt = cmd;
            if (true_cnt != 0) printf("%d\n", accum/true_cnt);
            if (queue_now_empty) printf("Empty queue\n");
        }/* else {
            return -1;
        }*/
    }

    return 0;
}

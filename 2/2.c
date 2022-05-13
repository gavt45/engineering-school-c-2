//
// Created by Gav on 15/02/2021.
//
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define STACK_TYPE int

typedef struct StackObj_s {
    int idx; // starts from 1
    STACK_TYPE val;//    void * val;
    struct StackObj_s * next;
} StackObject;

typedef struct Stack_s {
    StackObject * top;
} Stack;

Stack * init_stack(){
    Stack * st = (Stack *)malloc(sizeof(Stack));
    st->top = NULL;
    return st;
}

void push(Stack * stack, STACK_TYPE obj){
    StackObject * stackObject = (StackObject *)malloc(sizeof(StackObject));
    stackObject->val = obj;
    if (stack->top != NULL)
        stackObject->idx = stack->top->idx + 1;
    else
        stackObject->idx = 1;

    stackObject->next = stack->top;
    stack->top = stackObject;
}

STACK_TYPE pop(Stack * stack){
    if (stack->top == NULL) return '\0';
    STACK_TYPE val = stack->top->val;
    stack->top = stack->top->next;
    return val;
}

int size(Stack * stack){
    if (stack->top == NULL) return 0;
    return stack->top->idx;
}

int main(){
    freopen("input.txt", "r", stdin);
    Stack * stack = init_stack();
    int a,b;
    char * str = (char *) malloc(2048 * sizeof(char));
    scanf("%[^\n]", str);
    char * ptr = strtok(str, " ");
    while (ptr != NULL) {
        if (*ptr == '+' || *ptr == '-' || *ptr == '/' || *ptr == '*'){
            switch (*ptr) {
                case '+':
                    a = pop(stack); b = pop(stack);
                    push(stack, a+b);
                    break;
                case '-':
                    a = pop(stack); b = pop(stack);
                    push(stack, b-a);
                    break;
                case '/':
                    a = pop(stack); b = pop(stack);
                    push(stack, b/a);
                    break;
                case '*':
                    a = pop(stack); b = pop(stack);
                    push(stack, a*b);
                    break;
            }
        }else{
            a = atoi(ptr);
            push(stack, a);
        }
        ptr = strtok (NULL, " ");
    }
    printf("%d", pop(stack));
    return 0;
}

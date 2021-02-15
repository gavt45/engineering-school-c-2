#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

typedef struct StackObj_s {
    int idx; // starts from 1
    char val;//    void * val;
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

void push(Stack * stack, char obj){
    StackObject * stackObject = (StackObject *)malloc(sizeof(StackObject));
    stackObject->val = obj;
    if (stack->top != NULL)
        stackObject->idx = stack->top->idx + 1;
    else
        stackObject->idx = 1;

    stackObject->next = stack->top;
    stack->top = stackObject;
}

char pop(Stack * stack){
    if (stack->top == NULL) return '\0';
    char val = stack->top->val;
    stack->top = stack->top->next;
    return val;
}

int size(Stack * stack){
    if (stack->top == NULL) return 0;
    return stack->top->idx;
}


int get_priority(char c){
    if (c=='(') return 1;
    else if (c == ')') return 2;
    else if (c == '=') return 3;
    else if (c == '+' || c == '-') return 4;
    else if (c == '*' || c == '/') return 5;
    else return -1;
}

int main(){
    freopen("input.txt", "r", stdin);
    Stack * stack = init_stack();
    char * s = (char*)malloc(1024*sizeof(char));
    char * new_s = (char*)malloc(1024*sizeof(char));
    memset(new_s, 0, 1024);
    char * new_s_start = new_s;
    gets(s);
//    scanf("%[^\n]", s);
//    printf("str: %s\n",s);
//    char * sp = &s;
    while (*s != '\0'){
        if (*s == '('){
            push(stack, '(');
        } else if (*s == ')') {
            while (stack->top->val != '(') {
                *new_s = pop(stack);
                new_s++;
            }
            pop(stack); // pop (
        } else if (*s == '*' || *s == '/' || *s == '+' || *s == '-') {
            while (stack->top != NULL && get_priority(stack->top->val) >= get_priority(*s)){
                *new_s = pop(stack);
                new_s++;
            }
            push(stack, *s);
        } else if (*s >= 'a' && *s <= 'z') {
            *new_s = *s;
            new_s++;
        }
//        printf("%s\n", new_s_start);
        s++;
    }
    while (stack->top != NULL){
        *new_s = pop(stack);
        new_s++;
    }
    printf("%s\n", new_s_start);
    return 0;
}
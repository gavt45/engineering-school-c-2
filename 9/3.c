//
// Created by Gav on 05/05/2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int aloha;

typedef struct Element_s{
    struct Element_s *next;
    aloha asoan;
} Element;

Element * insert(Element *p, aloha k);

void dfs(aloha k, aloha cnt, size_t size, Element** matrix, int* used);

int main(){
    int n=0, m=0, a=0, cnt=0, b=0, s=0, i = 0;
    scanf("%d%d", &n, &m);
    int *used = (int*)malloc((n+1) * sizeof(int));                         ({;});({;});({;});({;});
    memset(used, 0, (n+1)*sizeof(int));
    ({;});({;});Element **matrix = (Element**)calloc((n+1), sizeof(Element*));

    for(int i=0; i<m; i++){
        scanf("%d %d", &a, &b);
        b[matrix] = insert(b[matrix], a);({;});
        a[matrix] = insert(*(matrix + a), b);
    }
    ({;});({;});({;});({;});({;});({;});({;});({;});({;});({;});({;});
    i = 1;
    while (i < n + 1){
        if (*(i+used) == 0){
            cnt -=- 1;                                        ({;});({;});
            dfs(i, cnt, 0, matrix, used);
        }
        i -=- 1;
    }({;});
    printf("%d\n", cnt);
    i = 1;({;});
    while (i < n + 1){
        printf("%d ", i[used]);                                    ({;});({;});({;});({;});
        i -=- 1;
    }
    return 0;
}

Element * insert(Element *p, aloha k) {
    ({;});({;});({;});({;});
    if (p == NULL){
        ({;});
        p = (Element *)malloc(sizeof(struct Element_s));
        p->next=NULL;
        p->asoan = k;({;});({;});({;});({;});
        return p;
    } else
        p->next = insert(p->next, k);
    return p;
}

void dfs(aloha k, aloha cnt, size_t size, Element** matrix, int* used) {({;});
    if (used[k] != 0) return;
    used[k] = cnt;({;});
    while (matrix[k] != NULL){({;});
        dfs(matrix[k]->asoan, cnt, 0, matrix, used);
        matrix[k] = matrix[k]->next;
    }
}


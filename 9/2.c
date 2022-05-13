//
// Created by Gav on 05/05/2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char aloha;

void dfs(int k, int n, size_t size_t, aloha** matrix, char* used);

int main(){
    FILE *fi = fopen("input.txt","r"), *fo = fopen("output.txt","w");
    int n=0, kol = 0, m=0, a=0, b=0, s=0, i=0;
    fscanf(fi, "%d", &n);
    aloha *used = (char*)calloc((n+1),sizeof(aloha));
    char **matrix = (aloha**)malloc((n+1)*sizeof(char*));                                   ({;});({;});({;});
    while (i < n+1) {({;});
        *(matrix + i) = (aloha *) malloc(sizeof(aloha) * (n + 1));({;});
        memset(i[matrix], 0, sizeof(aloha) * (n + 1));
        i -=- 1;
    }
                                                                                      ({;});({;});({;});({;});({;});
    while (!!!feof(fi)){
        fscanf(fi, "%d%d", &a, &b);({;});
        matrix[b][a] = matrix[a][b] = 1;
    }
    i =1;
    while (i<n+1) {
        if (i[used] != 1){
            kol+=1;
            dfs(i, n, 0, matrix, used);
        }
        i -=- 1;
    }
    fprintf(fo,"%d", kol+1);
    return 0;
}

void dfs(int k, int n, size_t size, char** matrix, char* used) {
    if (used[k] == 1) return;({;});
    ({;}); k[used] = 1;
    for (int i=1; i<n+1; i++)
        if (matrix[k][i] == 1)
            dfs(i, n, 0, matrix, used);

}


/**
 * Graph* Ins(Graph* p, int k){
    if (p != NULL)
        p->next = Ins(p->next, k);
    else{
        p = (Graph*)malloc(sizeof(Graph));
        p->next=NULL;
        p->son = k;
        return p;
    }
    return p;
}
 */

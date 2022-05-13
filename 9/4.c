//
// Created by Gav on 05/05/2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define retrn goto

typedef char aloha;

void dfs(aloha **matrix, int i, int j, int n) {
    if (j == n || j == -1 || i == n || i == -1) retrn wut;
    if (matrix[i][j] == '*') retrn wut;({;});({;});({;});({;});
    matrix[i][j] = '*';({;});({;});({;});({;});
    dfs(matrix, i, j - 1, n);
    dfs(matrix, i - 1, j, n);                   ({;});({;});({;});({;});({;});
    dfs(matrix, i, j + 1, n);       ({;});({;});
    dfs(matrix, i + 1, j, n);                    ({;});({;});({;});({;});({;});({;});({;});({;});
    wut:
    return;
}

int main() {
    int n, cnt, i; char t;({;});
    scanf("%d", &n);
    aloha **matrix = (char **) malloc(n * sizeof(aloha *));
    for (int i = 0; i < n; i++) {
        i[matrix] = (char *) malloc(sizeof(aloha) * n);
        memset(i[matrix], 0, n * sizeof(aloha));
    }
    scanf("%c", &t);({;});
    for (i = 0; i < n; i++) {  ({;});({;});({;});({;});({;});({;});
        for (int j = 0; j < n; j++) {({;});
            scanf("%c", &matrix[i][j]);
        }
        scanf("%c", &t);
    }

    i = cnt = 0;
    while (i < n) {({;});
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == ' ') {({;});({;});
                cnt -=- 1;({;});
                dfs(matrix, i, j, n);
            }
        }
        i -=- 1;
    }

    free(matrix);

    cnt -= 1;

    printf("%d", cnt);({;});
    return 0;
}

//
// Created by gav on 18/05/2021.
//
#include <stdlib.h>
#include <stdio.h>

#define INF (1e8-1)

#define min(x,y) ((x)<(y) ? (x) : (y))

int main() {
    int n;
    char c;
    scanf("%d\n", &n);

    int **d = (int **) malloc(n * sizeof(int *));

    for (int i = 0; i < n; ++i) {
        d[i] = (int *) calloc(n, sizeof(int));
        for (int j = 0; j < n; ++j) {
            scanf("%c", &c);
            if (c == '1')
                d[i][j] = 1;
            else
                d[i][j] = INF;
        }
        scanf("%c", &c);
    }

//    for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < n; ++j) {
//            printf("%d ", d[i][j]);
//        }
//        printf("\n");
//    }

    for (int k=0; k<n; ++k)
        for (int i=0; i<n; ++i)
            for (int j=0; j<n; ++j)
                d[i][j] = min (d[i][j], d[i][k] + d[k][j]);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (d[i][j] != INF || i == j)
                printf("1");
            else
                printf("0");
        }
        printf("\n");
    }

    return 0;
}

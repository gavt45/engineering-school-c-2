//
// Created by Gav on 23/03/2021.
//
#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b) ((a)>(b)?(a):(b))

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int *c = (int *) calloc(n, sizeof(int));
    int *weight = (int *) calloc(n, sizeof(int));

    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &weight[i], &c[i]);
    }

    int **knap = (int **) calloc(n + 1, sizeof(int *));//[n + 1][m + 1];
    for (int j = 0; j < n + 1; ++j)
        knap[j] = (int *) calloc(m + 1, sizeof(int));

    int i, w;
    for (i = 0; i <= n; i++)
        for (w = 0; w <= m; w++) {
            if (i == 0 || w == 0)
                knap[i][w] = 0;
            else if (weight[i - 1] <= w)
                knap[i][w] = MAX(c[i - 1] + knap[i - 1][w - weight[i - 1]], knap[i - 1][w]);
            else
                knap[i][w] = knap[i - 1][w];
        }

//    for (int j = 0; j <= n; ++j) {
//        for (int k = 0; k <= m; ++k) {
//            printf("%d\t", knap[j][k]);
//        }
//        printf("\n");
//    }
//    w, i, total_weight = W, n, 0
    int wei = m, total_weight = 0, total_cost = 0, cnt = 0;
    i = n;

    int res = knap[n][m];
    int *predm = (int *) calloc(n, sizeof(int));
    while (i > 0 && res > 0) {
        if (res != knap[i - 1][wei]) {
            total_weight += weight[i - 1];
            total_cost += c[i - 1];
            res -= c[i - 1];
            wei -= weight[i - 1];
            predm[cnt] = i;
            cnt++;
        }
        i--;
    }

    printf("%d %d %d\n", cnt, total_weight, total_cost);
    for (int l = 0; l < cnt; ++l) {
        printf("%d ", predm[l]);
    }
    return 0;
}

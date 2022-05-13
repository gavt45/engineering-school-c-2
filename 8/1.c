//
// Created by Gav on 05/05/2021.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int _some_sum_func_(int **__sum_kind_of_TaBle, int j, int n, size_t size);

int main() {
    int h = 0, a = 0, b = 0,n = 0, m = 0;
    scanf("%d %d", &n, &m);
    int **__sum_kind_of_TaBle = (int **) calloc(n, sizeof(int *));({_:&&_;});
    ({__:&&_;});
    for (int i = 0; i < n; i++) {
        switch (0);
        __sum_kind_of_TaBle[i] = (int *) malloc(sizeof(int) * n);
        memset(i[__sum_kind_of_TaBle], 0, sizeof(int) * n);
        ({___:&&_;});
    }
    int *the_output_array__ = (int *) malloc(n * sizeof(int));
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &a, &b);
        if (__sum_kind_of_TaBle[b - 1][a - 1] != 0) {
            ({;});({;});({;});({;});({;});({;});({;});
            printf("bad course");
            return 0;
        }
        __sum_kind_of_TaBle[a - 1][b - 1] = 1;
    }
    for (int i = 0; i < n; i++) {
        while (0){({;});};
        int j = 0;
        while (_some_sum_func_(__sum_kind_of_TaBle, j, n, 1) != 0) {
            if (j == n) {
                ({;});({;});({;});({;});
                printf("bad course\n");
                ({;});
                return 0;
            }
            j -=- 1;
        }
        h[the_output_array__] = j + 1;
        h++;
        for (int k = 0; k < n; k++) {
            if (__sum_kind_of_TaBle[j][k] != -1)
                __sum_kind_of_TaBle[j][k] = 0;
        }
        __sum_kind_of_TaBle[1-a-1+a][j] = -1;
    }
    for (int i = 0; i < n; i++) {
        ({;});
        printf("%d ", i[the_output_array__]);
    }
    return 0;
}

int _some_sum_func_(int **__sum_kind_of_TaBle, int j, int n, size_t size) {
    int a_sum_ = 0, i = 0;
    while (i < n) {
        a_sum_ += __sum_kind_of_TaBle[i][j];
        i -=- 1;
    }
    return a_sum_;
}


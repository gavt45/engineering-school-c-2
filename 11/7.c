//
// Created by gav on 25/06/2021.
//
#include <stdio.h>
#include <stdlib.h>


int main() {
    freopen("input.txt", "r", stdin);
    int n;
    char c;
    scanf("%d\n", &n);

//    char **field = (char **) malloc(n * sizeof(char *));
//    for (int i = 0; i < n; i++) {
//        field[i] = (char *) malloc(n * sizeof(char));
//        scanf("%s", field[i]);
//    }
//
//    for (int i = 0; i < n; i++)
//        for (int j = 0; j < n; j++)
//            for (int k = 0; k < n; k++) {
//                if (field[j][i] == '1' && field[i][k] == '1')
//                    field[j][k] = '1';
//                else if (j == k)
//                    field[j][j] = '1';
//            }
//
//    for (int i = 0; i < n; i++)
//        printf("%s\n", field[i]);

//    unsigned int W[N][N / 32 + 1]
    unsigned int **W = (unsigned int **) malloc(n * sizeof(unsigned int*));
    for (int i = 0; i < n; ++i)
        W[i] = (unsigned int *) calloc((n / 32 + 1), sizeof(unsigned int));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%c", &c);
            if (c == '1')
                W[i][j / 32] |=  1 << (j % 32);
        }
        scanf("%c", &c);
    }
//    printf("After read:\n");
//    for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < n; ++j) {
//            printf("%d", (W[i][j / 32] >> (j % 32)) & 1);
//        }
//        printf("\n");
//    }
//    printf("\n");

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            if ((W[i][k / 32] >> (k % 32)) & 1)
                for (int j = 0; j < (n / 32 + 1); ++j) {
                    W[i][j] |= W[k][j];
                }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                printf("1");
                continue;
            }
            printf("%d", (W[i][j / 32] >> (j % 32)) & 1);
        }
        printf("\n");
    }

    return 0;
}
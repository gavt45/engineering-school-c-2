//
// Created by Gav on 23/03/2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SOMEABS(x,k) ((x)<0 ? (k+(x)):(x))

int main(){
    int n,k;
    scanf("%d %d", &n, &k);

    int * nums = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; ++i)
        scanf("%d", nums+i);

    char **d = (char**)calloc(n, sizeof(char*));
    for (int j = 0; j < n; ++j) {
        d[j] = (char *) calloc(k, sizeof(char));
        memset(d[j], 0, k); // to be sure on WIN
    }

    d[0][SOMEABS(nums[0]%k, k)] = 1;

    for (int l = 1; l < n; ++l)
        for (int i = 0; i < k; ++i)
            if (d[l - 1][i] == 1) {
                d[l][SOMEABS((i + SOMEABS(nums[l]%k, k)) % k, k)] = 1;
                d[l][SOMEABS((i - SOMEABS(nums[l]%k, k)) % k, k)] = 1;
            }

    printf(d[n-1][0] == 1 ? "Divisible" : "Not divisible");
    return 0;
}

//
// Created by Gav on 15/03/2021.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef unsigned long long ll;

int main() {
    int cnt;
    ll n, m, maxW, w, c, bestMask = 0, bestCnt = 0, bestC = 0;

    scanf("%llu %llu", &n, &maxW);

    ll *W = (ll *) malloc(n * sizeof(ll));
    ll *C = (ll *) malloc(n * sizeof(ll));

    for (int j = 0; j < n; ++j) {
        scanf("%llu %llu", &W[j], &C[j]);
    }

    for (ll mask = 1; mask < (1u << n); ++mask) {
        w = 0;
        c = 0;
        cnt = 0;
        for (unsigned int i = 0; i < n; ++i)
            if ((mask >> i) & 1) {
                if (w+W[i] <= maxW) {
                    w += W[i];
                    c += C[i];
                    cnt++;
                }
            }
        if (c > bestC){
            bestC = c;
            bestCnt = cnt;
            bestMask = mask;
        }
    }

    printf("%llu %llu\n", bestC, bestCnt);
    for (unsigned int i = 0; i < n; ++i)
        if ((bestMask >> i) & 1) {
            printf("%u ", i+1);
        }

    return 0;
}

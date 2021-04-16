//
// Created by Gav on 27/03/2021.
//
#include <stdlib.h>
#include <stdio.h>

typedef long long ll;

int main() {
    ll N;
    scanf("%lld", &N);
    ll **d = (ll **) calloc(N+1, sizeof(ll *));
    for (int i = 0; i < N+1; ++i)
        d[i] = (ll *) calloc(N+1, sizeof(ll));

    d[0][0] = 1;

    for (int n = 0; n <= N; ++n)
        for (int k = 0; k <= N; ++k) {
            //debug handler
//            __asm {
//                nop;nop;nop;nop;
//            };
            if (k == 0 && n > 0)
                d[n][k] = 0;
            else if (0 < k && k <= n)
                d[n][k] = (d[n][k - 1] % (int) (1e9 + 7) + d[n - k][k] % (int) (1e9 + 7)) % (int) (1e9 + 7);
            else if (k > n) {
//                __asm {
//                    nop;nop;nop;nop;
//                };
                d[n][k] = d[n][n] % (int) (1e9 + 7);
//                __asm {
//                    nop;nop;nop;nop;nop;nop;
//                };
            }
        }
    printf("%lld", d[N][N]);
    return 0;
}

//
// Created by Gav on 08/02/2021.
//
//
// Created by Gav on 08/02/2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long double assin(long double x, int to){
    long double res = 1, mult = x;
    for (int i = 2; i < to; ++i) {
//        printf("%d\n", i);
        res += mult;
        mult /= (long double)i;
        mult *= x;
    }
    return res;
}

int main(int argc, char *argv[]) {
    freopen("input.txt", "r", stdin);
    int n, to = 195; //= atoi(argv[1]);
    long double x;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%Lf",&x);
//        printf("x: %lf\n", x);
        if (x>=0)
            printf("%0.15g\n", (double)assin(x,to));
        else
            printf("%0.15g\n", 1.0/(double)assin(-x,to));
    }
    return 0;
}


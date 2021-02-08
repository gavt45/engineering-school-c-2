//
// Created by Gav on 08/02/2021.
//
#include <stdio.h>
#include <stdlib.h>

long double assin(long double x){
    long double res = x, mult = -x*x*x/6;
    for (int i = 2; i < 20; ++i) {
//        printf("%d\n", i);
        res += mult;
        mult *= -x*x/(4*i*i+2*i);
    }
    return res;
}

int main() {
    freopen("input.txt", "r", stdin);
    int n;
    long double x;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%Lf",&x);
//        printf("x: %lf\n", x);
        printf("%0.15Lf\n", assin(x));
    }
    return 0;
}

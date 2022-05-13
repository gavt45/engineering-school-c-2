#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Asimpt_s {
    double p_pow;
    double n_s;
    double log_l_n;
} Asimpt;

Asimpt * read(){
    Asimpt * a = (Asimpt *)malloc(sizeof(Asimpt));
    a->n_s=0;a->log_l_n=0;a->p_pow=0;
//    size_t sz = 40;
    char * s = (char*)malloc(40 * sizeof(char));
//    getline(&s, &sz, stdin);
    scanf("%[^\n]", s);
    getchar();
//    scanf("%s", s);
//    printf("ln: %s\n", s);
    char * ptr = strtok(s, " ");
    while (ptr != NULL) {
//        printf("%s\n",ptr);
//        std::cout << pch  << "n";
        ptr = strtok (NULL, " ");
        if (ptr == NULL) break;
        if (ptr == strstr(ptr, "logN")){
            if (*(ptr+4) == '^')
                sscanf(ptr, "logN^%lf",&a->log_l_n);
            else
                a->log_l_n = 1;
//            printf("logn: %lf\n", a->log_l_n);
        }else if (ptr == strstr(ptr, "N")){
            if (*(ptr+1) == '^'){
                sscanf(ptr, "N^%lf", &a->n_s);
//                printf("N^%lf\n", a->n_s);
            } else {
//                printf("N\n");
                a->n_s = 1;
            }
        }else if (NULL != strstr(ptr, "^N")) {
            sscanf(ptr, "%lf^N", &a->p_pow);
//            printf("%lf^N\n", a->p_pow);
            if (fabs(a->p_pow - 1.0) < 1e-4) a->p_pow = 0;
        }
    }
    return a;
}

int main(){
    freopen("input.txt", "r", stdin);
    int n;
    scanf("%d\n", &n);
    for (int i = 0; i < n; ++i) {
        Asimpt * first = read();
        Asimpt * second = read();
        if (first->p_pow == second->p_pow){
            if (first->n_s == second->n_s){
                if (first->log_l_n == second->log_l_n){
                    printf("0\n");
                } else {
                    printf((first->log_l_n > second->log_l_n) ? "1\n":"-1\n");
                }
            } else {
                printf((first->n_s > second->n_s) ? "1\n":"-1\n");
            }
        } else {
            printf((first->p_pow > second->p_pow) ? "1\n":"-1\n");
        }
    }
    return 0;
}

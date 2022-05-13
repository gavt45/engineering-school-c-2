//
// Created by Gav on 27/03/2021.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct Element_s{
    int len;
    int val;
    int prev_idx;
    int next_idx;
    int first_idx;
}Element;

int main(){
    int n;
    scanf("%d", &n);

    int *arr = (int*)malloc(n*sizeof(int));
    for (int j = 0; j < n; ++j)
        scanf("%d", &arr[j]);

    Element * length = (Element*)malloc(n * sizeof(Element));

    for (int k = 0; k < n; k++) {
        length[k].len = 1;
        length[k].val = arr[n - k - 1];
        length[k].prev_idx = -1;
        length[k].next_idx = -1;
        length[k].first_idx = k;
        for (int i = 0; i < k; i++) {
            if (arr[n - i - 1] > arr[n - k - 1]) {
                if (length[k].len < length[i].len + 1){
                    length[k].len = length[i].len + 1;
                    length[k].prev_idx = i;
                    length[k].first_idx = length[i].first_idx;
                    length[i].next_idx = k;
                }
            }
        }
    }

    int i = n-1, maxlen = length[n-1].len;

    for (int m = n-1; m >= 3*n/4; m--) {
        if (length[m].len > maxlen){
            i = m;
            maxlen = length[m].len;
        }
    }

    printf("%d\n", maxlen);
//    i = length[i].first_idx;
//    while (length[i].prev_idx != -1) {
//        length[length[i].prev_idx].next_idx = i;
//        i = length[i].prev_idx;
//    }
//    for (int l = 0; l < n; ++l) {
//        printf("%d Element{len=%d val=%d prev=%d next=%d}\n", l, length[l].len, length[l].val, length[l].prev_idx, length[l].next_idx);
//    }
//    printf("First idx: %d\n", i);
    while (i != -1){
        printf("A[%d] = %d\n", n - i, length[i].val);
        i = length[i].prev_idx;
    }
    return 0;
}

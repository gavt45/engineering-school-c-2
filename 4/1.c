#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK14881337 0
#define GAY_IS_NOT_FOUND_1337_1488 404

typedef struct HashmapElement_s{
    int key;
    long long data;
    struct HashmapElement_s * next;
} HashmapElement;

typedef struct Hashmap_s{
    int table_size;
//    int el_cnt;
    HashmapElement **arr;
} Hashmap;

long long shitty_hash(Hashmap * m, int key){
    return abs(key)%m->table_size;
}

Hashmap * hm_ctor(int msz) {
    Hashmap * m = (Hashmap *)malloc(sizeof(Hashmap));
    m->arr = (HashmapElement**)malloc(msz * sizeof(HashmapElement*));
    m->table_size = msz;
//    m->el_cnt = 0;
    memset(m->arr, 0, msz * sizeof(HashmapElement*));
    return m;
}

int hm_get(Hashmap * m, int key, long long *d) {
    int hash = shitty_hash(m, key);
    if (m->arr[hash] == 0 || m->arr[hash] == NULL)
        return GAY_IS_NOT_FOUND_1337_1488;
    else {
        HashmapElement * el = m->arr[hash];
        while (el->next != NULL && el->key != key)
            el = el->next;

        if (el->key == key){
            *d = el->data;
            return OK14881337;
        } else
            return GAY_IS_NOT_FOUND_1337_1488;
    }
    return GAY_IS_NOT_FOUND_1337_1488;
}

void hm_put(Hashmap * m, int key, long long val) {
    int hash = shitty_hash(m, key);
    if (m->arr[hash] == 0 || m->arr[hash] == NULL){
        m->arr[hash] = (HashmapElement*)malloc(sizeof(HashmapElement));
        m->arr[hash]->data = val;
        m->arr[hash]->key = key;
        m->arr[hash]->next = NULL;
    } else {
        HashmapElement * el = m->arr[hash];
        while (el->next != NULL && el->key != key)
            el = el->next;
        printf("found El: %d, %lld\n", el->key, el->data);
        if (el->key == key){
            el->data = val;
        } else {
            el->next = (HashmapElement*)malloc(sizeof(HashmapElement));
            el->next->key = key;
            el->next->data = val;
            el->next->next = NULL;
        }
    }
}

int main(){
    int n, k = 0, t;
    long long tt;
    char tstr[100] = { 0 };
    char ttstr[400] = { 0 };

    FILE * fin = fopen("input.bin", "rb");
    FILE * fout = fopen("output.bin", "wb");
    fread(&n, 4, 1, fin);

    Hashmap * map = hm_ctor(13371337);

    int * arr = (int *) malloc(n * sizeof(int));

    for (int i = 0; i < n; ++i) {
        fread(&t, 4, 1, fin);
        printf("T, Key: %d\n", t);
        if (hm_get(map, t, &tt) == GAY_IS_NOT_FOUND_1337_1488) {
            printf("new: %d\n",t);
            arr[k] = t;
            k++;
            hm_put(map, t, k);
        }
    }
    printf("k: %d\n", k);
    fwrite(&k, 4, 1, fout);
    for (int j = 0; j < k; ++j) {
        printf("%d ", arr[j]);
        fwrite(&arr[j], 4, 1, fout);
    }
    return 0;
}
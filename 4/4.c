#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define OK 0
#define NOT_FOUND 404

#define ABS(x) (((x) > 0) ? (x) : (-x))

typedef struct HashmapElement_s{
    unsigned long long key;
    unsigned long long data;
    struct HashmapElement_s * next;
} HashmapElement;

typedef struct Hashmap_s{
    unsigned long long table_size;
//    int el_cnt;
    HashmapElement **arr;
} Hashmap;

unsigned long long shitty_hash(Hashmap * m, unsigned long long x){
//    x = ((x >> 16u) ^ x) * 0x45d9f3b;
//    x = ((x >> 16u) ^ x) * 0x45d9f3b;
//    x = (x >> 16u) ^ x;
    return x%m->table_size;
}

Hashmap * hm_ctor(int msz) {
    Hashmap * m = (Hashmap *)malloc(sizeof(Hashmap));
    m->arr = (HashmapElement**)malloc(msz * sizeof(HashmapElement*));
    m->table_size = msz;
//    m->el_cnt = 0;
    memset(m->arr, 0, msz * sizeof(HashmapElement*));
    return m;
}

int hm_get(Hashmap * m, unsigned long long key, unsigned long long *d) {
    long long int hash = shitty_hash(m, key);
    if (m->arr[hash] == 0 || m->arr[hash] == NULL)
        return NOT_FOUND;
    else {
        HashmapElement * el = m->arr[hash];
        while (el->next != NULL && el->key != key)
            el = el->next;

        if (el->key == key){
            *d = el->data;
            return OK;
        } else
            return NOT_FOUND;
    }
    return NOT_FOUND;
}

void hm_put(Hashmap * m, unsigned long long key, unsigned long long val) {
    long long int hash = shitty_hash(m, key);
    if (m->arr[hash] == 0 || m->arr[hash] == NULL){
        m->arr[hash] = (HashmapElement*)malloc(sizeof(HashmapElement));
        m->arr[hash]->data = val;
        m->arr[hash]->key = key;
        m->arr[hash]->next = NULL;
    } else {
        HashmapElement * el = m->arr[hash];
        while (el->next != NULL && el->key != key)
            el = el->next;
//        printf("found El: %lld, %lld\n", el->key, el->data);
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
unsigned long long func (unsigned long long s, unsigned long long a, unsigned long long b, unsigned long long c, unsigned long long M) {
    return (s *s* a + s*b + c) % M ;
}

int main(){
    unsigned long long M, a, b, c, s = 1, t;
    char snum[100];

    Hashmap * map = hm_ctor(371337);

    for (unsigned long long i = 1; i <= 2 * (int)1e5 - 1; ++i) {
        printf("eval %lld\n", i);
        fflush(stdout);
        scanf("%llu", &s);
//        sprintf(snum, "%lld", s);
        if (hm_get(map, s, &t) == NOT_FOUND)
            hm_put(map, s, i);
        else {
            printf("answer %lld %lld", t, i);
            return 0;
        }
    }
    return 0;
}

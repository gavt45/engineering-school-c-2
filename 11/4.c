#include <stdlib.h>
#include <stdio.h>
#include <assert.h> /* for assert */
#include <memory.h>

#define INF 1e9

typedef struct Pair_s {
    int first;
    int second;
} Pair;

/**
 * @brief cvector_vector_type - The vector type used in this library
 */
#define cvector_vector_type(type) type *

/**
 * @brief cvector_set_capacity - For internal use, sets the capacity variable of the vector
 * @param vec - the vector
 * @param size - the new capacity to set
 * @return void
 */
#define cvector_set_capacity(vec, size)     \
    do {                                    \
        if (vec) {                          \
            ((size_t *)(vec))[-1] = (size); \
        }                                   \
    } while (0)

/**
 * @brief cvector_set_size - For internal use, sets the size variable of the vector
 * @param vec - the vector
 * @param size - the new capacity to set
 * @return void
 */
#define cvector_set_size(vec, size)         \
    do {                                    \
        if (vec) {                          \
            ((size_t *)(vec))[-2] = (size); \
        }                                   \
    } while (0)

/**
 * @brief cvector_capacity - gets the current capacity of the vector
 * @param vec - the vector
 * @return the capacity as a size_t
 */
#define cvector_capacity(vec) \
    ((vec) ? ((size_t *)(vec))[-1] : (size_t)0)

/**
 * @brief cvector_size - gets the current size of the vector
 * @param vec - the vector
 * @return the size as a size_t
 */
#define cvector_size(vec) \
    ((vec) ? ((size_t *)(vec))[-2] : (size_t)0)

/**
 * @brief cvector_empty - returns non-zero if the vector is empty
 * @param vec - the vector
 * @return non-zero if empty, zero if non-empty
 */
#define cvector_empty(vec) \
    (cvector_size(vec) == 0)

/**
 * @brief cvector_grow - For internal use, ensures that the vector is at least <count> elements big
 * @param vec - the vector
 * @param count - the new capacity to set
 * @return void
 */
#define cvector_grow(vec, count)                                              \
    do {                                                                      \
        const size_t cv_sz = (count) * sizeof(*(vec)) + (sizeof(size_t) * 2); \
        if (!(vec)) {                                                         \
            size_t *cv_p = malloc(cv_sz);                                     \
            assert(cv_p);                                                     \
            (vec) = (void *)(&cv_p[2]);                                       \
            cvector_set_capacity((vec), (count));                             \
            cvector_set_size((vec), 0);                                       \
        } else {                                                              \
            size_t *cv_p1 = &((size_t *)(vec))[-2];                           \
            size_t *cv_p2 = realloc(cv_p1, (cv_sz));                          \
            assert(cv_p2);                                                    \
            (vec) = (void *)(&cv_p2[2]);                                      \
            cvector_set_capacity((vec), (count));                             \
        }                                                                     \
    } while (0)

/**
 * @brief cvector_pop_back - removes the last element from the vector
 * @param vec - the vector
 * @return void
 */
#define cvector_pop_back(vec)                           \
    do {                                                \
        cvector_set_size((vec), cvector_size(vec) - 1); \
    } while (0)

/**
 * @brief cvector_erase - removes the element at index i from the vector
 * @param vec - the vector
 * @param i - index of element to remove
 * @return void
 */
#define cvector_erase(vec, i)                                  \
    do {                                                       \
        if (vec) {                                             \
            const size_t cv_sz = cvector_size(vec);            \
            if ((i) < cv_sz) {                                 \
                cvector_set_size((vec), cv_sz - 1);            \
                size_t cv_x;                                   \
                for (cv_x = (i); cv_x < (cv_sz - 1); ++cv_x) { \
                    (vec)[cv_x] = (vec)[cv_x + 1];             \
                }                                              \
            }                                                  \
        }                                                      \
    } while (0)

/**
 * @brief cvector_free - frees all memory associated with the vector
 * @param vec - the vector
 * @return void
 */
#define cvector_free(vec)                        \
    do {                                         \
        if (vec) {                               \
            size_t *p1 = &((size_t *)(vec))[-2]; \
            free(p1);                            \
        }                                        \
    } while (0)

/**
 * @brief cvector_begin - returns an iterator to first element of the vector
 * @param vec - the vector
 * @return a pointer to the first element (or NULL)
 */
#define cvector_begin(vec) \
    (vec)

/**
 * @brief cvector_end - returns an iterator to one past the last element of the vector
 * @param vec - the vector
 * @return a pointer to one past the last element (or NULL)
 */
#define cvector_end(vec) \
    ((vec) ? &((vec)[cvector_size(vec)]) : NULL)

/* user request to use logarithmic growth algorithm */
#ifdef CVECTOR_LOGARITHMIC_GROWTH

/**
 * @brief cvector_push_back - adds an element to the end of the vector
 * @param vec - the vector
 * @param value - the value to add
 * @return void
 */
#define cvector_push_back(vec, value)                               \
    do {                                                            \
        size_t cv_cap = cvector_capacity(vec);                      \
        if (cv_cap <= cvector_size(vec)) {                          \
            cvector_grow((vec), !cv_cap ? cv_cap + 1 : cv_cap * 2); \
        }                                                           \
        vec[cvector_size(vec)] = (value);                           \
        cvector_set_size((vec), cvector_size(vec) + 1);             \
    } while (0)

#else

/**
 * @brief cvector_push_back - adds an element to the end of the vector
 * @param vec - the vector
 * @param value - the value to add
 * @return void
 */
#define cvector_push_back(vec, value)                   \
    do {                                                \
        size_t cv_cap = cvector_capacity(vec);          \
        if (cv_cap <= cvector_size(vec)) {              \
            cvector_grow((vec), cv_cap + 1);            \
        }                                               \
        vec[cvector_size(vec)] = (value);               \
        cvector_set_size((vec), cvector_size(vec) + 1); \
    } while (0)

#endif /* CVECTOR_LOGARITHMIC_GROWTH */

/**
 * @brief cvector_copy - copy a vector
 * @param from - the original vector
 * @param to - destination to which the function copy to
 * @return void
 */
#define cvector_copy(from, to)                                    \
    do {                                                        \
        for(size_t i = 0; i < cvector_size(from); i++) {        \
            cvector_push_back(to, from[i]);                        \
        }                                                        \
    } while (0)

typedef struct Rebro_s{
    int a, b, c;
} Rebro;

int main() {
    freopen("input.txt", "r", stdin);

    int n,m,k, start, end, tmp, a, b, c;
    scanf("%d %d %d", &n, &m, &k);

    cvector_vector_type(int) friends = NULL;
    for (int i = 0; i < k; ++i) {
        scanf("%d", &tmp);
        cvector_push_back(friends, tmp);
    }

    cvector_vector_type(Rebro) e = NULL;

    for (int i = 0; i < m; ++i) {
        Rebro r, r1;
        scanf("%d %d %d", &r.a, &r.b, &r.c);
        r.a--; r.b--;
        cvector_push_back(e, r);
//        r1.a = r.b; r1.b = r.a; r1.c = r.c;
//        cvector_push_back(e, r1);
    }

//    int **dd = (int **) malloc(n * sizeof(int *));
//    int **pp = (int **) malloc(n * sizeof(int *));
//
//    for (int i = 0; i < k; ++i) { // for all friends
    int *d = (int *) malloc(n * sizeof(int));
    for (int j = 0; j < n; ++j) d[j] = INF;

    int *path = (int *) malloc(n * sizeof(int));
    for (int j = 0; j < n; ++j) path[j] = -1;

    d[0] = 0;

    for (;;) {
        char any = 0;
        for (int j=0; j < cvector_size(e); ++j)
            if (d[e[j].a] < INF)
                if (d[e[j].b] > d[e[j].a] + e[j].c) {
                    d[e[j].b] = d[e[j].a] + e[j].c;
                    path[e[j].b] = e[j].a;
                    any = 1;
                }
        if (!any)  break;
    }

//        pp[i] = path;
//        dd[i] = d;
//    }

    for (int i = 0; i < k; ++i) {
        b = friends[i] - 1;

        cvector_vector_type(int) _path = NULL;
        for (int cur=b; cur!=-1; cur = path[cur])
            cvector_push_back(_path, cur);

        printf("%d  %lu  ", d[b], cvector_size(_path));

        for (int j = cvector_size(_path) - 1; j >= 0; --j)
            printf("%d ", _path[j] + 1);

        printf("\n");
    }

    return 0;
}
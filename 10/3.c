//
// Created by gav on 12/05/2021.
//
#include <stdlib.h>
#include <stdio.h>

#define INF 1e9

// MINE

#include <assert.h> /* for assert */
#include <memory.h>

typedef struct Pair_s{
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
#define cvector_copy(from, to)									\
	do {														\
		for(size_t i = 0; i < cvector_size(from); i++) {		\
			cvector_push_back(to, from[i]);						\
		}														\
	} while (0)

#define ERROR_OVERFLOW 0xdeadbeef
#define ERROR_EMPTY 0xDEADCAFE
#define OK 0x0

#define QUEUE_TYPE Pair

typedef struct Queue_s {
    int rear, front;
    QUEUE_TYPE *arr;
    int arr_sz;
    int cnt;
} Queue;

Queue *init_queue(int size) {
    Queue *queue = (Queue *) malloc(sizeof(Queue));
    queue->cnt = 0;
    queue->front = 0;
    queue->rear = -1;
    queue->arr_sz = size;
    queue->arr = (QUEUE_TYPE *) calloc(queue->arr_sz, sizeof(QUEUE_TYPE));
    return queue;
}

int get_first(Queue *queue, QUEUE_TYPE* out) {
    if (queue->cnt == 0) {
        out = NULL;
        return ERROR_EMPTY;
    }
    *out = queue->arr[(queue->front % queue->arr_sz)];
    return OK;
}

QUEUE_TYPE get_last(Queue *queue) {
    return queue->arr[((queue->rear) % queue->arr_sz)];
}

void queue_add(Queue *queue, QUEUE_TYPE value) {
    queue->rear = ((queue->rear + 1) % queue->arr_sz);
    queue->arr[queue->rear] = value;
}

int dequeue(Queue *queue, QUEUE_TYPE* out) {
    *out = queue->arr[queue->front];
    queue->front = ((queue->front + 1) % queue->arr_sz);
    queue->cnt--;
    return OK;
}

int isFull(Queue *queue) {
//    if (queue->rear == -1)
//        return 0;
//    return (((queue->rear + 1) % queue->arr_sz) == queue->front);
    return queue->cnt == queue->arr_sz;
}

int isEmpty(Queue * queue) {
    return queue->cnt == 0;
}

int enqueue(Queue *queue, QUEUE_TYPE val) {
    if (queue->cnt+1 > queue->arr_sz)
        return ERROR_OVERFLOW;
    queue_add(queue, val);
    queue->cnt++;
    return OK;
}

// END


int main() {
    int n, m,a,b;
    scanf("%d", &n);
    cvector_vector_type(Pair) vertexes;
    for (int i = 0; i < n; ++i) {
        Pair v;
        scanf("%d %d", &v.first, &v.second);
        cvector_push_back(vertexes, v);
    }

    cvector_vector_type(char)* g = (cvector_vector_type(char)*) malloc(n * sizeof(cvector_vector_type(char)));
    for (int i = 0; i < n; ++i) {
        g[i] = NULL;
        cvector_set_size(g[i], n);
        for (int j = 0; j < cvector_size(g[i]); ++j) {
            g[i][j] = 0;
        }
    }

    scanf("%d", &m);

    char *used = (char*) calloc(n, sizeof(char));

    int *sel_e = (int *) malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        sel_e[i] = -1;
    }

    for (int i = 0; i < m; ++i) {
        scanf("%d %d", &a, &b);
        a--;b--;
        used[a] = 1; used[b] = 1;
        g[a][b] = 1;
        g[b][a] = 1;
        sel_e[b] = a;
        sel_e[a] = b;
    }

    int *min_e = (int *) malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        min_e[i] = INF;
    }



    return 0;
}
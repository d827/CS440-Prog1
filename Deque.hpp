#ifndef DEQUE_HPP
#define DEQUE_HPP

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define Deque_DEFINE(t)                                                        \
    struct Deque_##t {                                                         \
        t data[10];                                                            \
        t &(*at)(Deque_##t *, int i);                                          \
        void (*delet)(Deque_##t *);                                            \
    };                                                                         \
	struct Deque_##t##_Iterator{											   \
																			   \
																			   \
	};																		   \
    t &Deque_##t##_at(Deque_##t *ap, int i) {                                  \
        assert(i < 10);                                                        \
        return ap->data[i];                                                    \
    }                                                                          \
    void Deque_##t##_delete(Deque_##t *ap) {                                   \
        free(ap);                                                              \
    }                                                                          \
    Deque_##t *Deque_##t##_new() {                                             \
        Deque_##t *ap = (Deque_##t *) malloc(sizeof(Deque_##t));               \
        ap->at = &Deque_##t##_at;                                              \
        ap->delet = &Deque_##t##_delete;                                       \
        return ap;                                                             \
    }

/*Deque_DEFINE(int)
struct MyClass {
    char str[20];
};
Deque_DEFINE(MyClass)*/


#endif

#ifndef DEQUE_HPP
#define DEQUE_HPP

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <string>
#include <typeinfo>

#define Deque_DEFINE(t)															\
	struct Deque_##t;															\
																				\
	struct Deque_##t##_Iterator{											   	\
																				\
		t ptr;																	\
		int index;																\
		Deque_##t *dptr;														\
		void (*inc)(Deque_##t##_Iterator *);									\
		void (*dec)(Deque_##t##_Iterator *);									\
		t &(*deref)(Deque_##t##_Iterator *);									\
		bool (*equal)(Deque_##t##_Iterator it1, Deque_##t##_Iterator it2);		\
																				\
	};																			\
																				\
	struct Deque_##t {															\
		size_t count;															\
		t *data;																\
		int sz;																	\
		int head;																\
		int tail;																\
		char type_name[sizeof("Deque_"#t)];														\
		t &(*at)(Deque_##t *, int i);											\
		t &(*front)(Deque_##t *);												\
		t &(*back)(Deque_##t *);												\
		Deque_##t##_Iterator &(*begin)(Deque_##t *);							\
		Deque_##t##_Iterator &(*end)(Deque_##t *);								\
		void (*dtor)(Deque_##t *);												\
		void (*clear)(Deque_##t *);												\
		void (*push_back)(Deque_##t *, t obj);									\
		void (*push_front)(Deque_##t *, t obj);									\
		void (*pop_back)(Deque_##t *);											\
		void (*pop_front)(Deque_##t *);											\
		void (*sort)(Deque_##t *, Deque_##t##_Iterator it1, Deque_##t##_Iterator it2);	\
		int (*partition)(Deque_##t *, int it1, int it2);						\
		size_t &(*size)(Deque_##t *);											\
		bool (*empty)(Deque_##t *);												\
		bool (*equal)(Deque_##t d1, Deque_##t d2);								\
		bool (*cmp)(const t &o1, const t &o2);									\
	};																			\
																				\
	void Deque_##t##_Iterator_inc(Deque_##t##_Iterator *it){					\
		if(it->index + 1 >= it->dptr->sz){										\
			it->index = 0;														\
			it->ptr = it->dptr->data[it->index];								\
		}																		\
		else{																	\
			it->index++;														\
			it->ptr = it->dptr->data[it->index];								\
		}																		\
	}																			\
	void Deque_##t##_Iterator_dec(Deque_##t##_Iterator *it){					\
		if(it->index - 1 < 0){													\
			it->index = it->dptr->sz-1;											\
			it->ptr = it->dptr->data[it->index];								\
		}																		\
		else{																	\
			it->index--;														\
			it->ptr = it->dptr->data[it->index];								\
		}																		\
																				\
	}																			\
																				\
	t &Deque_##t##_Iterator_deref(Deque_##t##_Iterator *it){					\
		return it->dptr->data[it->index];										\
	}																			\
	bool Deque_##t##_Iterator_equal(Deque_##t##_Iterator it1, Deque_##t##_Iterator it2){	\
		return &(it1.dptr->data[it1.index]) == &(it2.dptr->data[it2.index]);	\
	}																			\
																				\
																				\
	t &Deque_##t##_at(Deque_##t *ap, int i) {                                  	\
		int dex;																\
		if(i >= 1 && ap->head+1 > ap->sz-1 && ap->head+i > ap->sz-1){			\
			dex = 0;															\
			dex += (i-1);														\
		}																		\
		else{																	\
			dex = ap->head+i;													\
		}																		\
		return ap->data[dex];                                                   \
	}                                                                          	\
	t &Deque_##t##_front(Deque_##t *ap) {                                  		\
		return ap->data[ap->head];												\
	} 																			\
	t &Deque_##t##_back(Deque_##t *ap) {                                  		\
		return ap->data[ap->tail];												\
	} 																			\
	Deque_##t##_Iterator &Deque_##t##_begin(Deque_##t *ap){						\
		Deque_##t##_Iterator *it = (Deque_##t##_Iterator *) malloc(sizeof(Deque_##t##_Iterator));	\
		it->index = ap->head;													\
		it->dptr = ap;															\
		it->ptr = (ap->data[ap->head]);											\
		it->inc = Deque_##t##_Iterator_inc;										\
		it->dec = Deque_##t##_Iterator_dec;										\
		it->deref = &Deque_##t##_Iterator_deref;								\
		it->equal = Deque_##t##_Iterator_equal;									\
		return *it;																\
	}																			\
	Deque_##t##_Iterator &Deque_##t##_end(Deque_##t *ap){						\
		Deque_##t##_Iterator *it = (Deque_##t##_Iterator *) malloc(sizeof(Deque_##t##_Iterator));	\
		it->index = ap->tail+1;													\
		it->dptr = ap;															\
		it->ptr = (ap->data[ap->tail+1]);										\
		it->inc = Deque_##t##_Iterator_inc;										\
		it->dec = Deque_##t##_Iterator_dec;										\
		it->deref = &Deque_##t##_Iterator_deref;								\
		it->equal = Deque_##t##_Iterator_equal;									\
		return *it;																\
																				\
	}																			\
	void Deque_##t##_dtor(Deque_##t *ap) {                                   	\
		free((ap->data));                                                       \
	}                                                                          	\
	void Deque_##t##_clear(Deque_##t *ap){										\
		ap->count = 0;															\
		ap->head = -1;															\
		ap->tail = 0;															\
	}																			\
	void Deque_##t##_push_back(Deque_##t *ap, t obj){							\
		if(ap->count == ap->sz){												\
																				\
			int tmp = ap->sz;													\
			int newSz = ap->sz * 2;												\
			ap->data = (t *) realloc(ap->data, sizeof(t) * newSz);				\
			t *toBeCopied = (t *) malloc(sizeof(t) * tmp);						\
			Deque_##t##_Iterator it = ap->begin(ap);							\
			int i = 0;															\
			for (it; it.index != ap->tail; it.inc(&it)) {						\
		        toBeCopied[i] = (it.deref(&it));								\
				i++;															\
		    }																	\
			toBeCopied[i] = (it.deref(&it));									\
																				\
			for(int j = 0; j < tmp; j++){										\
				ap->data[j] = toBeCopied[j];									\
			}																	\
			ap->sz = newSz;														\
			free(toBeCopied);													\
			ap->head = 0;														\
			ap->tail = tmp;														\
			ap->data[ap->tail] = obj;											\
			ap->count++;														\
			return;																\
		}																		\
		if(ap->tail == ap->sz-1) ap->tail = 0;									\
		else{																	\
			ap->tail++;															\
			if(ap->head == -1 && ap->tail == 1){								\
				ap->head = 0;													\
				ap->tail = 0;													\
			}																	\
		}																		\
		ap->data[ap->tail] = obj;												\
		ap->count++;															\
																				\
	}																			\
	void Deque_##t##_push_front(Deque_##t *ap, t obj){							\
		if(ap->count == ap->sz){												\
			int tmp = ap->sz;													\
			int newSz = ap->sz * 2;												\
			ap->data = (t *) realloc(ap->data, sizeof(t) * newSz);				\
			t *toBeCopied = (t *) malloc(sizeof(t) * tmp);						\
			Deque_##t##_Iterator it = ap->begin(ap);							\
			int i = 0;															\
			for (it; it.index != ap->tail; it.inc(&it)) {						\
		        toBeCopied[i] = (it.deref(&it));								\
				i++;															\
		    }																	\
			toBeCopied[i] = (it.deref(&it));									\
																				\
			for(int j = 0; j < tmp; j++){										\
				ap->data[j+1] = toBeCopied[j];									\
			}																	\
			ap->sz = newSz;														\
			free(toBeCopied);													\
			ap->head = 0;														\
			ap->tail = tmp;														\
			ap->data[0] = obj;													\
			ap->count++;														\
			return;																\
		}																		\
																				\
		if(ap->head == 0) ap->head = ap->sz - 1;								\
		else{																	\
			ap->head--;															\
			if(ap->head == -2 && ap->tail == 0){								\
				ap->head = 0;													\
				ap->tail = 0;													\
			}																	\
		}																		\
		ap->data[ap->head] = obj;												\
		ap->count++;															\
	}																			\
	void Deque_##t##_pop_back(Deque_##t *ap){									\
		if(ap->head != -1){														\
			if(ap->head == ap->tail){											\
				ap->head = -1;													\
				ap->tail = -1;													\
			}																	\
			else if(ap->tail == 0) ap->tail = ap->sz-1;							\
			else{																\
				ap->tail--;														\
				ap->count--;													\
			}																	\
		}																		\
																				\
	}																			\
	void Deque_##t##_pop_front(Deque_##t *ap){									\
		if(ap->head != -1){														\
			if(ap->head == ap->tail){											\
				ap->head = -1;													\
				ap->tail = -1;													\
			}																	\
			else if(ap->head == ap->sz-1) ap->head = 0;							\
			else{																\
				ap->head++;														\
				ap->count--;													\
			}																	\
		}																		\
	}																			\
	size_t &Deque_##t##_size(Deque_##t *ap){									\
		return ap->count;														\
	}																			\
	bool Deque_##t##_empty(Deque_##t *ap){										\
		return ap->count == 0;													\
	}																			\
	bool Deque_##t##_equal(Deque_##t d1, Deque_##t d2){							\
		int flag = 0;															\
		int j = d2.head;														\
		int i2;																	\
		int j2;																	\
		if(d1.count == d2.count){												\
			for (int i = d1.head; i != d1.tail+1; i++) {						\
																				\
				if(!(d1.cmp(d1.at(&d1, i), d2.at(&d2, j)) == (d1.cmp(d2.at(&d2, j), d1.at(&d1, i))))){	\
					return false;												\
				}																\
				if(i+1 >= d1.sz) i = -1;										\
				if(j+1 >= d2.sz) j = -1;										\
				j++;															\
			}																	\
			return true;														\
		}																		\
		return false;															\
	}																			\
																				\
	int Deque_##t##_partition(Deque_##t *ap, int it1, int it2){					\
		t pivot = ap->data[it2];												\
		t tmp;																	\
		int i = (it1-1);														\
																				\
		for(int j = it1; j <= it2 - 1; j++){									\
			if(ap->cmp(ap->at(ap, j), ap->at(ap, it2))){						\
				i++;															\
				tmp = ap->data[i];												\
				ap->data[i] = ap->data[j];										\
				ap->data[j] = tmp;												\
			}																	\
		}																		\
		tmp = ap->data[i+1];													\
		(ap->data[i+1]) = (ap->data[it2]);										\
		(ap->data[it2]) = tmp;													\
																				\
		return (i+1);															\
	}																			\
																				\
																				\
	void Deque_##t##_sort(Deque_##t *ap, Deque_##t##_Iterator it1, Deque_##t##_Iterator it2){	\
		if(ap->head > ap->tail){												\
			t *toBeCopied = (t *) malloc(sizeof(t) * ap->sz);					\
			Deque_##t##_Iterator it = ap->begin(ap);							\
			int i = 0;															\
			for (it; it.index != ap->tail; it.inc(&it)) {						\
				toBeCopied[i] = (it.deref(&it));								\
				i++;															\
			}																	\
			toBeCopied[i] = (it.deref(&it));									\
																				\
			for(int j = 0; j < ap->sz; j++){									\
				ap->data[j] = toBeCopied[j];									\
			}																	\
			free(toBeCopied);													\
			ap->head = 0;														\
			ap->tail = ap->sz-1;												\
			it1.index = 0;														\
																				\
		}																		\
		if(Deque_##t##_Iterator_equal(it2, ap->end(ap))){						\
			it2.ptr = ap->data[ap->tail];										\
			it2.index = ap->tail;												\
		}																		\
																				\
		if(it1.index < it2.index){												\
			int pi = Deque_##t##_partition(ap, it1.index, it2.index);			\
																				\
			Deque_##t##_Iterator it3 = it1;										\
			Deque_##t##_Iterator it4 = it2;										\
			it3.ptr = ap->data[pi-1];											\
			it3.index = pi-1;													\
			it4.ptr = ap->data[pi+1];											\
			it4.index = pi+1;													\
			Deque_##t##_sort(ap, it1, it3);										\
			Deque_##t##_sort(ap, it4, it2);										\
		}																		\
	}																			\
	void Deque_##t##_ctor(Deque_##t *ptr, bool (*cmpFunc)(const t &o1, const t &o2)) {                                             									\
																				\
		ptr->at = &Deque_##t##_at;                                              \
		ptr->front = &Deque_##t##_front;										\
		ptr->back = &Deque_##t##_back;											\
		ptr->begin = &Deque_##t##_begin;										\
		ptr->end = &Deque_##t##_end;											\
		ptr->dtor = &Deque_##t##_dtor;                                       	\
		ptr->size = &Deque_##t##_size;											\
		ptr->empty = Deque_##t##_empty;											\
		ptr->equal = Deque_##t##_equal;											\
		ptr->push_back = Deque_##t##_push_back;									\
		ptr->push_front = Deque_##t##_push_front;								\
		ptr->pop_back = Deque_##t##_pop_back;									\
		ptr->pop_front = Deque_##t##_pop_front;									\
		ptr->clear = Deque_##t##_clear;											\
		ptr->sort = Deque_##t##_sort;											\
		ptr->partition = Deque_##t##_partition;									\
		ptr->cmp = cmpFunc;														\
		ptr->count = 0;															\
		ptr->sz = 5;															\
		ptr->head = -1;															\
		ptr->tail = 0;															\
		ptr->data = (t *) malloc(sizeof(t) * ptr->sz);							\
		strcpy(ptr->type_name, "Deque_"#t);										\
	}																			\


#endif

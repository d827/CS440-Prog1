#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <string>
#include <typeinfo>
//#include "Deque.hpp"

using namespace std;

struct MyClass {
    int id;
    char name[10];
};

struct Deque_MyClass;

struct Deque_MyClass_Iterator{											   																			   
	MyClass ptr; 
	int index;
	Deque_MyClass *dptr;
	//MyClass *dptr;
	void (*inc)(Deque_MyClass_Iterator *);																			
	void (*dec)(Deque_MyClass_Iterator *);
	MyClass &(*deref)(Deque_MyClass_Iterator *);
	bool (*equal)(Deque_MyClass_Iterator it1, Deque_MyClass_Iterator it2);
	
};

struct Deque_MyClass {
	size_t count;
	MyClass *data;
	//Deque_MyClass_Iterator *myIt;
	int sz;
	int head;
	int tail;
	char type_name[sizeof("Deque_MyClass")];
	MyClass &(*at)(Deque_MyClass *, int i);
	MyClass &(*front)(Deque_MyClass *);
	MyClass &(*back)(Deque_MyClass *);
	Deque_MyClass_Iterator &(*begin)(Deque_MyClass *);
	Deque_MyClass_Iterator &(*end)(Deque_MyClass *);
	void (*dtor)(Deque_MyClass *);
	void (*clear)(Deque_MyClass *);
	void (*push_back)(Deque_MyClass *, MyClass obj);
	void (*push_front)(Deque_MyClass *, MyClass obj);
	void (*pop_back)(Deque_MyClass *);
	void (*pop_front)(Deque_MyClass *);
	void (*sort)(Deque_MyClass *, Deque_MyClass_Iterator it1, Deque_MyClass_Iterator it2);
	size_t &(*size)(Deque_MyClass *);
	bool (*empty)(Deque_MyClass *);
	bool (*equal)(Deque_MyClass d1, Deque_MyClass d2);
	bool (*cmp)(const MyClass &o1, const MyClass &o2);
};

bool MyClass_less_by_id(const MyClass &o1, const MyClass &o2){
	return o1.id < o2.id;
}

bool MyClass_less_by_name(const MyClass &o1, const MyClass &o2){
	return strcmp(o1.name, o2.name) < 0;
}
void MyClass_print(const MyClass *o){
	printf("%d\n", o->id);
	printf("%s\n", o->name);
}
void Deque_MyClass_Iterator_inc(Deque_MyClass_Iterator *it){
	//it->dptr = (it->dptr->data)++;
	if(it->index + 1 >= it->dptr->sz){
		it->index = 0;
		it->ptr = it->dptr->data[it->index];
	}
	else{
		it->index++;	
		it->ptr = it->dptr->data[it->index];
	}
}
void Deque_MyClass_Iterator_dec(Deque_MyClass_Iterator *it){
	if(it->index - 1 < 0){
		it->index = it->dptr->sz-1;
		it->ptr = it->dptr->data[it->index];
	}
	else{
		it->index--;	
		it->ptr = it->dptr->data[it->index];
	}

}	
	
MyClass &Deque_MyClass_Iterator_deref(Deque_MyClass_Iterator *it){
	//return (*it).ptr;	
	return it->dptr->data[it->index];
}
bool Deque_MyClass_Iterator_equal(Deque_MyClass_Iterator it1, Deque_MyClass_Iterator it2){
	return &(it1.dptr->data[it1.index]) == &(it2.dptr->data[it2.index]);
}


MyClass &Deque_MyClass_at(Deque_MyClass *ap, int i) {                                  
	int dex;
	if(i >= 1 && ap->head+1 > ap->sz-1 && ap->head+i > ap->sz-1){
		dex = 0;
		dex += (i-1);	
	}
	else{
		dex = ap->head+i;
	}
    return ap->data[dex];                                                    
}                                                                          
MyClass &Deque_MyClass_front(Deque_MyClass *ap) {                                  
	return ap->data[ap->head];
} 
MyClass &Deque_MyClass_back(Deque_MyClass *ap) {                                  
	return ap->data[ap->tail];
} 
Deque_MyClass_Iterator &Deque_MyClass_begin(Deque_MyClass *ap){
	Deque_MyClass_Iterator *it = (Deque_MyClass_Iterator *) malloc(sizeof(Deque_MyClass_Iterator));
	it->index = ap->head;
	//it->dptr = (Deque_MyClass *) malloc(sizeof(Deque_MyClass));
	//it->dptr = ap;
	it->dptr = ap;
	it->ptr = (ap->data[ap->head]);
	it->inc = Deque_MyClass_Iterator_inc;
	it->dec = Deque_MyClass_Iterator_dec;
	it->deref = &Deque_MyClass_Iterator_deref;
	it->equal = Deque_MyClass_Iterator_equal;
	return *it;
	/*
	ap->myIt->ptr = *(ap->data);
	ap->myIt->inc = Deque_MyClass_Iterator_inc;
	ap->myIt->dec = Deque_MyClass_Iterator_dec;
	ap->myIt->deref = Deque_MyClass_Iterator_deref;
	ap->myIt->equal = Deque_MyClass_Iterator_equal;
	return *ap->myIt;
	*/
}
Deque_MyClass_Iterator &Deque_MyClass_end(Deque_MyClass *ap){
	/*Deque_MyClass_Iterator it;
	it.ptr = (ap->data[ap->sz-1]);
	it.dptr
	it.inc = Deque_MyClass_Iterator_inc;
	it.dec = Deque_MyClass_Iterator_dec;
	it.deref = Deque_MyClass_Iterator_deref;
	it.equal = Deque_MyClass_Iterator_equal;
	return it;
	*/
	Deque_MyClass_Iterator *it = (Deque_MyClass_Iterator *) malloc(sizeof(Deque_MyClass_Iterator));
	it->index = ap->tail+1;
	//it->dptr = ap;
	it->dptr = ap;
	it->ptr = (ap->data[ap->tail+1]);
	it->inc = Deque_MyClass_Iterator_inc;
	it->dec = Deque_MyClass_Iterator_dec;
	it->deref = &Deque_MyClass_Iterator_deref;
	it->equal = Deque_MyClass_Iterator_equal;
	return *it;
	
}
void Deque_MyClass_dtor(Deque_MyClass *ap) {                                   
	//for(int i = 0; i < ap->sz; i++){
		free((ap->data));                                                              
	//}
}                                                                          
void Deque_MyClass_clear(Deque_MyClass *ap){
	ap->count = 0;
	ap->head = -1;
	ap->tail = 0;
	/*for(int i = 0; i < ap->sz; i++){
		ap->data[i] = 
	}*/
}
void Deque_MyClass_push_back(Deque_MyClass *ap, MyClass obj){
	if(ap->count == ap->sz){
		//q full
		int tmp = ap->sz;	
		int newSz = ap->sz * 2;
		ap->data = (MyClass *) realloc(ap->data, sizeof(MyClass) * newSz);
		MyClass *toBeCopied = (MyClass *) malloc(sizeof(MyClass) * tmp);
		Deque_MyClass_Iterator it = ap->begin(ap);	
		int i = 0;
		for (it; it.index != ap->tail; it.inc(&it)) {
            toBeCopied[i] = (it.deref(&it));
			i++;
        }
		toBeCopied[i] = (it.deref(&it));
		
		for(int j = 0; j < tmp; j++){
			ap->data[j] = toBeCopied[j];
		}
		//after reordering
		ap->sz = newSz;	
		free(toBeCopied);
		ap->head = 0;
		ap->tail = tmp;
		ap->data[ap->tail] = obj;
		ap->count++;
		return;
	}
	if(ap->tail == ap->sz-1) ap->tail = 0;
	else{
		ap->tail++;
		if(ap->head == -1 && ap->tail == 1){
			ap->head = 0;
			ap->tail = 0;
		}
	}
	ap->data[ap->tail] = obj;
	ap->count++;

}
void Deque_MyClass_push_front(Deque_MyClass *ap, MyClass obj){
	if(ap->count == ap->sz){
		//q full
		int tmp = ap->sz;	
		int newSz = ap->sz * 2;
		ap->data = (MyClass *) realloc(ap->data, sizeof(MyClass) * newSz);
		MyClass *toBeCopied = (MyClass *) malloc(sizeof(MyClass) * tmp);
		Deque_MyClass_Iterator it = ap->begin(ap);	
		int i = 0;
		for (it; it.index != ap->tail; it.inc(&it)) {
            toBeCopied[i] = (it.deref(&it));
			i++;
        }
		toBeCopied[i] = (it.deref(&it));
		
		for(int j = 0; j < tmp; j++){
			ap->data[j+1] = toBeCopied[j];
		}
		//after reordering
		ap->sz = newSz;	
		free(toBeCopied);
		ap->head = 0;
		ap->tail = tmp;
		ap->data[0] = obj;
		ap->count++;
		return;
	}

	if(ap->head == 0) ap->head = ap->sz - 1;
	else{
		ap->head--;
		if(ap->head == -2 && ap->tail == 0){
			ap->head = 0;
			ap->tail = 0;
		}	
	}
	ap->data[ap->head] = obj;
	ap->count++;
}
void Deque_MyClass_pop_back(Deque_MyClass *ap){
	if(ap->head != -1){
		if(ap->head == ap->tail){
			ap->head = -1;
			ap->tail = -1;
		}
		else if(ap->tail == 0) ap->tail = ap->sz-1;
		else{
			ap->tail--;
			ap->count--;
		}
	}

}
void Deque_MyClass_pop_front(Deque_MyClass *ap){
	if(ap->head != -1){
		if(ap->head == ap->tail){
			ap->head = -1;
			ap->tail = -1;
		}
		else if(ap->head == ap->sz-1) ap->head = 0;
		else{
			ap->head++;
			ap->count--;
		}
	}
}
size_t &Deque_MyClass_size(Deque_MyClass *ap){
	return ap->count;
}
bool Deque_MyClass_empty(Deque_MyClass *ap){
	return ap->count == 0;
}
bool Deque_MyClass_equal(Deque_MyClass d1, Deque_MyClass d2){
	int flag = 0;	
	int j = d2.head;
	int i2;
	int j2;
	if(d1.count == d2.count){
		for (int i = d1.head; i != d1.tail+1; i++) {
			/*
			if(i + 1 >= d1.sz) i2 = 0;
			else{
				i2 = i + 1;
			}
			if(j + 1 >= d2.sz) j2 = 0;
			else{
				j2 = j + 1;
			}
			*/
			/*if(i + 1 >= d1.sz) i = 0;
			else{
				i = i + 1;
			}
			if(j + 1 >= d2.sz) j2 = 0;
			else{
				j2 = j + 1;
			}*/

				
			//if(!(d1.cmp(d1.at(&d1, i), d1.at(&d1, i2)) == d2.cmp(d2.at(&d2, j), d2.at(&d2, j2)))){
			if(!(d1.cmp(d1.at(&d1, i), d2.at(&d2, j)) == (d1.cmp(d2.at(&d2, j), d1.at(&d1, i))))){
				return false;	
			}
			if(i+1 >= d1.sz) i = -1;
			if(j+1 >= d2.sz) j = -1;
			j++;
		}
		return true;
	}
	return false;
}
void Deque_MyClass_sort(Deque_MyClass *ap, Deque_MyClass_Iterator it1, Deque_MyClass_Iterator it2){

}
void Deque_MyClass_ctor(Deque_MyClass *ptr, bool (*cmpFunc)(const MyClass &o1, const MyClass &o2)) {                                             
	
    //ptr = (Deque_MyClass *) malloc(sizeof(Deque_MyClass));               
    ptr->at = &Deque_MyClass_at;                                              
	ptr->front = &Deque_MyClass_front;
	ptr->back = &Deque_MyClass_back;
	ptr->begin = &Deque_MyClass_begin;
	ptr->end = &Deque_MyClass_end;
    ptr->dtor = &Deque_MyClass_dtor;                                       
	ptr->size = &Deque_MyClass_size;
	ptr->empty = Deque_MyClass_empty;
	ptr->equal = Deque_MyClass_equal;
	ptr->push_back = Deque_MyClass_push_back;
	ptr->push_front = Deque_MyClass_push_front;
	ptr->pop_back = Deque_MyClass_pop_back;
	ptr->pop_front = Deque_MyClass_pop_front;
	ptr->clear = Deque_MyClass_clear;
	ptr->sort = Deque_MyClass_sort;
	ptr->cmp = cmpFunc;
	ptr->count = 0;
	ptr->sz = 5;
	ptr->head = -1;
	ptr->tail = 0;
	//ptr->type_name = {"D","e","q","u","e","_","M","y","C","l","a","s","s","\n"};
	//ptr->myIt = (Deque_MyClass_Iterator *) malloc(sizeof(Deque_MyClass_Iterator));
	ptr->data = (MyClass *) malloc(sizeof(MyClass) * ptr->sz);
}


int main() {

	Deque_MyClass deq;
        Deque_MyClass_ctor(&deq, MyClass_less_by_id);

        assert(deq.size(&deq) == 0);
        // size() should return a size_t.
        assert(typeid(std::size_t) == typeid(decltype(deq.size(&deq))));
        assert(deq.empty(&deq));

        // Should print "---- Deque_MyClass, 14".
        //printf("---- %s, %d\n", deq.type_name, (int) sizeof(deq.type_name));

		//---EDITED FOR DIFF
		printf("---- Deque_MyClass, %d\n", (int) sizeof(deq.type_name));

        // std::cout << "---- " << deq.type_name << ", " << sizeof(deq.type_name) << std::endl;
        assert(sizeof deq.type_name == 14);
		

        deq.push_back(&deq, MyClass{1, "Joe"});
        deq.push_back(&deq, MyClass{2, "Mary"});
        deq.push_back(&deq, MyClass{3, "Tom"});
        deq.push_front(&deq, MyClass{0, "Mike"});
        deq.push_front(&deq, MyClass{-1, "Mary"});
		//RESIZE TEST

        MyClass_print(&deq.front(&deq));
        MyClass_print(&deq.back(&deq));
        assert(deq.front(&deq).id == -1);
        assert(deq.back(&deq).id == 3);

        deq.pop_front(&deq);
        deq.pop_back(&deq);
        assert(deq.front(&deq).id == 0);
        assert(deq.back(&deq).id == 2);

        assert(deq.size(&deq) == 3);
		
        for (Deque_MyClass_Iterator it = deq.begin(&deq);
			!Deque_MyClass_Iterator_equal(it, deq.end(&deq)); it.inc(&it)) {
            MyClass_print(&it.deref(&it));
        }
			
        // Multiple iterators?
        for (Deque_MyClass_Iterator it1 = deq.begin(&deq);
         !Deque_MyClass_Iterator_equal(it1, deq.end(&deq)); it1.inc(&it1)) {
            MyClass_print(&it1.deref(&it1));
            for (Deque_MyClass_Iterator it2 = deq.begin(&deq);
             !Deque_MyClass_Iterator_equal(it2, deq.end(&deq)); it2.inc(&it2)) {
                MyClass_print(&it2.deref(&it2));
                for (Deque_MyClass_Iterator it3 = deq.begin(&deq);
                 !Deque_MyClass_Iterator_equal(it3, deq.end(&deq)); it3.inc(&it3)) {
                    MyClass_print(&it3.deref(&it3));
                }
            }
        }
		
	// Test decrement of end.
        {
            auto it = deq.end(&deq);
            it.dec(&it);
            assert(it.deref(&it).id == 2);
        }

        // printf("Using at.\n");

        for (size_t i = 0; i < 3; i++) {
            MyClass_print(&deq.at(&deq, i));
        }
		

        // Test that front(), back(), at(), and deref() are returning a reference.
        // Change via at().
        assert(deq.at(&deq, 0).id == 0);
        deq.at(&deq, 0).id = 100;
        assert(deq.at(&deq, 0).id == 100);
        // Change via front().
        assert(deq.front(&deq).id == 100);
        deq.front(&deq).id = 0;
        assert(deq.front(&deq).id == 0);
        assert(deq.at(&deq, 0).id == 0); // Verify with at() also.
        {
            auto it = deq.end(&deq);
            it.dec(&it);
            assert(it.deref(&it).id == 2);
            it.deref(&it).id = 200;
            assert(it.deref(&it).id == 200);
            // Change using back().
            assert(deq.back(&deq).id == 200);
            deq.back(&deq).id = 2;
            assert(deq.back(&deq).id == 2);
            assert(it.deref(&it).id == 2); // Verify with iterator also.
        }
		
        deq.clear(&deq);

        deq.dtor(&deq);

		
		// Test equality.  Two deques compare equal if they are of the same
        // length and all the elements compare equal.  It is undefined behavior
        // if the two deques were constructed with different comparison
        // functions.
        {
            Deque_MyClass deq1, deq2;
            // Compare on ID.  Name is ignored.
            Deque_MyClass_ctor(&deq1, MyClass_less_by_id);
            Deque_MyClass_ctor(&deq2, MyClass_less_by_id);

            deq1.push_back(&deq1, MyClass{1, "Joe"});
            deq1.push_back(&deq1, MyClass{2, "Jane"});
            deq1.push_back(&deq1, MyClass{3, "Mary"});
            deq2.push_back(&deq2, MyClass{1, "John"});
            deq2.push_back(&deq2, MyClass{2, "Alice"});
            deq2.push_back(&deq2, MyClass{3, "Mike"});

            assert(Deque_MyClass_equal(deq1, deq2));

            deq1.pop_back(&deq1);
            assert(!Deque_MyClass_equal(deq1, deq2));
            deq1.push_back(&deq1, MyClass{4, "Mary"});
            assert(!Deque_MyClass_equal(deq1, deq2));

            deq1.dtor(&deq1);
            deq2.dtor(&deq2);
        }

	// Test sort with different comparators.
    {
        Deque_MyClass sort_by_id, sorted_by_id;
        Deque_MyClass sort_by_name, sorted_by_name;

        // The two deques below compare on ID only.
        Deque_MyClass_ctor(&sort_by_id, MyClass_less_by_id);
        Deque_MyClass_ctor(&sorted_by_id, MyClass_less_by_id);
        // The two deques below compare on name only.
        Deque_MyClass_ctor(&sort_by_name, MyClass_less_by_name);
        Deque_MyClass_ctor(&sorted_by_name, MyClass_less_by_name);

        sort_by_id.push_back(&sort_by_id, MyClass{1, "Mary"});
        sort_by_id.push_back(&sort_by_id, MyClass{3, "Beth"});
        sort_by_id.push_back(&sort_by_id, MyClass{2, "Kevin"});

        sorted_by_id.push_back(&sorted_by_id, MyClass{1, "Bob"});
        sorted_by_id.push_back(&sorted_by_id, MyClass{2, "Alex"});
        sorted_by_id.push_back(&sorted_by_id, MyClass{3, "Sheldon"});

        sort_by_name.push_back(&sort_by_name, MyClass{9, "Bob"});
        sort_by_name.push_back(&sort_by_name, MyClass{6, "Sheldon"});
        sort_by_name.push_back(&sort_by_name, MyClass{2, "Alex"});

        sorted_by_name.push_back(&sorted_by_name, MyClass{2, "Alex"});
        sorted_by_name.push_back(&sorted_by_name, MyClass{1, "Bob"});
        sorted_by_name.push_back(&sorted_by_name, MyClass{3, "Sheldon"});

        assert(!Deque_MyClass_equal(sort_by_id, sorted_by_id));
        sort_by_id.sort(&sort_by_id, sort_by_id.begin(&sort_by_id), sort_by_id.end(&sort_by_id));
        assert(Deque_MyClass_equal(sort_by_id, sorted_by_id));

        assert(!Deque_MyClass_equal(sort_by_name, sorted_by_name));
        sort_by_name.sort(&sort_by_name, sort_by_name.begin(&sort_by_name), sort_by_name.end(&sort_by_name));
        assert(Deque_MyClass_equal(sort_by_name, sorted_by_name));

        sort_by_id.dtor(&sort_by_id);
        sorted_by_id.dtor(&sorted_by_id);
        sort_by_name.dtor(&sort_by_name);
        sorted_by_name.dtor(&sorted_by_name);
    }
	
}
 

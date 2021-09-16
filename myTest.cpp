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

struct Deque_MyClass_Iterator{											   																			   
	MyClass *cls; 
	void (*inc)(Deque_MyClass_Iterator *);																			
	void (*dec)(Deque_MyClass_Iterator *);
	//DEREF RETURNS MyClass
	void (*deref)(Deque_MyClass_Iterator *);
	bool (*equal)(Deque_MyClass_Iterator it1, Deque_MyClass_Iterator it2); 
		
	
	
};	

struct Deque_MyClass {                                                         
	size_t count;
    MyClass *data;                                                            
	int sz;
	int head;
	int tail;
	//const char *type_name;
    MyClass &(*at)(Deque_MyClass *, int i);                                          
	MyClass &(*front)(Deque_MyClass *);                                          
	MyClass &(*back)(Deque_MyClass *);                                          
	Deque_MyClass_Iterator (*begin)(const Deque_MyClass *);
	Deque_MyClass_Iterator (*end)(const Deque_MyClass *);
    void (*dtor)(Deque_MyClass *);                                            
	void (*clear)(Deque_MyClass *);
	void (*push_back)(Deque_MyClass *, MyClass obj);
	void (*push_front)(Deque_MyClass *, MyClass obj);
	void (*pop_back)(Deque_MyClass *);
	void (*pop_front)(Deque_MyClass *);
	size_t &(*size)(Deque_MyClass *);
	bool (*empty)(Deque_MyClass *);
	bool (*equal)(Deque_MyClass d1, Deque_MyClass d2);
};                                                                         

bool
MyClass_less_by_id(const MyClass &o1, const MyClass &o2) {
    return o1.id < o2.id;
}

bool
MyClass_less_by_name(const MyClass &o1, const MyClass &o2) {
    return strcmp(o1.name, o2.name) < 0;
}

void
MyClass_print(const MyClass *o) {
    printf("%d\n", o->id);
    printf("%s\n", o->name);
}

void Deque_MyClass_Iterator_inc(Deque_MyClass_Iterator *it){
	it++;
} 
void Deque_MyClass_Iterator_dec(Deque_MyClass_Iterator *it){
	it--;
}
//SHOULD RETURN MyClass, switched to void to compile
void Deque_MyClass_Iterator_deref(Deque_MyClass_Iterator *it){
	//return it;
	
}
bool Deque_MyClass_Iterator_equal(Deque_MyClass_Iterator it1, Deque_MyClass_Iterator it2){

}


MyClass &Deque_MyClass_at(Deque_MyClass *ap, int i) {                                  
    return ap->data[i];                                                    
}                                                                          
MyClass &Deque_MyClass_front(Deque_MyClass *ap) {                                  
	return ap->data[ap->head];
} 
MyClass &Deque_MyClass_back(Deque_MyClass *ap) {                                  
	return ap->data[ap->tail];
} 
Deque_MyClass_Iterator Deque_MyClass_begin(const Deque_MyClass *ap){
	Deque_MyClass_Iterator *it = (Deque_MyClass_Iterator *) &(ap->data);
	//it->inc = Deque_MyClass_Iterator_inc;
	//it->dec = Deque_MyClass_Iterator_dec;
	//it->deref = Deque_MyClass_Iterator_deref;
	//it->equal = Deque_MyClass_Iterator_equal;
	return *it;
}
Deque_MyClass_Iterator Deque_MyClass_end(const Deque_MyClass *ap){
	Deque_MyClass_Iterator *it = (Deque_MyClass_Iterator *) &(ap->data[ap->sz-1]);
	return *it;
}
void Deque_MyClass_dtor(Deque_MyClass *ap) {                                   
	//for(int i = 0; i < ap->sz; i++){
		free((ap->data));                                                              
	//}
}                                                                          
void Deque_MyClass_clear(Deque_MyClass *ap){

}
void Deque_MyClass_push_back(Deque_MyClass *ap, MyClass obj){
	if(ap->count == ap->sz){
		//q full
		ap->sz = ap->sz * 2;
		ap->data = (MyClass *) realloc(ap->data, sizeof(MyClass) * ap->sz);

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
		ap->sz = ap->sz * 2;
		ap->data = (MyClass *) realloc(ap->data, sizeof(MyClass) * ap->sz);

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

}
void Deque_MyClass_ctor(Deque_MyClass *ptr, bool amt) {                                             
	
    //ptr = (Deque_MyClass *) malloc(sizeof(Deque_MyClass));               
    ptr->at = &Deque_MyClass_at;                                              
	ptr->front = &Deque_MyClass_front;
	ptr->back = &Deque_MyClass_back;
	ptr->begin = Deque_MyClass_begin;
	ptr->end = Deque_MyClass_end;
    ptr->dtor = &Deque_MyClass_dtor;                                       
	ptr->size = &Deque_MyClass_size;
	ptr->empty = Deque_MyClass_empty;
	ptr->equal = Deque_MyClass_equal;
	ptr->push_back = Deque_MyClass_push_back;
	ptr->push_front = Deque_MyClass_push_front;
	ptr->pop_back = Deque_MyClass_pop_back;
	ptr->pop_front = Deque_MyClass_pop_front;
	ptr->clear = Deque_MyClass_clear;
	ptr->count = 0;
	ptr->sz = 5;
	ptr->head = -1;
	ptr->tail = 0;
	//ptr->type_name = "Deque_MyClass";
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
        /*printf("---- %s, %d\n", deq.type_name, (int) sizeof(deq.type_name));
        // std::cout << "---- " << deq.type_name << ", " << sizeof(deq.type_name) << std::endl;
        assert(sizeof deq.type_name == 14);
		*/

        deq.push_back(&deq, MyClass{1, "Joe"});
        deq.push_back(&deq, MyClass{2, "Mary"});
        deq.push_back(&deq, MyClass{3, "Tom"});
        deq.push_front(&deq, MyClass{0, "Mike"});
        deq.push_front(&deq, MyClass{-1, "Mary"});

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
            //MyClass_print(&it.deref(&it));
        }
		/*	
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

	*/
}
 

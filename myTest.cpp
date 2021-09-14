#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
//#include "Deque.hpp"

struct MyClass {
    int id;
    char name[10];
};


struct Deque_MyClass {                                                         
	size_t size;
    MyClass *data;                                                            
    MyClass &(*at)(Deque_MyClass *, int i);                                          
    void (*dtor)(Deque_MyClass *);                                            
};                                                                         

struct Deque_MyClass_Iterator{											   																			   
																			   
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



MyClass &Deque_MyClass_at(Deque_MyClass *ap, int i) {                                  
    return ap->data[i];                                                    
}                                                                          
void Deque_MyClass_dtor(Deque_MyClass *ap) {                                   
    free(ap);                                                              
}                                                                          
void Deque_MyClass_ctor(Deque_MyClass *ptr, bool amt) {                                             
	
    ptr = (Deque_MyClass *) malloc(sizeof(Deque_MyClass));               
    ptr->at = &Deque_MyClass_at;                                              
    ptr->dtor = &Deque_MyClass_dtor;                                       
	ptr->size = 0;
	ptr->data = (MyClass *) malloc(sizeof(MyClass));
}



int main() {

    /*Deque_MyClass a2;
	Deque_MyClass_ctor(&a2, MyClass_less_by_id);
    strcpy(a2.at(&a2, 0).name, "John");
    printf("%s\n", a2.at(&a2, 0).name);
    a2.dtor(&a2);*/

	Deque_MyClass deq;
    Deque_MyClass_ctor(&deq, MyClass_less_by_id);
	printf("Hi.\n");

    /*assert(deq.size(&deq) == 0);
    // size() should return a size_t.
    assert(typeid(std::size_t) == typeid(decltype(deq.size(&deq))));
    assert(deq.empty(&deq));

    // Should print "---- Deque_MyClass, 14".
    printf("---- %s, %d\n", deq.type_name, (int) sizeof(deq.type_name));
    // std::cout << "---- " << deq.type_name << ", " << sizeof(deq.type_name) << std::endl;
    assert(sizeof deq.type_name == 14);

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
	*/

	// printf("Using at.\n");

    /*for (size_t i = 0; i < 3; i++) {
        MyClass_print(&deq.at(&deq, i));
    }*/
	//deq.clear(&deq);

    //deq.dtor(&deq);


}
 

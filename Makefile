all:	test	

test:	test.o
	g++ -g -ldl test.o -o test

test.o:	test.cpp Deque.hpp	
	g++ -c -g test.cpp -o test.o


clean:
	rm -f *.o test


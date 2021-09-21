# CS440-Prog1

Functionality: All deque and iterator functions work. The macro works as intended (any type can be used). The output of the program is correct up until the sum of all integers section. The only issue is that it segfaults due to a memory leak caused by the way I create iterators, and the abundance of iterators created by the sort function. The sort function works correctly, but the leak eventually causes the program to crash. 

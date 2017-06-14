#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <vector>
#include <netinet/in.h>
#include<arpa/inet.h>
#include <stdio.h>
#include <iostream>
#include <thread>
using namespace std;

template<class T>
void QuickSort(T *array, int len, int (*CompareFun)(const void *,const void *))
{
	if(len <= 1) return;

	int begin = 0, end = len - 1;
	T pivot = array[begin];
	while(begin < end){
		while(begin < end && CompareFun(&array[end], &pivot) >=0) end--;
		array[begin] = array[end];
		while(begin < end && CompareFun(&pivot, &array[end]) >=0) begin++;
		array[end] = array[begin];
	}

	array[begin] = pivot;
	QuickSort(array, begin);
	QuickSort(array + begin + 1, len - begin - 1);
}

int intComp(const void *left,const void *right){
	int *l=(int*)left;
	int *r=(int*)right;
	return *l-*r;
}

int loop = 10000;
volatile int com = 0;
void fun1() {
	for (int i=0; i<loop; i++)
		++com;
}

void fun2() {
	for (int i=0; i<loop; i++) 
		--com;
}

int main()
{
	thread t1(fun1);
	thread t2(fun2);
	t2.join();
	t1.join();
	cout << com << endl;
	return 0;
	//	int pint[] = {3,2,6,4,1,9};
	//	int len = sizeof (pint) /sizeof (pint[0]);
	//	
	//	QuickSort(pint, len, intComp);
	//	for (int i = 0; i < len; i++) {
	//		printf ("%d\n", pint[i]);
	//	}
	//	return 0;
}


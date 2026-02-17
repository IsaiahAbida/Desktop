#include <stdio.h>
#include <stdlib.h>

 int main() {
	int num;
	int *ptr;
	int **handle;

	num = 14;
	ptr = (int *) malloc(2 * sizeof(int));
	*ptr = num;
	handle = (int **) malloc(1 * sizeof(int *));
	*handle = ptr;

	printf("num value: %d\n", num);
    printf("address of num: %p\n\n", (void*)&num);

    printf("ptr value (address stored in ptr): %p\n", (void*)ptr);
    printf("address of ptr: %p\n", (void*)&ptr);
    printf("*ptr (value at address ptr points to): %d\n\n", *ptr);

    printf("handle value (address stored in handle): %p\n", (void*)handle);
    printf("address of handle: %p\n", (void*)&handle);
    printf("*handle (content in heap, should be same as ptr): %p\n", (void*)*handle);
    printf("**handle (value at the int in heap): %d\n\n", **handle);
	return 0;
} 


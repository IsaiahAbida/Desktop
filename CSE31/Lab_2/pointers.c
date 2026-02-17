#include <stdio.h>

int main() {
    int x = 1;
    int y = 2;
    int *px = &x;
    int *py = &y;
    int arr[10];

    // for question 2
    //printf("x = %d, y = %d, arr[0] = %d\n", x, y, arr[0]);

    // for question 4
    // printf("Address of x = %p, Adress of  y = %p", &x, &y);

    // for question 5
    //printf("px has an address of %p, stored value = %p\n", &px, px);
    //printf("py has an address %p, stored value = %p\n", &py, py);

    // for question 6
    //for (int i = 0; i < 10; i++){
    //    printf("arr[%d] = %d\n", i, *(arr + i ));
    //}

    // for question 7
    //    printf("adress of arr = %p\n",(void*)arr);
    //    printf("address of arr[0] = %p\n", (void*)&arr[0]);

    //for   question 8 
        printf("address of arr = %p\n",(void*)arr);

    return 0;
}

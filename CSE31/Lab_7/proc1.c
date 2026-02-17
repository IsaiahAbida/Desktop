#include <stdio.h>

int SUM(int a0, int a1) {
    return a0 + a1;   // same as: add $v0, $a0, $a1
}

int main() {
    int m = 10;
    int n = 5;

    // This mimics:
    // a0 = m
    // a1 = n
    int result = SUM(m, n);

    printf("%d", result);

    return 0;
}
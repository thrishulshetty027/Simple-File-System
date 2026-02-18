#include <stdio.h>

/* Computes y = ax² + bx + c */
int quadratic(int a, int b, int c, int x) {
    return a * x * x + b * x + c;
}

/* Computes y = mx + d */
int linear(int m, int d, int x) {
    return m * x + d;
}

int main() {
    printf("%d\n", quadratic(1, 2, 1, 3));  // 1*9 + 6 + 1 = 16
    printf("%d\n", linear(2, 5, 4));        // 13
    return 0;
}


//
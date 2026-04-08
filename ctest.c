#include <math.h>

#define EPS 1e-9

int isPrime(int n) {
    if (n <= 1) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;

    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

int gcd(int a, int b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;

    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int lcm(int a, int b) {
    if (a == 0 || b == 0) return 0;
    return (a / gcd(a, b)) * b;
}

long long factorial(int n) {
    if (n < 0) return -1;
    if (n == 0 || n == 1) return 1;

    long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

int fibonacci(int n) {
    if (n < 0) return -1;
    if (n == 0) return 0;
    if (n == 1) return 1;

    int a = 0, b = 1, c = 0;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

double power(double base, int exp) {
    double result = 1.0;

    if (exp < 0) {
        base = 1.0 / base;
        exp = -exp;
    }

    while (exp > 0) {
        if (exp % 2 == 1)
            result *= base;
        base *= base;
        exp /= 2;
    }
    return result;
}

int isPerfectSquare(int n) {
    if (n < 0) return 0;
    int root = (int)sqrt(n);
    return root * root == n;
}

int sumOfDigits(int n) {
    if (n < 0) n = -n;

    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int reverseNumber(int n) {
    int reversed = 0;
    int sign = (n < 0) ? -1 : 1;
    n = (n < 0) ? -n : n;

    while (n > 0) {
        reversed = reversed * 10 + (n % 10);
        n /= 10;
    }
    return reversed * sign;
}

int isPalindrome(int n) {
    return n == reverseNumber(n);
}

double nthRoot(double x, int n) {
    if (n <= 0) return -1;
    if (x < 0 && n % 2 == 0) return -1;

    double low = 0, high = x > 1 ? x : 1;
    double mid;

    while ((high - low) > EPS) {
        mid = (low + high) / 2;
        if (pow(mid, n) < x)
            low = mid;
        else
            high = mid;
    }
    return (low + high) / 2;
}

int countSetBits(int n) {
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

int isPowerOfTwo(int n) {
    if (n <= 0) return 0;
    return (n & (n - 1)) == 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int clamp(int value, int low, int high) {
    if (value < low) return low;
    if (value > high) return high;
    return value;
}

double average(int arr[], int size) {
    if (size <= 0) return 0;

    long long sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return (double)sum / size;
}

int variance(int arr[], int size) {
    if (size <= 1) return 0;

    double avg = average(arr, size);
    double var = 0;

    for (int i = 0; i < size; i++) {
        double diff = arr[i] - avg;
        var += diff * diff;
    }
    return (int)(var / size);
}
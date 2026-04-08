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

#include <math.h>

#define MAX 50
#define EPS 1e-6

int absVal(int x) {
    return (x < 0) ? -x : x;
}

int isEven(int n) {
    return n % 2 == 0;
}

int isOdd(int n) {
    return n % 2 != 0;
}

int sumRange(int start, int end) {
    int sum = 0;
    for (int i = start; i <= end; i++) {
        sum += i;
    }
    return sum;
}

int productRange(int start, int end) {
    if (start > end) return 0;

    int prod = 1;
    for (int i = start; i <= end; i++) {
        prod *= i;
    }
    return prod;
}

int isArmstrong(int n) {
    int original = n, sum = 0, digits = 0;
    int temp = n;

    while (temp > 0) {
        digits++;
        temp /= 10;
    }

    temp = n;
    while (temp > 0) {
        int d = temp % 10;
        sum += (int)pow(d, digits);
        temp /= 10;
    }

    return sum == original;
}

int isPerfectNumber(int n) {
    if (n <= 1) return 0;

    int sum = 1;
    for (int i = 2; i <= n / 2; i++) {
        if (n % i == 0)
            sum += i;
    }
    return sum == n;
}

int countDigits(int n) {
    if (n == 0) return 1;

    int count = 0;
    n = absVal(n);

    while (n > 0) {
        count++;
        n /= 10;
    }
    return count;
}

int sumArray(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

int maxArray(int arr[], int size) {
    if (size <= 0) return -1;

    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}

int minArray(int arr[], int size) {
    if (size <= 0) return -1;

    int min = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min)
            min = arr[i];
    }
    return min;
}

void bubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int binarySearch(int arr[], int size, int target) {
    int left = 0, right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target)
            return mid;
        else if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

void matrixAdd(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX], int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void matrixMultiply(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX], int r1, int c1, int c2) {
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            C[i][j] = 0;
            for (int k = 0; k < c1; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

double determinant2x2(double mat[2][2]) {
    return mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0];
}

double distance2D(double x1, double y1, double x2, double y2) {
    return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}

int solveLinear(int a, int b) {
    if (a == 0) return 0;
    return -b / a;
}

int isSorted(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        if (arr[i] < arr[i - 1])
            return 0;
    }
    return 1;
}

void prefixSum(int arr[], int result[], int size) {
    if (size <= 0) return;

    result[0] = arr[0];
    for (int i = 1; i < size; i++) {
        result[i] = result[i - 1] + arr[i];
    }
}

int findPeak(int arr[], int size) {
    if (size == 0) return -1;

    for (int i = 0; i < size; i++) {
        if ((i == 0 || arr[i] >= arr[i - 1]) &&
            (i == size - 1 || arr[i] >= arr[i + 1])) {
            return i;
        }
    }
    return -1;
}
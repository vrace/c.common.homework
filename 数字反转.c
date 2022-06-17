#include <stdio.h>
#include <stdlib.h>

int flip(int n)
{
    int sum = 0;
    while (n) {
        sum = sum * 10 + n % 10;
        n = n / 10;
    }
    return sum;
}

int main(void)
{
    int n;
    printf("Enter an integer:\n");
    scanf("%d", &n);
    printf("After flip:\n%d\n", flip(n));
    return 0;
}

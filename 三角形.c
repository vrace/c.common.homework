#include <stdio.h>
#include <stdlib.h>

void draw_triangle(int rows)
{
    int i;
    int k;
    for (i = 0; i < rows; i++) {
        for (k = 0; k < rows - i - 1; k++) {
            printf(" ");
        }
        for (k = 0; k < i * 2 + 1; k++) {
            printf("*");
        }
        printf("\n");
    }
}

int main(void)
{
    int rows;
    printf("Number of rows:\n");
    scanf("%d", &rows);
    draw_triangle(rows);
    return 0;
}

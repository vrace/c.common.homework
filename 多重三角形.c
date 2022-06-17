#include <stdio.h>
#include <stdlib.h>

void draw_triangles(int rows, char *symbols, int num_symbols)
{
    int i, k, n;

    for (i = 0; i < rows; i++) {
        for (n = 0; n < num_symbols; n++) {
            for (k = 0; k < rows - i - 1; k++) {
                printf(" ");
            }
            for (k = 0; k < i * 2 + 1; k++) {
                putchar(symbols[n]);
            }
            for (k = 0; k < rows - i - 1; k++) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int main(void)
{
    int rows;
    char symbols[] = {'*', '$'};
    
    printf("Number of rows:\n");
    scanf("%d", &rows);

    draw_triangles(rows, symbols, sizeof(symbols));

    return 0;
}

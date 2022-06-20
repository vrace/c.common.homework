#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    int answer;
    int input;
    int range = 100;
    
    srand((unsigned int)time(NULL));
    answer = rand() % range;

    for (;;) {
        printf("Guess the number: (0 ~ %d): ", range);
        scanf("%d", &input);
        if (input < answer) {
            printf("Too small!\nTry again! ");
        }
        else if (input > answer) {
            printf("Too large!\nTry again! ");
        }
        else {
            printf("Correct answer!\n");
            break;
        }
    }

    return 0;
}

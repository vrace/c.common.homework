#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static const int RANGE = 100;
static const int MAX_GUESS = 7;

int main(void)
{
    int answer;
    int input;
    int i;
    
    srand((unsigned int)time(NULL));
    answer = rand() % RANGE;

    for (i = 0; i < MAX_GUESS; i++) {
        printf("Guess the number: (0 ~ %d): ", RANGE);
        scanf("%d", &input);
        if (input < answer) {
            printf("Too small!\n");
        }
        else if (input > answer) {
            printf("Too large!\n");
        }
        else {
            printf("Correct answer!\n");
            break;
        }
    }

    if (i == MAX_GUESS) {
        printf("Ran out of %d chances!\n", MAX_GUESS);
        printf("The actual answer is %d\n", answer);
    }

    return 0;
}

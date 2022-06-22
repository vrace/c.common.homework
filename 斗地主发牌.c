#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct card
{
    char name[20];
} CARD;

typedef struct deck
{
    CARD cards[54];
} DECK;

void init_deck(DECK *deck)
{
    int i, k;
    CARD *card = &deck->cards[0];
    const char *type[] = {"HEART", "SPADE", "DIAMOND", "CLUB"};
    const char *seq[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

    for (i = 0; i < 4; i++) {
        for (k = 0; k < 13; k++) {
            strcpy(card->name, type[i]);
            strcat(card->name, " ");
            strcat(card->name, seq[k]);
            ++card;
        }
    }
    strcpy(card++->name, "RED JOKER");
    strcpy(card++->name, "BLACK JOKER");
}

void shuffle_deck(DECK *deck)
{
    int i, k;
    CARD tmp;

    for (i = 0; i < 54; i++) {
        k = rand() % 54;
        if (i != k) {
            memcpy(&tmp, &deck->cards[i], sizeof(CARD));
            memcpy(&deck->cards[i], &deck->cards[k], sizeof(CARD));
            memcpy(&deck->cards[k], &tmp, sizeof(CARD));
        }
    }
}

int main(void)
{
    int i, k;
    DECK deck;
    CARD *card = &deck.cards[0];

    srand((unsigned int)time(NULL));
    
    init_deck(&deck);
    shuffle_deck(&deck);

    for (i = 0; i < 3; i++) {
        printf("Player %d\n", i + 1);
        for (k = 0; k < 17; k++) {
            printf("%13s", card++->name);
            if (k && (k + 1) % 6 == 0) {
                printf("\n");
            }
        }
        printf("\n");
    }

    printf("Remains\n");
    for (; card != &deck.cards[sizeof(deck.cards) / sizeof(deck.cards[0])]; card++) {
        printf("%13s", card->name);
    }

    return 0;
}

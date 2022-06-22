#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum card_type
{
    CARD_TYPE_HEART,
    CARD_TYPE_SPADE,
    CARD_TYPE_DIAMOND,
    CARD_TYPE_CLUB,
    CARD_TYPE_JOKER,
} CARD_TYPE;

typedef struct card
{
    CARD_TYPE type;
    int index;
} CARD;

typedef struct deck
{
    CARD cards[54];
} DECK;

void init_deck(DECK *deck)
{
    int i, k;
    CARD *card = &deck->cards[0];
    const CARD_TYPE types[] = {CARD_TYPE_HEART, CARD_TYPE_SPADE, CARD_TYPE_DIAMOND, CARD_TYPE_CLUB};

    for (i = 0; i < sizeof(types) / sizeof(types[0]); i++) {
        for (k = 0; k < 13; k++) {
            card->type = types[i];
            card->index = k;
            card++;
        }
    }
    card->type = CARD_TYPE_JOKER;
    card->index = 0;
    card++;
    card->type = CARD_TYPE_JOKER;
    card->index = 1;
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

void draw_card(CARD *card)
{
    static const char *types[] = {"HEART", "SPADE", "DIAMOND", "CLUB"};
    static const char *indices[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    static const char *jokers[] = {"RED JOKER", "BLACK JOKER"};
    char buf[13];

    switch (card->type) {
        case CARD_TYPE_HEART:
        case CARD_TYPE_SPADE:
        case CARD_TYPE_DIAMOND:
        case CARD_TYPE_CLUB:
            sprintf(buf, "%s %s", types[card->type], indices[card->index]);
            printf("%13s", buf);
            break;
        case CARD_TYPE_JOKER:
            printf("%13s", jokers[card->index]);
            break;
        default:
            break;
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
            draw_card(card++);
            if (k && (k + 1) % 6 == 0) {
                printf("\n");
            }
        }
        printf("\n");
    }

    printf("Remains\n");
    for (; card != &deck.cards[sizeof(deck.cards) / sizeof(deck.cards[0])]; card++) {
        draw_card(card);
    }
    printf("\n");

    return 0;
}

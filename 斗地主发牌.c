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
    int rank;
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
            card->rank = k;
            card++;
        }
    }
    card->type = CARD_TYPE_JOKER;
    card->rank = 0;
    card++;
    card->type = CARD_TYPE_JOKER;
    card->rank = 1;
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
    static const char *ranks[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    static const char *jokers[] = {"RED JOKER", "BLACK JOKER"};
    char buf[13];

    switch (card->type) {
        case CARD_TYPE_HEART:
        case CARD_TYPE_SPADE:
        case CARD_TYPE_DIAMOND:
        case CARD_TYPE_CLUB:
            sprintf(buf, "%s %s", types[card->type], ranks[card->rank]);
            printf("%13s", buf);
            break;
        case CARD_TYPE_JOKER:
            printf("%13s", jokers[card->rank]);
            break;
        default:
            break;
    }
}

typedef struct hands
{
    CARD *players[3][17];
    CARD *remains[3];
} HANDS;

void init_hands(HANDS *hands, DECK *deck)
{
    int i, k;
    CARD *card = &deck->cards[0];

    for (i = 0; i < 3; i++) {
        for (k = 0; k < 17; k++) {
            hands->players[i][k] = card++;
        }
    }
    for (i = 0; i < 3; i++) {
        hands->remains[i] = card++;
    }
}

int sort_hands_ranking(const CARD *card)
{
    switch (card->type)
    {
        case CARD_TYPE_HEART:
        case CARD_TYPE_SPADE:
        case CARD_TYPE_DIAMOND:
        case CARD_TYPE_CLUB:
            return card->rank * 10 + card->type;
        case CARD_TYPE_JOKER:
            return 500 + card->rank;
        default:
            break;
    }
    return 0;
}

int sort_hands_fn(const void *left, const void *right)
{
    const CARD *lhs = *(const CARD**)left;
    const CARD *rhs = *(const CARD**)right;
    return sort_hands_ranking(lhs) - sort_hands_ranking(rhs);
}

void sort_hands(HANDS *hands)
{
    int i;
    for (i = 0; i < 3; i++) {
        qsort(hands->players[i], 17, sizeof(CARD*), sort_hands_fn);
    }
    qsort(hands->remains, 3, sizeof(CARD*), sort_hands_fn);
}

void draw_hands(HANDS *hands)
{
    int i, k;

    for (i = 0; i < 3; i++) {
        printf("Player %d\n", i + 1);
        for (k = 0; k < 17; k++) {
            draw_card(hands->players[i][k]);
            if ((k + 1) % 6 == 0) {
                printf("\n");
            }
        }
        printf("\n");
    }

    printf("Remains\n");
    for (i = 0; i < 3; i++) {
        draw_card(hands->remains[i]);
    }
    printf("\n");
}

int main(void)
{
    DECK deck;
    HANDS hands;

    srand((unsigned int)time(NULL));
    
    init_deck(&deck);
    shuffle_deck(&deck);

    init_hands(&hands, &deck);
    sort_hands(&hands);
    draw_hands(&hands);

    return 0;
}

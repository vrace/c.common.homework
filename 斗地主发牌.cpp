#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> init_deck()
{
    std::vector<std::string> deck;
    const char *type[] = {"♠️", "♥️", "♣️", "♦️"};
    const char *seq[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    for (int i = 0; i < 4; i++) {
        for (int k = 0; k < 13; k++) {
            std::string card = type[i];
            card += " ";
            card += seq[k];
            deck.push_back(card);
        }
    }
    deck.push_back("JOKER");
    deck.push_back("Joker");

    for (int i = 0; i < 54; i++) {
        int k = rand() % 54;
        if (i != k) {
            std::string tmp = deck[i];
            deck[i] = deck[k];
            deck[k] = tmp;
        }
    }
    
    return deck;
}

int main(void)
{
    srand((unsigned int)time(NULL));

    std::vector<std::string> deck = init_deck();
    std::vector<std::string>::iterator it = deck.begin();

    for (int i = 0; i < 3; i++) {
        std::cout << "Player " << i + 1 << "\n";
        for (int k = 0; k < 17; k++) {
            std::cout << *it++ << " ";
        }
        std::cout << "\n";
    }
    std::cout << "Remains\n";
    for (; it != deck.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    return 0;
}

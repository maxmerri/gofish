#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <memory>
using namespace std;

class Card {
public:
    int value;
    int suit;
    Card(int x, int y) {
        value = x;
        suit = y;
    }

    bool operator<(const Card& other) const {
        return value < other.value;
    }

    //gives you the name of the card
    string name() {
        string name;
        if (value == 1) {
            name = "Ace";
        }else if (value > 1 && value < 11) {
            name = to_string(value);
        }else if (value == 11) {
            name = "Jack";
        }else if (value == 12) {
            name = "Queen";
        }else if (value == 13) {
            name = "King";
        }

        name += " of ";

        switch (suit) {
            case 1:
                name += "Clubs";
                break;
            case 2:
                name += "Diamonds";
                break;
            case 3:
                name += "Hearts";
                break;
            case 4:
                name += "Spades";
                break;
        }
        return name;
    }
};

vector<Card> shuffleDeck() {
    //makes the deck vector
    vector<Card> deck;

    //adds the cards
    for (int i = 1; i < 14; i++) {
        for (int j = 1; j < 5; j++) {
            deck.emplace_back(i,j);
        }
    }

    //sets up randomization
    random_device rd;
    mt19937 g(rd());
    //shuffles
    std::shuffle(deck.begin(), deck.end(), g);
    return deck;
}

int main() {
    bool gameRunning = true;
    while (gameRunning) {

    }
}
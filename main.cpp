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


bool handContains(vector<Card> hand, int card) {
    for (int i = 0; i < hand.size(); i++) {
        //cout << "hand i value " << hand[i].value << " card " << card << endl;
        if (hand[i].value == card) {
            return true;
        }
    }
    return false;
}

//removes cards asked and adds to the asker
void askCards(vector<Card> &loser, vector<Card> &receiver, int card) {
    for (int i = 0; i < loser.size(); ) {
        if (loser[i].value == card) {
            receiver.push_back(loser[i]);
            cout << "You got a/an " << loser[i].name() << endl;
            loser.erase(loser.begin() + i);
        } else {
            ++i;
            //cout << "askCard loop " << i << " asker[i] " << asker[i].value << " card " << card << endl;
        }
    }
}


int main() {
    bool gameRunning = true;
    while (gameRunning) {
        //set up the deck
        vector<Card> deck = shuffleDeck();


        //deal player their cards
        int cardsDealt = 5;
        vector<Card> playerCards;
        for (int i = 0; i < cardsDealt; i++) {
            playerCards.emplace_back(deck[deck.size() - 1]);
            deck.pop_back();
        }
        //deals bot 1 cards
        vector<Card> bot1Cards;
        for (int i = 0; i < cardsDealt; i++) {
            bot1Cards.emplace_back(deck[deck.size() - 1]);
            deck.pop_back();
        }
        //deals bot 2 cards
        vector<Card> bot2Cards;
        for (int i = 0; i < cardsDealt; i++) {
            bot2Cards.emplace_back(deck[deck.size() - 1]);
            deck.pop_back();
        }


        bool mainLoop = true;
        while (mainLoop) {

            //Player game loop
            while (true) {
                //Choose which bot
                int botChoice;
                while (true) {
                    cout << "Choose which player to ask from. (1 or 2)\n";
                    cin >> botChoice;
                    if (botChoice == 1 or botChoice == 2) {
                        break;
                    }
                    cout << "Invalid choice, please try again\n";
                }

                //Choose which card
                int cardChoice;
                bool cardInputLoop = true;
                while (cardInputLoop) {
                    cout << "Choose which card to ask for. (1 for ace, 13 for king)\n";
                    cin >> cardChoice;
                    if (handContains(playerCards, cardChoice)) {
                        for (int i = 1; i < 13; i++) {
                            if (cardChoice == i) {
                                cardInputLoop = false;
                            }
                        }
                    }else {
                        cout << "Invalid choice, please try again\n";
                    }
                }

                //cout << "Debug: cardchoice: " << cardChoice << " bot choice: " << botChoice << endl;

                //bot1 card interaction
                if (botChoice == 1 && handContains(bot1Cards, cardChoice)) {
                    askCards(bot1Cards, playerCards, cardChoice);
                //bot2 card interactions
                }else if (botChoice == 2 && handContains(bot1Cards, cardChoice)) {
                    askCards(bot2Cards, playerCards, cardChoice);
                }else {
                    cout << "Go Fish\n";
                    if (!deck.empty()) {
                        cout << "You got a/an " << deck[deck.size() - 1].name() << endl;
                        playerCards.emplace_back(deck[deck.size() - 1]);
                        deck.pop_back();
                    }
                }
            }
        }
    }
}

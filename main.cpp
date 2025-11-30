#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include ".\display.cpp"
using namespace std;

//to do
//-----------implement function that removes book from hand and adds 1 to score
//implement bot
//implement game ended state and winner print out


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

void removeBook(vector<Card> &hand) {
    int bookNumber = 0;
    for (int i = 0; i < 13; i++) {
        int cardNum = 0;
        for (int j = 0; j < hand.size(); j++) {
            if (hand[j].value == i) {
                cardNum++;
            }
        }
        if (cardNum == 4) {
            for (int j = 0; j < hand.size();) {
                if (hand[j].value == i) {
                    hand.erase(hand.begin() + j);
                }else {
                    j++;
                }
            }
        }
    }
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

//returns how many books a hand has
bool hasBook(vector<Card> hand) {
    int bookNumber = 0;
    for (int i = 0; i < 13; i++) {
        int cardNum = 0;
        for (int j = 0; j < hand.size(); j++) {
            if (hand[j].value == i) {
                cardNum++;
            }
        }
        if (cardNum == 4) {
            return true;
        }
    }
    return false;
}

void showHand(vector<Card> &hand) {
    cout << "Your hand: ";
    for (int i = 0; i < hand.size(); i++) {
        cout << hand[i].name() << " | ";
    }
    cout << "\n";
}

//used for random number
mt19937 rng((unsigned)chrono::high_resolution_clock::now().time_since_epoch().count());
//returns a random rank from the hand
int chooseRandomRankFromHand(vector<Card>& hand) {
    uniform_int_distribution<int> dist(0, (int)hand.size() - 1);
    return hand[dist(rng)].value;
}

void drawCards() {

}




int main() {
    bool gameRunning = true;
    while (gameRunning) {
        //set up the deck
        vector<Card> deck = shuffleDeck();


        //deal player their cards
        int cardsDealt = 5;
        vector<Card> playerCards;
        int playerScore = 0;
        for (int i = 0; i < cardsDealt; i++) {
            playerCards.emplace_back(deck[deck.size() - 1]);
            deck.pop_back();
        }
        //deals bot 1 cards
        vector<Card> bot1Cards;
        int bot1Score = 0;
        for (int i = 0; i < cardsDealt; i++) {
            bot1Cards.emplace_back(deck[deck.size() - 1]);
            deck.pop_back();
        }
        //deals bot 2 cards
        vector<Card> bot2Cards;
        int bot2Score = 0;
        for (int i = 0; i < cardsDealt; i++) {
            bot2Cards.emplace_back(deck[deck.size() - 1]);
            deck.pop_back();
        }

        //Player game loop
        while (true) {
            display(playerCards, bot1Cards, bot2Cards);
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
            //playerScore = bookNumbers(playerCards);

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

            //checks for 4 of a kind
            if (hasBook(playerCards)) {
                removeBook(playerCards);
                playerScore++;
                cout << "four of a kind\n";
            }

            /*
            //bot 1 actions
            if (!bot1Cards.empty()) {
                int askRank = chooseRandomRankFromHand(bot1Cards);
                cout << "Bot1 asks: Do you have any " << (askRank==1?"Ace": to_string(askRank)) << "s?\n";
                if (handContains(playerCards, askRank)) {
                    transferCards(playerCards, bot1Cards, askRank, "You", "Bot1");
                } else {
                    cout << "You say: Go Fish\n";
                    drawCard(deck, bot1Cards, "Bot1");
                }
            } else {
                // If bot has no cards, it draws one if possible
                if (!deck.empty()) {
                    drawCard(deck, bot1Cards, "Bot1");
                }
            }
            */



        }
    }
}
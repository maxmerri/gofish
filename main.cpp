#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include ".\display.cpp"
#include ".\file.cpp"
using namespace std;

//to do
//file
//

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

//checks if a hand contains a
bool handContains(vector<Card> hand, int card) {
    for (int i = 0; i < hand.size(); i++) {
        //cout << "hand i value " << hand[i].value << " card " << card << endl;
        if (hand[i].value == card) {
            return true;
        }
    }
    return false;
}

//removes a set of four
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
            cout << "You got: " << loser[i].name() << endl;
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

//Used for development while display.cpp was being made
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
//taken from copilot
int chooseRandomRankFromHand(vector<Card>& hand) {
    uniform_int_distribution<int> dist(0, (int)hand.size() - 1);
    return hand[dist(rng)].value;
}



//removes cards asked and adds to the asker; prints messages using names
void transferCards(vector<Card> &loser, vector<Card> &receiver, int card, const string &loserName, const string &receiverName) {
    for (size_t i = 0; i < loser.size(); ) {
        if (loser[i].value == card) {
            cout << receiverName << " You got: " << loser[i].name() << " from " << loserName << endl;
            receiver.push_back(loser[i]);
            loser.erase(loser.begin() + i);
        } else {
            ++i;
        }
    }
}

// returns 0 or 1
int chooseRandomTargetForBot() {
    uniform_int_distribution<int> dist(0,1);
    return dist(rng);
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
        bool playerLoop = true;
        bool cardInputLoop = true;
        while (playerLoop) {
            cout << "-----------------------------------------\nYour Turn \n-----------------------------------------\n";
            display(playerCards, bot1Cards, bot2Cards);
            //showHand(playerCards);
            //Choose which bot
            int botChoice;
            while (true) {
                cout << "Choose which player to ask from. (1 or 2) (3 to quit)\n";
                cin >> botChoice;
                if (botChoice == 1 or botChoice == 2) {
                    break;
                }else if (botChoice == 3) {// use to quit early
                    playerLoop = false;
                    cardInputLoop = false;
                    break;
                }
                cout << "Invalid choice, please try again\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
            }

            //Choose which card
            int cardChoice;
            while (cardInputLoop) {
                cout << "Choose which card to ask for. (1 for ace, 13 for king)\n";
                cin >> cardChoice;
                if (handContains(playerCards, cardChoice)) {
                    if (cardChoice > 0 && cardChoice < 14) {
                        cardInputLoop = false;
                    }
                }else {
                    cout << "Invalid choice, please try again\n";
                }
                std::cin.clear();
                std::cin.ignore(10000, '\n');
            }

            //cout << "Debug: cardchoice: " << cardChoice << " bot choice: " << botChoice << endl;
            cout << "-----------------------------------------" << endl;

            //bot1 card interaction
            if (botChoice == 1 && handContains(bot1Cards, cardChoice)) {
                askCards(bot1Cards, playerCards, cardChoice);
                //bot2 card interactions
            }else if (botChoice == 2 && handContains(bot2Cards, cardChoice)) {
                askCards(bot2Cards, playerCards, cardChoice);
            }else {
                cout << "Bot " << botChoice << " says: Go Fish\n";
                if (!deck.empty()) {
                    cout << "You got: " << deck[deck.size() - 1].name() << endl;
                    playerCards.emplace_back(deck[deck.size() - 1]);
                    deck.pop_back();
                }
            }

            //checks for 4 of a kind
            if (hasBook(playerCards)) {
                removeBook(playerCards);
                playerScore++;
                cout << "Player: four of a kind!\n";
            }

            cout << "-----------------------------------------\nBot One's Turn \n-----------------------------------------\n";



            if (!bot1Cards.empty() || !deck.empty()) {
                if (bot1Cards.empty()) {
                    bot1Cards.emplace_back(deck[deck.size() - 1]);
                    deck.pop_back();
                } else {
                    //Decides if it goes for the bot or the player
                    int target = chooseRandomTargetForBot();
                    int askRank = chooseRandomRankFromHand(bot1Cards);
                    if (target == 0) {
                        cout << "Bot1 asks you: Do you have any " << to_string(askRank) << "s?\n";
                        if (handContains(playerCards, askRank)) {
                            transferCards(playerCards, bot1Cards, askRank, "You", "Bot1");
                        } else {
                            cout << "You say: Go Fish\n";
                            bot1Cards.emplace_back(deck[deck.size() - 1]);
                            deck.pop_back();
                        }
                    } else { // ask bot2
                        cout << "Bot1 asks Bot2: Do you have any " << to_string(askRank) << "s?\n";
                        if (handContains(bot2Cards, askRank)) {
                            transferCards(bot2Cards, bot1Cards, askRank, "Bot2", "Bot1");
                        } else {
                            cout << "Bot2 says: Go Fish\n";
                            bot1Cards.emplace_back(deck[deck.size() - 1]);
                            deck.pop_back();
                        }
                    }
                }
            }


            //checks for 4 of a kind
            if (hasBook(bot1Cards)) {
                removeBook(bot1Cards);
                bot1Score++;
                cout << "Bot 1: four of a kind\n";
            }




            cout << "-----------------------------------------\nBot Two's Turn \n-----------------------------------------\n";

            // Bot2's turn: randomly ask player or bot1
            if (!bot2Cards.empty() || !deck.empty()) {
                if (bot2Cards.empty()) {
                    bot2Cards.emplace_back(deck[deck.size() - 1]);
                    deck.pop_back();
                } else {
                    //Decides if it goes for the bot or the player
                    int target = chooseRandomTargetForBot();
                    int askRank = chooseRandomRankFromHand(bot2Cards);
                    if (target == 0) {
                        cout << "Bot2 asks you: Do you have any " << to_string(askRank) << "s?\n";
                        if (handContains(playerCards, askRank)) {
                            transferCards(playerCards, bot2Cards, askRank, "You", "Bot2");
                        } else {
                            cout << "You say: Go Fish\n";
                            bot2Cards.emplace_back(deck[deck.size() - 1]);
                            deck.pop_back();
                        }
                    } else { // ask bot1
                        cout << "Bot2 asks Bot1: Do you have any " << to_string(askRank) << "s?\n";
                        if (handContains(bot1Cards, askRank)) {
                            transferCards(bot1Cards, bot2Cards, askRank, "Bot1", "Bot2");
                        } else {
                            cout << "Bot1 says: Go Fish\n";
                            bot2Cards.emplace_back(deck[deck.size() - 1]);
                            deck.pop_back();
                        }
                    }
                }
            }


            //checks for 4 of a kind
            if (hasBook(bot2Cards)) {
                removeBook(bot2Cards);
                bot2Score++;
                cout << "Bot 2: four of a kind\n";
            }

            //game control
            if (deck.empty() && playerCards.empty() && bot1Cards.empty() && bot2Cards.empty()) {
                cout << "All cards exhausted. Round over.\n";
                if (playerScore > bot1Score && playerScore > bot2Score) {
                    cout << "YOU WIN!!!! [:";
                }else {
                    cout << "YOU LOST!!! ]:";
                }
                playerLoop = false;
            }
        }
        while (true) {
            string continueInput;
            cout << "Do you want to continue?(y/n)\n";
            cin >> continueInput;
            if (continueInput == "y" or continueInput == "Y") {
                gameRunning = true;
                break;
            }else if (continueInput == "n" or continueInput == "N") {
                gameRunning = false;
                break;
            }
            cout << "invalid input\n";
        }
    }
}
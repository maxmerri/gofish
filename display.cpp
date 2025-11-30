#include <iostream>
#include <vector>
#include <iomanip>
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

//nameCon - name conversion (11=J,12=Q,13=K)
string nameCon(int value) {
    string name;
    {
        if (value == 1) {
            name = "A";
        }else if (value >=2 && value < 10) {
            name = to_string(value);
        }else if (value == 10) {
            name = "10";
        }else if (value == 11) {
            name = "J";
        }else if (value == 12) {
            name = "Q";
        }else if (value == 13) {
            name = "K";
        }
    } return name;
}

//card display - show player their cards, and number of cards for Chuck and Bob
void display(vector<Card> player, vector<Card> Chuck, vector<Card> Bob) {
    int playerCards = 0;
    playerCards = player.size();
    int ChuckCards = 0;
    ChuckCards = Chuck.size();
    int BobCards = 0;
    BobCards = Bob.size();

    //border frame -  stars in corners, minuses as borders
    cout << "* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *\n" << endl;
    //card groups
    cout << " + - - - + - + - + - + - + - + - + - + - + --- + - + - + - +" << endl;
    cout << " |     A | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |  10 | J | Q | K |" << endl;
    cout << " |     / | / | / | / | / | / | / | / | / |   / | / | / | / |" << endl; // replace "/" with initial of completed set "P"/"C"/"B"
    cout << " |       |   |   |   |   |   |   |   |   |     |   |   |   |" << endl;
    cout << " + - - - + - + - + - + - + - + - + - + - + --- + - + - + - +\n\n" << endl;

        //Chuck
        cout << " Chuck has " << Chuck.size() << " cards." << endl;
            //top section
            cout << " + - - - +";
            for (int i = 0; i <= Chuck.size()-2; i++) {
                cout << " - +";
            }
            cout << endl;

            //midsection
            for (int l = 0; l <= 2; l++) {
                cout << " |       |";
                for (int i = 0; i <= Chuck.size()-2; i++) {
                    cout << "   |";
                }
                cout << endl;
            }

            //low section
            cout << " + - - - +";
            for (int i = 0; i <= Chuck.size()-2; i++) {
                cout << " - +";
            }
            cout << "\n" << endl;

        //Bob
        cout << " Bob has " << Bob.size() << " cards." << endl;
            //top section
            cout << " + - - - +";
            for (int i = 0; i <= Bob.size()-2; i++) {
                cout << " - +";
            }
            cout << endl;

            //midsection
            for (int l = 0; l <= 2; l++) {
                cout << " |       |";
                for (int i = 0; i <= Bob.size()-2; i++) {
                cout << "   |";
            }
            cout << endl;
            }

            //low section
            cout << " + - - - +";
            for (int i = 0; i <= Bob.size()-2; i++) {
                cout << " - +";
            }
            cout << "\n" << endl;

        //Player
            cout << " You have " << player.size() << " cards." << endl;
            //top section
            cout << " + - - - +";
            for (int i = 0; i <= player.size()-2; i++) {
                cout << " - +";
            }
            cout << endl;

        //upper midsection
        cout << " |    " << setw(2) << left << nameCon(player[0].value) << " |";
        for (int i = 1; i <=player.size()-1; i++) {
            cout << " " << setw(2) << left << nameCon(player[i].value) << "|";
        }
        cout << endl;


        //low midsection
        for (int l = 0; l <= 1; l++) {
            cout << " |       |";
            for (int i = 0; i <=player.size()-2; i++) {
                cout << "   |";
            }
            cout << endl;
        }

        //low section
        cout << " + - - - +";
        for (int i = 0; i <= player.size()-2; i++) {
            cout << " - +";
        }
        cout << "\n" << endl;
    cout << "* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *" << endl;
}

    //check goFish part - if i ask chuck for ace checks if he has ace.
    /*for (int j = 0; j < playerCards; j++) {
        for (int k = 0; k < ChuckCards; k++) {
            if (player[j] == Chuck[k]) {
                cout << "*";
            }
        }
    }*/
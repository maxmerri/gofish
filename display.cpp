#include <iostream>
#include <vector>
using namespace std;

//card display - show player their cards, and number of cards for Chuck and Bob
void display(vector<Card> player, vector<Card> Chuck, vector<Card> Bob) {
    int playerCards = 0;
    playerCards = player.size();
    int ChuckCards = 0;
    ChuckCards = Chuck.size();
    int BobCards = 0;
    BobCards = Bob.size();

    //border frame -  stars in corners, pluses as borders
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
            for (int i = 0; i <= Chuck.size(); i++) {
                cout << " - +";
            }
            cout << endl;

            //midsection
            for (int l = 0; l <= 2; l++) {
                cout << " |       |";
                for (int i = 0; i <= Chuck.size(); i++) {
                    cout << "   |";
                }
                cout << endl;
            }

            //low section
            cout << " + - - - +";
            for (int i = 0; i <= Chuck.size(); i++) {
                cout << " - +";
            }
            cout << "\n" << endl;

        //Bob
        cout << " Bob has " << Bob.size() << " cards." << endl;
            //top section
            cout << " + - - - +";
            for (int i = 0; i <= Bob.size(); i++) {
                cout << " - +";
            }
            cout << endl;

            //midsection
            for (int l = 0; l <= 2; l++) {
                cout << " |       |";
                for (int i = 0; i <= Bob.size(); i++) {
                cout << "   |";
            }
            cout << endl;
            }

            //low section
            cout << " + - - - +";
            for (int i = 0; i <= Bob.size(); i++) {
                cout << " - +";
            }
            cout << "\n" << endl;

        //Player
            cout << " You have " << player.size() << " cards." << endl;
            //top section
            cout << " + - - - +";
            for (int i = 0; i <= player.size(); i++) {
                cout << " - +";
            }
            cout << endl;

        //upper midsection
        cout << " |     " << player[i] << " |" << endl;
        for (int i = 0; i <=player.size(); i++) {
            cout << " " << player[i+1] << " |";
        }
        cout << endl;


        //low midsection
        for (int l = 0; l <= 1; l++) {
            cout << " |       |";
            for (int i = 0; i <=player.size(); i++) {
                cout << "   |";
            }
            cout << endl;
        }

        //low section
        cout << " + - - - +";
        for (int i = 0; i <= player.size(); i++) {
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
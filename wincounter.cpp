#include <iostream>
#include <fstream>
using namespace std;


// adding one to the win counter when they win
void wc() { // wc = win counter
    /*ofstream outFile; // instantiated an ofstream object - outFile works like the cout object
    outFile.open(".//WinCounter.txt"); // name of the file on the computer (connect ofstream object to a file on your storage system) appears around the executable because of the .//
    int w = 0;
    w++; // adding one to the counter when someone wins
    outFile << w; // using outFile to write data to the new file
    outFile.close(); // closes the file after it is done running the code*/
    int w = -1;
    ifstream inFile(".//WinCounter.txt");
    if (inFile) {
        inFile >> w;
    }
    inFile.close();
    w++;
    ofstream outFile(".//WinCounter.txt");
    outFile << w;
    outFile.close();
}


// show the counter which returns an int to show the number
int nwc() { // outputs the number from the file
    int wins = 0;
    ifstream inFile; // creating an input object
    inFile.open(".//WinCounter.txt"); // opening the file
    if (!inFile) { // lets the user know if they cannot get to the file to open
        return -1;
    } else { // lets the user know that the file could be opened and outputs the data
        inFile >> wins;
        inFile.close();
    }
    return wins;
}

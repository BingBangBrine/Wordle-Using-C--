#include <iostream>
#include <fstream>
#include "functions.h"


#define RESET "\033[0m"
#define GRAY "\033[90m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"

using namespace std;


int main(int argc, char* argv[]) {
    string input;
    mainMenu();
    writeLaunched();
    int wordLength = 5;
    if(argc != 1){
        wordLength = stoi(argv[1]);
        if(wordLength < 4 || wordLength > 8){
            cout << "Must enter wordLength between 4 and 8." << endl;
            writeClosed();
            return 1;
        }
    }
    while(getline(cin, input)){
        if(input == "5"){
            // system("cls");
            break;
        }
        if(input == "4"){
            resetStatistics();
        }
        if(input == "3"){
            viewStatistics();
        }
        if(input == "2"){
            howToPlay();
        }
        if(input == "1"){
            wordle(wordLength);
            mainMenu();
        }
        if(input.empty()){
            mainMenu();
        }

    }
    writeClosed();
        

    return 0;
}
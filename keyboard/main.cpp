#include <iostream>
#include <unistd.h> // for sleep to work
#include <fstream> // to create/write/read from files
#include <vector>
#include "functions.h"

using namespace std;


int main(int argc, char* argv[]) {
    while(true){
        if(gameLaunched()==true){
            int count1 = 0;
            while(gameLaunched() == true){
                if(fileIsChanged() || count1 == 0){
                    clearScreen();
                    keyboard();
                    count1 = 1;
                }
            }   
        }
        else if(appLaunched() == true){
            while(appLaunched() == true){
                clearScreen();
                cout << "Start the first round." << endl;
                sleep(1);
                int count2 = 0;
                while(gameLaunched() == true){
                    if(fileIsChanged() || count2 == 0){
                        clearScreen();
                        keyboard();
                        count2 = 1;
                    }
                }
            }
        }
        else if(appLaunched() == false){
            while(appLaunched() == false){
                clearScreen();
                cout << "Launch the wordle app to begin." << endl;
                sleep(1);
                break;
            }
        }
    }


    return 0;
}
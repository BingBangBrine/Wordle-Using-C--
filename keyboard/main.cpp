#include <iostream>
#include<unistd.h> // for sleep to work
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
                    // system("clear");
                    keyboard();
                    count1 = 1;
                }
            }   
        }
        else if(appLaunched() == true){
            while(appLaunched() == true){
                // system("clear");
                cout << "Start the first round." << endl;
                sleep(1);
                int count2 = 0;
                while(gameLaunched() == true){
                    if(fileIsChanged() || count2 == 0){
                        // system("clear");
                        keyboard();
                        count2 = 1;
                    }
                }
            }
        }
        else if(appLaunched() == false){
            while(appLaunched() == false){
                // system("clear");
                cout << "Launch the wordle app to begin." << endl;
                sleep(1);
                while(appLaunched() == true){
                    // system("clear");
                    cout << "Start the first round." << endl;
                    sleep(1);
                    int count3 = 0;
                    while(gameLaunched() == true){
                        if(fileIsChanged() || count3 == 0){
                            // system("clear");
                            keyboard();
                            count3 = 1;
                        }
                    }
                }
            }
        }
    }


    return 0;
}
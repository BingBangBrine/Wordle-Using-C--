#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#define RESET "\033[0m"
#define GRAY "\033[90m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"


#include <iostream>
#include <unistd.h> // for sleep to work
#include <fstream> // to create/write/read from files
#include <vector>
#include <iomanip>

void clearScreen(){
    printf( "\033[2J" "\033[1;1H");
}


// status file will have the following format:
// isLaunched isGameRunning
// Example of the Wordle game not launched or running:
// false false

void fileToVector(std::vector<std::string>& launch){
    std::ifstream file; // declares file for opening

    file.open("status.txt", std::ios::in); // opens file for reading

    if(file.is_open()) { // checks if file opened successfully
        std::string empty, tempword;
        while(file >> tempword){
            launch.push_back(tempword);
            tempword = empty;
        }
        file.close();
    }    
    
}

void fileToColorString(std::string& s, std::string filename){
    std::string newDir = "../wordle/" + filename;
    std::ifstream file(newDir); // declares file for opening

    std::string line, word;
    if(file.is_open()) { // checks if file opened successfully
        while(getline(file, line)) {
            word+=line;
        }
        file.close();
    }
    s = word;
}

void kbFileToColorString(std::string& s, std::string filename){
    std::ifstream file(filename); // declares file for opening

    std::string line, word;
    if(file.is_open()) { // checks if file opened successfully
        while(getline(file, line)) {
            word+=line;
        }
        file.close();
    }
    s = word;
}

std::string getColor(char color){
    bool isGreen = false;
    bool isYellow = false;
    bool isGray = false;
    std::string greenString = "";
    fileToColorString(greenString, "green.txt");
    std::string yellowString = "";
    fileToColorString(yellowString, "yellow.txt");
    std::string grayString = "";
    fileToColorString(grayString, "gray.txt");

    for(char c : greenString){
        if(color == c){
            isGreen = true;
        }
    }
    for(char c : yellowString){
        if(color == c){
            isYellow = true;
        }
    }
    for(char c : grayString){
        if(color == c){
            isGray = true;
        }
    }    

    if(isGreen){
        return GREEN;
    }
    else if(isYellow){
        return YELLOW;
    }
    else if(isGray){
        return GRAY;
    }
    return RESET;
}

void keyboard(){
    std::string bar = " --- ";
    std::string leftBar = "| ";
    std::string rightBar = " |";
    std::string topLetters = "QWERTYUIOP";
    std::string midLetters = "ASDFGHJKL";
    std::string bottomLetters = "ZXCVBNM";
    
    std::string printTopBar = "";
    std::string printTopLetters = "";
    std::string printMidBar = "";
    std::string printMidLetters = "";
    std::string printBottomBar = "";
    std::string printBottomLetters = "";

    for(char c : topLetters){
        printTopBar += getColor(c) + bar + RESET;
        printTopLetters += getColor(c) + leftBar + c + rightBar + RESET;
    }

    for(char c : midLetters){
        printMidBar += getColor(c) + bar + RESET;
        printMidLetters += getColor(c) + leftBar + c + rightBar + RESET;
    }

    for(char c : bottomLetters){
        printBottomBar += getColor(c) + bar + RESET;
        printBottomLetters += getColor(c) + leftBar + c + rightBar + RESET;
    }
    
    std::cout << "\t" << printTopBar << std::endl;
    std::cout << "\t" << printTopLetters << std::endl;
    std::cout << "\t" << printTopBar << std::endl;

    std::cout << "\t   " << printMidBar << std::endl;
    std::cout << "\t   " << printMidLetters << std::endl;
    std::cout << "\t   " << printMidBar << std::endl;

    std::cout << "\t        " << printBottomBar << std::endl;
    std::cout << "\t        " << printBottomLetters << std::endl;
    std::cout << "\t        " << printBottomBar << std::endl;
    
}

void writeToFile(std::string s){
    std::ofstream file("../keyboard/previousString.txt");
    if(file.is_open()) {
        file << s;
        file.close();
    }
}

bool fileIsChanged(){
    std::string greenString = "";
    fileToColorString(greenString, "green.txt");
    std::string yellowString = "";
    fileToColorString(yellowString, "yellow.txt");
    std::string grayString = "";
    fileToColorString(grayString, "gray.txt");
    
    std::string currentString = greenString + yellowString + grayString;
    std::string previousString = "";
    kbFileToColorString(previousString, "previousString.txt");
    if(previousString == currentString){
        return false;
    }
    else{
        writeToFile(currentString);
        return true;
    }
}


bool gameLaunched() {
    bool launched = false;
    std::vector<std::string> launch;
    fileToVector(launch);

    if(launch[1] == "true"){
        launched = true;
    }    
    return launched;
}

bool appLaunched() { // will read from the status file to see if game is launched
    bool launched = false; // declares launched variable to be returned later
    std::vector<std::string> launch;
    fileToVector(launch);
    
    if(launch[0] == "true"){
        launched = true;
    }
    return launched;
}

void gameRunning(){
    std::ofstream file("../keyboard/status.txt");
    if(file.is_open()) {
        file << "true true";
        file.close();
    }
}

void writeLaunched(){
    std::ofstream file("../keyboard/status.txt");
    if(file.is_open()) {
        file << "true false";
        file.close();
    }
}

void writeClosed(){
    std::ofstream file("../keyboard/status.txt");
    if(file.is_open()) {
        file << "false false";
        file.close();
    }
}

void clearColorFile(std::string filename){
    std::string dir = "../wordle/" + filename;
    std::ofstream file(dir);
    if(file.is_open()) {
        file.close();
    }
}

void addToColorFile(std::string filename, std::string str){
    std::string dir = "../wordle/" + filename;
    std::ofstream file(dir);
    if(file.is_open()) {
        file << str;
        file.close();
    }
}

void clearKeyboard(){
    clearColorFile("green.txt");
    clearColorFile("yellow.txt");
    clearColorFile("gray.txt");
}

std::string readOutput(std::string filename){
    std::ifstream file; // declares file for opening
    std::string fileInString;
    file.open(filename, std::ios::in); // opens file for reading

    if(file.is_open()) { // checks if file opened successfully
        std::string line;
        while(getline(file, line)) {
            fileInString += line;
        }
        file.close();
    }
    return fileInString;
}


#endif
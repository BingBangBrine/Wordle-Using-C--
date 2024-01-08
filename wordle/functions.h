#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#define RESET "\033[0m"
#define GRAY "\033[90m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>

void howToPlay(){
    system("clear");
    std::cout << "=============================================" << std::endl;
    std::cout << "                 HOW TO PLAY" << std::endl;
    std::cout << "=============================================" << std::endl;
    std::cout << "Guess the Wordle in 6 tries." << std::endl;
    std::cout << "\n\nHOW TO PLAY:" << std::endl;
    std::cout << "- Each guess must be a valid 5 letter word." << std::endl;
    std::cout << "- The color of the tiles will change to show" << std::endl;
    std::cout << "  you how close your guess was to the word." << std::endl;
    std::cout << GREEN << "\n\n --- " << RESET << " ---  ---  ---  ---"<< std::endl;
    std::cout << GREEN << "| W |" << RESET << "| E || A || R || Y |" << std::endl;
    std::cout << GREEN << " --- " << RESET << " ---  ---  ---  ---"<< std::endl;
    std::cout << "W Is in the word and in the correct spot." << std::endl;
    std::cout << "\n ---  " << YELLOW << "---  " << RESET << "---  ---  ---"<< std::endl;
    std::cout << "| P |" << YELLOW << "| I |" << RESET << "| L || L || S |" << std::endl;
    std::cout << " ---  " << YELLOW << "---  " << RESET << "---  ---  ---"<< std::endl;
    std::cout << "I is in the word but in the wrong spot." << std::endl;
    std::cout << "\n\n ---  ---  ---  " << GRAY << "---  " << RESET << "---" << std::endl;
    std::cout << "| V || A || G |" << GRAY << "| U |" << RESET "| E |" << std::endl;
    std::cout << " ---  ---  ---  " << GRAY << "---  " << RESET << "---" << std::endl;
    std::cout << "U is not in the word in any spot." << std::endl;

    std::cout << "\n\nPress [enter] to continue " << std::endl;

}

void mainMenu(){
    system("clear");
    std::cout << "=========================" << std::endl; 
    std::cout << "    WELCOME TO WORDLE" << std::endl;
    std::cout << "=========================" << std::endl;
    std::cout << "\n\n1. Play Wordle" << std::endl;
    std::cout << "2. How to Play" << std::endl;
    std::cout << "3. Statistics Summary" << std::endl;
    std::cout << "4. Reset Statistics" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "\n\nSelect an option:" << std::endl;
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

void gameRunning(){
    std::ofstream file("../keyboard/status.txt");
    if(file.is_open()) {
        file << "true true";
        file.close();
    }
}

std::vector<std::string> stringToVec(std::string str){
    std::vector<std::string> vec;
    std::string oneWord = "";

    for(char c : str){
        if(!(isalpha(c) || std::isdigit(c))) {
            vec.push_back(oneWord);
            oneWord = "";
        }
        else{
            oneWord += c;
        }
    }
    return vec;
}

void fileToVector(std::vector<std::vector<std::string>>& vec){
    std::ifstream file; // declares file for opening
    file.open("stats.txt", std::ios::in); // opens file for reading

    if(file.is_open()) { // checks if file opened successfully
        std::string line, word;
        while(getline(file, line)) {
            vec.push_back(stringToVec(line));
        }
        file.close();
    }
}

void fileToStringVector(std::vector<std::string>& vec, std::string filename){
    std::ifstream file; // declares file for opening
    file.open(filename, std::ios::in); // opens file for reading

    if(file.is_open()) { // checks if file opened successfully
        std::string line, word;
        while(getline(file, line)) {
            vec.push_back(line);
        }
        file.close();
    }
}    


void addToFile(std::vector<std::string> round){
    std::ofstream file;
    file.open("stats.txt", std::ios::app);

    if(file.is_open()){
        for(std::string item : round){
            file << item << " ";
        }
        file << std::endl;
        file.close();
    }
    
}

void resetStatistics(){
    std::ofstream file;
    file.open("stats.txt", std::ios::out);
    if(file.is_open()){
        file.close();
    }

    system("clear");
    std::cout << "==========================" << std::endl;
    std::cout << "    STATISTICS SUMMARY" << std::endl;
    std::cout << "==========================" << std::endl;
    std::cout << "Times Played:            0" << std::endl;
    std::cout << "Average Attempts:        0" << std::endl;
    std::cout << "Win Percentage:         0%" << std::endl;
    std::cout << "Current Streak:          0" << std::endl;
    std::cout << "Longest Streak:          0" << std::endl;
    std::cout << "\n\n--------------------------" << std::endl;
    std::cout << "WORD     ATTEMPTS      WIN" << std::endl;
    std::cout << "--------------------------" << std::endl;
    std::cout << "\n\nPress [enter] to continue " << std::endl;
}

void viewStatistics(){
    std::vector<std::vector<std::string>> stats;
    fileToVector(stats);
    
    int timesPlayed = stats.size();
    if(timesPlayed != 0){
        int totalAttempts = 0;
        for(std::vector<std::string> vec : stats){
            totalAttempts += std::stoi(vec[1]);
        }
        int averageAttempts = totalAttempts / timesPlayed;
        
        int wins = 0, losses = 0, bestStreak = 0, currentStreak = 0;
        for(std::vector<std::string> vec : stats){
            if(vec[2] == "Yes"){
                wins++;
                currentStreak++;
                if(bestStreak < currentStreak){
                    bestStreak = currentStreak;
                }
            }
            else if(vec[2] == "No"){
                losses++;
                if(bestStreak < currentStreak){
                    bestStreak = currentStreak;
                }
                currentStreak = 0;
            }
        }
        float winPercent = (float)wins / (float)(wins+losses);


        system("clear");
        std::cout << "==========================" << std::endl;
        std::cout << "Statistics Summary" << std::endl;
        std::cout << "==========================" << std::endl;
        std::cout << "Times Played:" << std::setw(13) << timesPlayed << std::endl;
        std::cout << "Average Attempts:" << std::setw(9) << averageAttempts << std::endl;
        std::cout << "Win Percentage:" << std::setw(10)  << std::setprecision(3) << winPercent*100 << "%" << std::endl;
        std::cout << "Current Streak:" << std::setw(11) << currentStreak << std::endl;
        std::cout << "Longest Streak:" << std::setw(11) << bestStreak << std::endl;
        std::cout << "\n\n--------------------------" << std::endl;
        std::cout << "WORD     ATTEMPTS      WIN" << std::endl;
        std::cout << "--------------------------" << std::endl;
        
        for(std::vector<std::string> vec : stats){
            int lenOfWord = vec[0].length();
            std::cout << vec[0] << std::setw(17-lenOfWord) << vec[1] << std::setw(9) << vec[2] << std::endl;
        }
        std::cout << "\n\nPress [enter] to continue " << std::endl;
    }
    else{
        resetStatistics();
    }
    
    
}

std::string wordUpper(std::string word) {
    std::string newWord = "";
    for(char c : word) {
        newWord += std::toupper(c);
    }
    return newWord;
}

std::string wordLower(std::string word) {
    std::string newWord = "";
    for(char c : word) {
        newWord += std::tolower(c);
    }
    return newWord;
}

std::string determineWord(int wordLength){
    std::ifstream file; // declares file for opening
    std::vector<std::string> launch;
    std::string wordsFileName = std::to_string(wordLength) + "-words.txt";
    file.open(wordsFileName, std::ios::in); // opens file for reading

    if(file.is_open()) { // checks if file opened successfully
        std::string empty, tempword;
        while(file >> tempword){
            launch.push_back(tempword);
            tempword = empty;
        }
        file.close();
    }
    std::srand(std::time(nullptr));
    int random = rand() % launch.size();
    return launch[random];
}

bool isWord(std::string guess, int wordLength){
    std::vector<std::string> words, allowedWords, correctWords;
    std::string allowedFileName = std::to_string(wordLength) + "-allowed.txt";
    std::string wordsFileName = std::to_string(wordLength) + "-words.txt";
    fileToStringVector(allowedWords, allowedFileName);
    fileToStringVector(correctWords, wordsFileName);

    for(std::string s : allowedWords){
        words.push_back(s);
    }
    for(std::string s : correctWords){
        words.push_back(s);
    }

    for(std::string word : words)    
        if(word == guess){
            return true;
        }

    return false;
}

bool letterInFile(char letter, std::string filename){
    // open file read by line. while loop see if 
    std::ifstream file; // declares file for opening
    file.open(filename, std::ios::in); // opens file for reading
    std::string line, word;
    if(file.is_open()) { // checks if file opened successfully
        while(getline(file, line)) {
            word+=line;
        }
        file.close();
    }
    for(char c : word){
        if(c == letter){
            return true;
        }
    }
    return false;
}

void addColorLetter(std::string color, char letter){
    std::string filename = wordLower(color) + ".txt";
    if(!letterInFile(letter, filename)){
        std::ofstream file;
        file.open(filename, std::ios::app);

        if(file.is_open()){
            file << letter;
            file.close();
        }
    }
}

void clearColorFile(std::string filename){
    std::ofstream file;
    file.open(filename, std::ios::out);
    if(file.is_open()) {
        file.close();
    }
}

std::string getColor(std::string guess, std::string correctWord, char charGuess, int locationOfCharInGuess){
    int locationOfCharInWord = -1;
    bool inWord = false;
    for(int i = locationOfCharInGuess; i < correctWord.length(); i++){
        if(correctWord[i] == charGuess){
            locationOfCharInWord = i;
            break;
        }
    }
    for(int i=0; i<correctWord.length();i++){
        if(correctWord[i] == charGuess){
            inWord = true;
        }
    }

    if(locationOfCharInWord == locationOfCharInGuess){
        addColorLetter("GREEN", charGuess);
        return GREEN;
    }
    else if(inWord){
        addColorLetter("YELLOW", charGuess);
        return YELLOW;
    }    
    else if(locationOfCharInWord == -1){
        addColorLetter("GRAY", charGuess);
        return GRAY;
    }
    return RESET;
}

void printGuess(std::string guess, std::string word){
    std::string guessColored = "";
    std::string barColored = "";
    std::string leftBar = "| ";
    std::string rightBar = " |";
    std::string bar = " --- ";
    std::string color = "";
    for(int i = 0; i < guess.length(); i++){
        color = getColor(guess, word, guess[i], i);
        guessColored += color + leftBar + guess[i] + rightBar + RESET;
        barColored += color + bar + RESET;
    }
    
    std::cout << barColored << std::endl;    
    std::cout << guessColored << std::endl;
    std::cout << barColored << std::endl;
}

void wordle(int wordLength){
    gameRunning(); // open the game
    std::string input;
    std::string guess;
    std::string win = "No";
    std::vector<std::string> round;
    std::string word = wordUpper(determineWord(wordLength));
    int attempts = 0;
    system("clear");

    std::vector<std::string> guesses;
    // std::cout << word << std::endl;
    std::cout << "Enter guess: ";
    clearColorFile("gray.txt");
    clearColorFile("green.txt");
    clearColorFile("yellow.txt");

    while(std::getline(std::cin, guess)){
        attempts++;
        if(attempts == 6 && guess.length() == wordLength && isWord(wordLower(guess), wordLength)){
            guesses.push_back(wordUpper(guess));
            if(wordUpper(guess) == word){
                system("clear");
                for(int i=0; i<guesses.size(); i++){
                    printGuess(wordUpper(guesses[i]), wordUpper(word));
                }
                std::cout << "You win because you guessed " << word << " with " << attempts << " attempts." << std::endl;
                std::cout << "\n\nPress [enter] to continue " << std::endl;
                std::getline(std::cin, guess);                
                win = "Yes";
                break;
            }
            system("clear");
            for(int i=0; i<guesses.size(); i++){
                printGuess(wordUpper(guesses[i]), wordUpper(word));
            }
            std::cout << "You lost. The word was: " << word << std::endl;
            std::cout << "\n\nPress [enter] to continue " << std::endl;
            std::getline(std::cin, guess);
            break;
        }
        else{
            if(guess.length() == wordLength && isWord(wordLower(guess), wordLength)){
                guesses.push_back(guess);
                if(wordUpper(guess) == word){
                    system("clear");
                    for(int i=0; i<guesses.size(); i++){
                        printGuess(wordUpper(guesses[i]), wordUpper(word));
                    }
                    if(attempts == 1){
                        std::cout << "You win because you guessed " << word << " with 1 attempt." << std::endl;
                    }
                    else{
                        std::cout << "You win because you guessed " << word << " with " << attempts << " attempts." << std::endl;
                    }
                    
                    std::cout << "\n\nPress [enter] to continue " << std::endl;
                    std::getline(std::cin, guess);
                    guess = "";
                    win = "Yes";
                    break;
                }
            }
            else{
                attempts--;
                std::cout << "Enter Guess: ";
                continue;
            }
            system("clear");
            // std::cout << word << std::endl;
            for(int i=0; i<guesses.size(); i++){
                printGuess(wordUpper(guesses[i]), wordUpper(word));
            }
        }
        if(attempts != 6){
            std::cout << "Enter Guess: ";
        }
    }
    
    round.push_back(word);
    round.push_back(std::to_string(attempts));
    round.push_back(win);

    addToFile(round); // write to file the round results
    writeLaunched(); // closing the game

}

//git message for next commit:
//


//for tests
void kbFileToVector(std::vector<std::string>& launch){
    // std::ifstream file; // declares file for opening
    std::ifstream file("../keyboard/status.txt");
    // file.open("status.txt", std::ios::in); // opens file for reading

    if(file.is_open()) { // checks if file opened successfully
        std::string empty, tempword;
        while(file >> tempword){
            launch.push_back(tempword);
            tempword = empty;
        }
        file.close();
    }    
    
}

bool gameLaunched() {
    bool launched = false;
    std::vector<std::string> launch;
    kbFileToVector(launch);

    if(launch[1] == "true"){
        launched = true;
    }    
    return launched;
}

bool appLaunched() { // will read from the status file to see if game is launched
    bool launched = false; // declares launched variable to be returned later
    std::vector<std::string> launch;
    kbFileToVector(launch);
    
    if(launch[0] == "true"){
        launched = true;
    }
    return launched;
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
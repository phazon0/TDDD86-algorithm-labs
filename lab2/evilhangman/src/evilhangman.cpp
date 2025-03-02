/*
 * File: evilhangman.cpp
 * ------------
 * This file is an implementation of the game hangman but with an evil twist in cpp.
 * author: ludin609 & ferpe211
 * since:  20/09/2024
 */


#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

//Parses dictonary from text file into an unordered_map with the size of the word as key
unordered_map<int,unordered_set<string>> parseDict(string fileName){
    //Reads the inputed textfile and creates a grid same as described in the text file
    std::ifstream inputFile(fileName);

    std::string line;
    unordered_map<int,unordered_set<string>> dict;

    while(getline(inputFile, line) ) {
        dict[line.length()].insert(line);
    }

    inputFile.close();
    return dict;
}
//Prints the remaining words from an unordered_set of strings
void printRemainingWords(const unordered_set<string>& wordSet){
    cout << "Printing Remaining words:" << endl;
    for(string word: wordSet){
        cout<< word<< endl;
    }
}
//Algorithm for finding the largest subset of words in a set of words
//This is done by generating a pattern from every word and using it as a key in a map
//By then comparing the size of the different collections of words that follow different patterns, we can pinpoint which subset is the largest
//Example: wordSet = {"word", "worm", "test"}, target character = 'o'
//-> Pattern ['-, 'o', '-', '-'] {2} (Refers to "worm" and "word")
//-> Pattern ['-, '-', '-', '-'] {1} (Refers to "test")
unordered_set<string> filterLargestSubSet(const unordered_set<string>& wordSet, char targetChar){
    map<forward_list<char>, unordered_set<string>> wordSetPermutations;
    for(string word: wordSet){
        forward_list<char> pattern;
        for(char letter:word){
            if(letter == targetChar){
                pattern.push_front(letter);
            }else{
                pattern.push_front('-');
            }
        }
        wordSetPermutations[pattern].insert(word);
    }
    unordered_set<string> largestSubSet;
    int length=0;
    //Compares and obtains the largest collection of wordSet permutations
    for(const auto &patternSet: wordSetPermutations){
        int currentSize =  wordSetPermutations[patternSet.first].size();
        if(length <= currentSize){
            length = currentSize;
            largestSubSet = wordSetPermutations[patternSet.first];
        }
    }
    return largestSubSet;

}

//Loop where user has to guess letters untill the word is found or there are no guesses left
void guessingLoop(int& guessesCount, unordered_set<string>& wordSet, bool showWords){
    char currentChar;
    vector<char> usedChars;

    while((wordSet.size() > 1) && guessesCount >=1){

        std::cout << "Current word is: ";
        auto wordSetIterator = wordSet.begin();
        for(char letter:*wordSetIterator){
            if(find(usedChars.begin(), usedChars.end(), letter)!=usedChars.end()){
                std::cout << letter;
            }else{
                std::cout << "-";
            }
        }
        std::cout << "\nAmount of guesses left: " << guessesCount-- << std::endl;

        std::cout << "Enter new character: ";
        std::cin >> currentChar;
        cin.clear();
        std::string ignoreLine;
        std::getline(cin, ignoreLine);

        if(cin.fail() || find(usedChars.begin(), usedChars.end(), currentChar)!=usedChars.end() || !(ALPHABET.find(tolower(currentChar))<ALPHABET.length())){
            std::cout << "Character already used or invalid!" << std::endl;
            continue;
        }
        usedChars.push_back(tolower(currentChar));
        wordSet = filterLargestSubSet(wordSet,currentChar);

        if(showWords){
            printRemainingWords(wordSet);
        }


    }

}
//Loop for setting word length, guessesCount, showWords based on the users input during the configuration stage of the program
void parseUserConfiguration(int & wordLength, int& guessesCount, bool& showWords, const unordered_map<int,unordered_set<string>>& dictonary){
    do{
        std::cout << "Enter length of word: ";
        std::cin >> wordLength;
        //Clears cin object if fails
        //when fail, invalid input is still present in the stream, therefore we have to read new line which we ignore
        cin.clear();
        std::string ignoreLine;
        std::getline(cin, ignoreLine);
    }
    while(cin.fail() || wordLength <= 0 || (dictonary.find(wordLength) == dictonary.end()));


    std::cout << "\nEnter amount of guesses: ";
    std::cin >> guessesCount;


    char remainingWordsChoice;
    std::cout << "\nShow remaining words? y/n: ";
    std::cin >> remainingWordsChoice;
    showWords = tolower(remainingWordsChoice)=='y';
}

//Game method for assembling the game
int game() {
    int wordLength;
    int guessesCount;
    bool showWords;
    unordered_map<int,unordered_set<string>> dictonary = parseDict("dictionary.txt");
    cout << "Welcome to Hangman." << endl;

    parseUserConfiguration(wordLength, guessesCount,showWords, dictonary);

    //Obtains a set of words that fit the word length
    unordered_set<string> wordSet = dictonary.at(wordLength);

    guessingLoop(guessesCount, wordSet,showWords);

    if(wordSet.size() > 1){
        cout << "Better luck next time!" << endl;

    }else{
        cout << "Congratulations!" << endl;

    }
    auto wordSetIterator = wordSet.begin();
    cout << "The word was: " << *wordSetIterator << endl;
    return 0;
}


//Handles the replay feature so the player can choose to play again
int main(){
    char playAgainChoice;
    do{
        game();
        std::cout << "Do you want to play again (y/n) ";
        std::cin >> playAgainChoice;
    }while (tolower(playAgainChoice) == 'y');
}

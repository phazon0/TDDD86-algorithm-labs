/*
 * File: wordChain.cpp
 * ------------
 * This file generates a word chain based on two given words by the user.
 * author: ludin609 & ferpe211
 * since:  24/09/2024
 */

#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";


//Parses a text file into a vector of strings
vector<string> parseDictionary(const string& textFile){
    std::ifstream inputFile(textFile);

    std::string line;
    vector<string> dictonary;

    while(getline(inputFile, line) ) {
        dictonary.push_back(line);
    }
    inputFile.close();
    return dictonary;
}

//Returns wheter two words are differentiated by one letter
bool isNeighbour(const string& word1, const string& word2){
    int n = word1.length();
    int counter = 0;
    for (int i=0; i<n; i++){
        if(word1[i] == word2[i]){
            counter++;
        }
    }
    return (counter == n-1);
}

//Obtains a vector of strings that are neighbour to the given word
vector<string> getNeighbours(const string& word, const vector<string>& dictonary){
    vector<string> neighbours;
    for (string validWord : dictonary){
        if(validWord.size() == word.size()){
            if(isNeighbour(word,validWord)){
                neighbours.push_back(validWord);
            }
        }
    }
    return neighbours;
}

//Prints out a stack
void printStack(stack<string> stackToPrint){
    while(!stackToPrint.empty()) {
            cout << stackToPrint.top() <<" ";
            stackToPrint.pop();
        }
          cout << endl;
}

//Bredth first search algorithm for finding a word chain
stack<string> wordChain(const string& start, const string& target, const vector<string>& dictonary){
    queue<stack<string>> availablePaths;
    stack<string> startStack;
    startStack.push(start);
    availablePaths.push(startStack);
    vector<string> usedWords;
    while (!availablePaths.empty()) {
        stack<string> firstPath = availablePaths.front();
        availablePaths.pop();
        string top = firstPath.top();
        if(target == top){
            return firstPath;
        }else{
            for (string neighbour : getNeighbours(firstPath.top(), dictonary)){
                if(!(find(usedWords.begin(), usedWords.end(), neighbour) != usedWords.end())){
                    stack<string> chainCopy = firstPath;
                    chainCopy.push(neighbour);
                    availablePaths.push(chainCopy);
                    usedWords.push_back(neighbour);
                }
            }
        }
    }
    return startStack;}


//I/O for the program
int main() {
    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;

    cout << "Please type two words: ";

    string arguments;
    getline(cin, arguments);
    int divider = arguments.find(" ");
    string startWord = arguments.substr(0,divider );
    string targetWord = arguments.substr(divider+1,arguments.length()-1 );
    vector<string> dict = parseDictionary("dictionary.txt");
    printStack(wordChain(startWord, targetWord, dict));


    return 0;
}

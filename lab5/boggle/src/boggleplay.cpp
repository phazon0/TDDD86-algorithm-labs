/*
 * File: boggleplay.cpp
 * ------------
 * This is the source file for the handling all IO for the boggle game
 * Executes one human turn allowing the user to input words and prints all possible words during the computer turn
 * author: ludin609 & ferpe211
 * since:  26/11/2024
 */
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include "Boggle.h"
#include "bogglemain.h"
#include "strlib.h"
#include <algorithm>
#include <cmath>  // For abs()

vector<string> usedWords;

/*
 * Outputs board in a readable way thats easy to understand for the user
 */
void showBoard(const Boggle& boggle){
    for (int i = 0; i < boggle.BOARD_SIZE; ++i){
        for (int j = 0; j < boggle.BOARD_SIZE; ++j){
        cout << boggle.board.get(i, j);
        }
        cout << endl;
    }
}

/*
 * Method for performing the computers turn
 * Prints IO
 * Finds all possbible valid word combinations
 */
void computerTurn(const Boggle& boggle, const Lexicon& lexicon){
    cout << "Its my turn!" << endl;
    set<string> words = boggle.getWordsinBoard( lexicon);
    int size = words.size();
    int score = 0;
    cout << "My words ("<<size<<") : {";
    for (string word: words){
        cout<<word<<" ,";
        score+=word.length() -3;
    }
    cout<<"}" <<endl;
    cout<<"My Score: "<<score<<endl;
    cout<<"Ha ha ha, I destroyed you. Better luck next time, puny human! "<<endl;
}

/*
 * Method for executing the human turn
 * Reads user input
 * Checks if inputted word is valid
 */
void humanTurn(const Boggle& boggle, const Lexicon& lexicon){
    cout << "Its your turn!" << endl;
    int humanScore = 0;

    showBoard(boggle);
    string currentWord;
    while(true){
        do{
        cout << "Type a word or press enter to end your turn" << endl;
        getline(cin, currentWord);

        if(currentWord == ""){
            return;
        }

        }while(!boggle.isWordAccepted( currentWord, lexicon, usedWords));
            usedWords.push_back(currentWord);
            humanScore += currentWord.size() - 3;
            cout << "You found a new word "<<currentWord<<endl;
            cout << "Your words: (" <<usedWords.size() << "): {";
            for (string word: usedWords){
                cout<<word<<" ,";
            }
            cout<<"}" <<endl;
            cout<< "Your score: " << humanScore << endl;

    }

}

/*
 * Method for resetting the game, clearing usedWords vector
 */
void resetGame(){
    usedWords.clear();
}

/*
 * Plays one game of Boggle using the given boggle game state object.
 */
void playOneGame(const Boggle& boggle, const Lexicon& lexicon) {
    humanTurn(boggle, lexicon);
    computerTurn(boggle, lexicon);
    resetGame();
}



/*
 * Erases all currently visible text from the output console.
 */
void clearConsole() {
#if defined(_WIN32) || defined(_WIN64)
    std::system("CLS");
#else
    std::system("clear");
#endif
}

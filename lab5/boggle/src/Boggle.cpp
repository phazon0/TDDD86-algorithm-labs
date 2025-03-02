/*
 * File: Boggle.cpp
 * ------------
 * This is the source file for the Boggle object
 * Boggle stores a board of psuedo randomized characters of size BOARD_SIZE. Source file contains all logic for playing the boggle game,
 * e.g obtaining all possible words in the board and checking if inputted word can be created using letters adjecent to one another in the board
 * author: ludin609 & ferpe211
 * since:  26/11/2024
 */
#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"


static string CUBES[Boggle::NUM_CUBES] = {        // the letters on all 6 sides of every cube
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

/*
 * Recursively checks if each character in the word meets the required criteria (max distance is one cell from the previous character)
 */
bool validateWordRec(const Boggle& boggle, string& word, const int x, const int y){
    if(word == "")
        return true;
    char startChar = word[0];
    string wordLeft = word.erase(0,1);

    for (int i = 0; i < boggle.board.nRows; i++) {
        for (int j = 0; j < boggle.board.nCols; j++) {
            if(boggle.board.get(i,j) == startChar){
                if(abs(x-i)<=1 && abs(y-j)<=1){
                    if(validateWordRec(boggle,wordLeft,i,j))
                        return true;
                }
            }
        }
    }

return false;


}
/*
 * Returns if a word does exist in board
 */
bool isWordInBoard(const Boggle& boggle, string word){
    char startChar = word[0];
    vector<pair<int, int>> startPoints;
    for (int i = 0; i < boggle.board.nRows; i++) {
        for (int j = 0; j < boggle.board.nCols; j++) {
            if(boggle.board.get(i,j) == startChar){
                startPoints.push_back(make_pair(i,j));
            }
        }
    }
    string recWord = word.erase(0,1);
    for(pair<int, int> coord : startPoints){
        bool foundWord = validateWordRec(boggle, recWord, coord.first, coord.second);
        if(foundWord)
            return true;
    }
    return false;


}

/*
 * Returns if word fits the criteria for a valid word in board
 */
bool Boggle::isWordAccepted(string& word, const Lexicon& lexicon, vector<string>& usedWords) const{
    if(word.size() < 4)
        return false;


    auto firstOccurence = find(usedWords.begin(), usedWords.end(), word);
    if (firstOccurence != usedWords.end())
        return false;

    if(!lexicon.contains(word))
        return false;

    if(!isWordInBoard(*this, word))
        return false;

    return true;


}

/*
 * Returns if a position is already in use by usedPositions set in the param
 */
bool isUsedPosition(const set<pair<int, int>>& usedPositions, const pair<int, int> pos){
     if (std::find(usedPositions.begin(), usedPositions.end(), pos) != usedPositions.end()){
         return true;
     }
     return false;
}
/*
 * Returns if a position (i ,j ) is is adjecent to position (x , y)
 */
bool isAdjecent(int x, int y, int i, int j){
    if(!(abs(x-i)<=1 && abs(y-j)<=1))
        return false;
    if ((i==x && j==y))
         return false;

    return true;
}

/*
 * Method for finding word sequence using recursive backtracking
 */
void getWordRec(set<string>& words,const Boggle& boggle, const Lexicon& lexicon, const string& current, const int x, const int y, const set<pair<int, int>> usedPositions){
//hitta alla möjliga ord, för varje substring, kolla containsprefix från lexicon, om contains prefix, kolla om ord då lägg till i words
    //BASFALL
    if (!lexicon.containsPrefix(current)){
        return;
    }
    if (lexicon.contains(current) && current.length() >= 4){
        words.insert(current);
    }
    //RECURSIONSTEG
    for (int i = 0; i < boggle.board.nRows; i++) {
        for (int j = 0; j < boggle.board.nCols; j++) {
                if(isAdjecent(x, y, i ,j) && !isUsedPosition(usedPositions, make_pair(i, j))){
                        char cubeLetter = boggle.board.get(i, j);
                        string newCurrent = current + cubeLetter;
                        set<pair<int, int>> newUsedPositions = usedPositions;
                        newUsedPositions.insert(make_pair(i, j));
                        getWordRec(words, boggle, lexicon, newCurrent, i, j, newUsedPositions);
                    }
                }

    }
    return;
}
/*
 * Method for obtaining all words in board
 * Every cell in the board is looped through and passed into getWordRec to then be verified recursivly
 */
set<string> Boggle::getWordsinBoard(const Lexicon& lexicon) const{
    set<string> words;
    for (int i = 0; i < this->board.nRows; i++) {
        for (int j = 0; j < this->board.nCols; j++) {
            char start = this->board.get(i,j);
            set<string> empty;
            set<pair<int, int>> emptyPos;
            emptyPos.insert(make_pair(i, j));
            string newString = std::string(1, start);
            getWordRec(empty, *this, lexicon, newString, i, j, emptyPos);
            words.insert(empty.begin(), empty.end());
        }
    }
    return words;
}





Boggle::Boggle(){
    int counter = 0;
    board.resize(BOARD_SIZE, BOARD_SIZE);
    for (int i = 0; i < BOARD_SIZE; ++i){
        for (int j = 0; j < BOARD_SIZE; ++j){
            string cube = CUBES[counter];
            int randomNum = rand() % 6;

            char key = cube[randomNum];
            board.set(i,j,key);
            counter++;
        }
    }
    shuffle(board);

}

Boggle::Boggle(const string& config){
    int counter = 0;
    board.resize(BOARD_SIZE, BOARD_SIZE);
    for (int i = 0; i < BOARD_SIZE; ++i){
        for (int j = 0; j < BOARD_SIZE; ++j){

            char key = config[counter];
            board.set(i,j,key);
            counter++;
        }
    }

}





/*
 * File: Boggle.h
 * ------------
 * This is a header file for the Boggle.cpp
 * Boggle stores a board of psuedo randomized characters of size BOARD_SIZE. Source file contains all logic for playing the boggle game,
 * e.g obtaining all possible words in the board and checking if inputted word can be created using letters adjecent to one another in the board
 * author: ludin609 & ferpe211
 * since:  26/11/2024
 */


#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include <bits/stdc++.h>

#include "lexicon.h"
#include "grid.h"
#include <algorithm>
#include <cmath>  // For abs()

using namespace std;

class Boggle {
public:
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
    static const int BOARD_SIZE = 4;
    static const int NUM_CUBES = 16;   // the number of cubes in the game
    static const int CUBE_SIDES = 6;   // the number of sides on each cube
    Grid<char> board;     //Grid for storing each cube in the boggle board
    set<string> getWordsinBoard(const Lexicon& lexicon) const; //method for returning a set of words that exist in the board, used for computer turn
    bool isWordAccepted(string& word, const Lexicon& lexicon, vector<string>& usedWords) const; //Validates string word and checks if it exists and can be built in our board
    /*
     * Constructor for boggle
     * Creates a board object and places a cube on each cell with a random letter from the cube, the board is then shuffled
     */
    Boggle();
    /*
     * Constructor for boggle
     * Creates a board object when taking user input string where every letter is one cell on the board, only accepts string of length NUM_CUBES
     */
    Boggle(const string& config);
private:
};

#endif

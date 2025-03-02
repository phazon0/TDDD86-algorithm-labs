/*
 * TDDD86 Boggle
 * This file declares required function prototypes that are defined in
 * our provided bogglemain.cpp and your boggleplay.cpp that you will write.
 * See the respective .cpp files for implementation comments for each function.
 * Please do not modify this provided file.
 */

#ifndef _bogglemain_h
#define _bogglemain_h

#include "Boggle.h"
#include <string>
#include "lexicon.h"

using namespace std;
/*
 * Method for outputting an intro dialogue
 */
void intro();

/*
 * Method for playing one game of boggle, this method executes human turn and computers turn
 */
void playOneGame(const Boggle& boggle, const Lexicon& lexicon);

/*
 * Boolean for determining if user answers yes (Y) or no (N)
 */
bool yesOrNo(string prompt);
void clearConsole();

/*
 * Boolean for determining if string is in an alphabet
 */
bool isStringAlpha(string input);

#endif

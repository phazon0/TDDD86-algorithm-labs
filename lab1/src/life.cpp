/*
 * File: life.cpp
 * ------------
 * This file is an implementation of the game of life in cpp.
 * author: ludin609 & ferpe211
 */

#include <iostream>
#include "grid.h"
#include "lifeutil.h"
#include <fstream>

//Prints out a grid in the console
int printGrid(Grid<bool> grid){
    for (int row = 0; row< grid.numRows(); row++){
        std::string line;
        for (int column = 0; column< grid.numCols(); column++){
            //If cell has value true the cell is alive therefore we print 'X'
            if(grid.get(row, column)){
                  line += 'X';
            //If value false the cell is dead
            }else{
                line+= '-';
            }
        }
        std::cout << line << std::endl;
    }
    return 0;
}

//Determines if a cell is going to survive based on the number of alive neighbours and it's current state
bool willSurvive(int neighbours, bool isAlive){
       if (neighbours < 2){
           return false;
       }
       else if (neighbours == 2){
           return isAlive;
       }
       else if (neighbours == 3){
           return true;
       }
       return false;
}

int countNeighbours(int row, int column, Grid<bool> grid){
    int aliveNeighbours = 0;
    for (int neighbourRow = row-1; neighbourRow <= row+1; neighbourRow++){
        for (int neigbourColumn = column-1; neigbourColumn <= column+1; neigbourColumn++){
            if (neighbourRow == row && neigbourColumn == column){
                continue;
            }
            else{
                if(grid.inBounds(neighbourRow, neigbourColumn)){
                   if (grid.get(neighbourRow, neigbourColumn)){
                       aliveNeighbours++;
                   }
               }
            }
        }
    }
    return aliveNeighbours;
}


//Generates the next generation of the grid by looping through each cell and calculating its alive neighbours
Grid<bool> generateNextGen(Grid<bool> grid){
     Grid<bool> newGrid = Grid<bool>(grid.numRows(), grid.numCols());
     for (int row = 0; row< grid.numRows(); row++){
         for (int column = 0; column< grid.numCols(); column++){
             int aliveNeighbours = countNeighbours(row, column, grid);
             newGrid.set(row, column, willSurvive(aliveNeighbours, grid.get(row, column)));
         }

     }
     return newGrid;
}


//Parses and creates a grid from a given textfile using ifstream
Grid<bool> parseGrid(std::string textFile){
    //Reads the inputed textfile and creates a grid same as described in the text file
    std::ifstream inputFile(textFile);

    std::string line;
    int currentLine = 0;
    int rows = 0, columns = 0;
    Grid<bool> grid = Grid<bool>(rows, columns);

    while(getline(inputFile, line) ) {
        if(currentLine == 0) {
            rows = std::stoi(line);
        }else if (currentLine == 1){
            columns = std::stoi(line);
            //resize grid after found rows and columns
            grid.resize(rows, columns);
        }else {
           if(currentLine-2 >= rows){
               break;
           }
           for (int i = 0; i < columns; i++) {
               bool alive = line[i] == 'X';
               grid.set(currentLine-2,i, alive);
           }
        }
        currentLine++;
    }
    inputFile.close();
    return grid;
}


//Main method for the program that parses and creates the grid from a given textfile.
//Also controls user input for manipulating the grid
int main() {
    clearConsole();
    std::string fileName;
    std::cout << "Welcome to the TDDD86 Game of Life,\na simulation of the lifecycle of a bacteria colony.\nCells (X) live and die by the following rules:"
                 "- A cell with 1 or fewer neighbours dies.\n"
                 "- Locations with 2 neighbours remain stable.\n"
                 "- Locations with 3 neighbours will create life.\n"
                 "- A cell with 4 or more neighbours dies."  << std::endl;
    std::cout << "Grid input file name? ";
    std::cin >> fileName;
    Grid<bool> grid = parseGrid(fileName);



    //Main loop
    while(true){
        printGrid(grid);
        std::string choice;
        std::cout << "a)nimate, t)ick, q)uit?" << std::endl;
        std::cin >> choice;
        if (choice == "a"){
            for (int i = 0; i < 10; i++){
                grid = generateNextGen(grid);
                printGrid(grid);
                pause(100);
                clearConsole();
            }
        }
        else if (choice == "t"){
            grid = generateNextGen(grid);
        }
        else if (choice == "q"){
            std::cout << "Have a nice life" << std::endl;
            break;
        }
    }
    //End of program
    return 0;
}



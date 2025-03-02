/*
 * File: Tour.h
 * ------------
 * This is a header file for the Tour.cpp file
 * Tour object stores nodes that are circularly linked together and contains different methods for manipulating and understanding/visualizing the linked node list.
 * author: ludin609 & ferpe211
 * since:  01/10/2024
 */

#ifndef TOUR_H
#define TOUR_H

#include "Node.h"
#include "Point.h"


/*
 * Tour is a container of type linked circular list storing nodes
*/
class Tour {
public:
    /*
     * Constructor takes no arguments and initializes the first node with a nullptr
    */
    Tour();
    /*
     * Deconstructor, unallocates all nodes from the heap
     */
    ~Tour();
    /*
     * Loops through all nodes in the list and prints them
     */
    void show();
    /*
     * Draws graphical points for each node and lines connecting them using QGraphics
     */
    void draw(QGraphicsScene* scene);
    /*
     * Returns size of the list
     */
    int size();
    /*
     * Traverses all nodes calculating the distance between each pair and returns the total distance
     */
    double distance();
    /*
     * Inserts a node using a heuristic that finds the node closest to the one being inserted
     */
    void insertNearest(Point p);
    /*
     * Inserts a node using a heuristic that finds the lowest increment in distance when inserting
     */
    void insertSmallest(Point p);

private:
    //First node in the list
    Node* m_front;

};

#endif // TOUR_H

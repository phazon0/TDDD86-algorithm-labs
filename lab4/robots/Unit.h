/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 * Updated for TDDD86, 2021.
 */

#ifndef UNIT_H
#define UNIT_H

#include "utilities.h"
#include <QGraphicsScene>

/* Root class for all pieces on the board.
 * Subclasses are Robot, Hero and Junk.
 */
class Unit {
public:

    /*
     * Create a unit at a random position
     */
    Unit();

    /*
    * Create unit at given point
    */
    Unit(const Point& p);

    virtual ~Unit(){}

    /*
    * Return Point representation of Unit
    */
    Point asPoint() const;

    /*
    * Am I in the same square as u?
    */
    bool at(const Unit& u) const;


    /*
    * Take one step closer to point
    */
    virtual void moveTowards(const Point&);


    /*
    * Teleport. Does not check for collision
    */
    void teleport();

    /*
    * Euclidean distance to u
    */
    double distanceTo(const Unit& u) const;

    /*
     * Returns wheter unit is alive, false by default
     */
    virtual bool isAlive() const;
    /*
     * Draws object using QGraphics
     */
    virtual void draw(QGraphicsScene *scene) const;
    /*
     * Return wheter unit has crashed, false by default
     */
    virtual bool isToBeJunked() const;
    /*
     * Crash logic for units
     */
    virtual void doCrash();
    /*
     * Creates a clone of a unit, allocates memory in the heap. Abstract by default
     */
    virtual Unit* clone() const = 0;

private:
    int x;  // x position of this unit
    int y;  // y position of this unit
    // private helpers
    void checkBounds();
};

#endif // UNIT_H

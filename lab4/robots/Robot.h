/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef ROBOT_H
#define ROBOT_H

#include "Unit.h"
#include <QGraphicsScene>

class Robot : public Unit {
    bool toBeJunked = false;

public:

    /*
     * did not crash yet
     */
    bool isAlive() const override;

    /*
     * Crashes and remembers it
     */
    void doCrash() override;

    /*
     * Return whether the robot crashed
     */
    bool isToBeJunked() const override;

    /*
    * Draws this robot onto the given QGraphicsScene.
    */
    void draw(QGraphicsScene* scene) const override;
    /*
     * Allocates a new robot object in the heap
     */
    Unit* clone() const override;

};

#endif // ROBOT_H

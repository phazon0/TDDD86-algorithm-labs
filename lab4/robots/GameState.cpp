/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 * Updated for TDDD86, 2021.
 */

#include "GameState.h"
#include "utilities.h"
#include "constants.h"
#include <iostream>


GameState::GameState(int numberOfRobots) {
   for (int i = 0; i < numberOfRobots; i++) {
        Robot robot;
        while(!isEmpty(robot)){
            robot =  Robot();
        }
        units.push_back(new Robot(robot));
    }
    teleportHero();
}

GameState::~GameState() {
    for (size_t i = 0; i < units.size(); ++i) {
        delete units[i];
    }
}


void GameState::draw(QGraphicsScene *scene) const {
    scene->clear();
    hero.draw(scene);
    for (const Unit* unit : units){
        unit->draw(scene);
    }

}

void GameState::teleportHero() {
    do hero.teleport();
    while (!isEmpty(hero));
}

void GameState::moveRobots() {
    for(Unit* robot: units)
        robot->moveTowards(hero.asPoint());
}


void GameState::updateCrashes() {
    for(Unit* unit1 : units){
        for(Unit* unit2 : units){
            if(unit2 != unit1){
                if(unit1->at(*unit2)){
                    unit1->doCrash();
                    unit2->doCrash();
                }
            }
        }
    }
}

int GameState::countToBeJunked()const{
    int numberDestroyed =0;
    for (const Unit* unit : units){
        if(unit->isToBeJunked()){
            numberDestroyed++;

        }
        return numberDestroyed;
    }

}
void GameState::junkTheCrashed() {
    for (size_t i = 0; i < units.size(); ++i) {
        if (units[i]->isToBeJunked()) {
            Junk* junk = new Junk(units[i]->asPoint());

            delete units[i];

            // Replace the old Unit pointer with the new Junk pointer
            units[i] = junk;
        }
    }
}


bool GameState::someRobotsAlive() const {
    for(const Unit* unit : units){
        if(unit->isAlive())
            return true;
    }
    return false;

}


bool GameState::heroDead() const {
    for (const Unit* unit : units){
        if(hero.at(*unit)){
            return true;
        }
    }

    return false;
}


void GameState::moveHeroTowards(const Point& dir) {
    hero.moveTowards(dir);
}

Point GameState::getHeroAsPoint() const {return hero.asPoint();}


GameState::GameState(const GameState& gamestate){
    for (size_t i = 0; i < units.size(); ++i) {
        delete units[i];
    }
    units.clear();

    for (const auto& unit : gamestate.units) {
        if (unit) {
            units.push_back(unit->clone());
        }
    }

    hero = gamestate.hero;
}


GameState& GameState::operator=(const GameState& gamestate) {

    if (this == &gamestate) {
        return *this;
    }



    GameState temp(gamestate);
    std::swap(units, temp.units);
    std::swap(hero, temp.hero);


    return *this;
}
/*
 * Free of robots and junk
 */
bool GameState::isEmpty(const Unit& target) const {
    for(const Unit* unit : units){
        if(unit->at(target))
            return false;
    }
    return true;

}


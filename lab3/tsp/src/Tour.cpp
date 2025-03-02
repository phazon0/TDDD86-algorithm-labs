/*
 * File: Tour.cpp
 * ------------
 * This is a Tour object
 * Tour object stores nodes that are circularly linked together and contains different methods for manipulating and understanding/visualizing the linked node list.
 * author: ludin609 & ferpe211
 * since:  01/10/2024
 */

#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"
#include <limits>

Tour::Tour()
{
    m_front = nullptr;
}


Tour::~Tour()
{
    Node* current = m_front;
    do {
        Node* next = current->next;
        delete current;
        current = next;
    }
    while(current != m_front);

}



void Tour::show()
{
    Node* current = m_front;
    do {
        std::cout << current->point << std::endl;
        current = current->next;
    }
    while(current != m_front);
}

void Tour::draw(QGraphicsScene *scene)
{
    Node* current = m_front;
    do {
        Node* next = current->next;
        current->point.draw(scene);
        current->point.drawTo(next->point, scene);
        current = current->next;
    }
    while(current != m_front);

}

int Tour::size()
{
    int size = 0;
    Node* current = m_front;
    do {
        size++;
        current = current->next;
    }
    while(current != m_front);
    return size;

}

double Tour::distance()
{
    double totalDistance = 0;
    Node* current = m_front;
    do {
        Node* next = current->next;
        totalDistance += current->point.distanceTo(next->point);
        current = current->next;
    }
    while(current != m_front);

    return totalDistance;
}

void Tour::insertNearest(Point p)
{
    if(m_front == nullptr){
        m_front = new Node(p, nullptr);
        m_front->next = m_front;
    }else {
    Node* current = m_front;
    Node* closest = current;
    double nearestDistance = std::numeric_limits<double>::max();
    do {
        double currentDistance = current->point.distanceTo(p);
        if ( currentDistance <= nearestDistance){
            closest = current;
            nearestDistance = currentDistance;
        }
        current = current->next;
    }
    while(current != m_front);
    Node* next = closest->next;
    closest->next = new Node(p, next);
    }

}

void Tour::insertSmallest(Point p)
{
    if(m_front == nullptr){
        m_front = new Node(p, nullptr);
        m_front->next = m_front;
    }else {
    Node* current = m_front;
    Node* closest = current;
    double smallestDistance = std::numeric_limits<double>::max();
    do {
        Node* next = current->next;
        double currentDistance = current->point.distanceTo(p);
        double nextDistance = next->point.distanceTo(p);
        double parallelDistance = current->point.distanceTo(next->point);
        double totalDistance = currentDistance +nextDistance- parallelDistance;
        if(totalDistance <= smallestDistance){
           smallestDistance = totalDistance;
           closest = current;
        }
        current = current->next;
    }
    while(current != m_front);
    Node* next = closest->next;
    closest->next = new Node(p, next);
    }
}

/*
 * File: trailblazer.cpp
 * ------------
 * This is the source file for the handling pathfinding in BasicGraph
 * The file implements four different pathfinding algorithms
 * DFS, BFS, Dikjstra and A*
 * author: ludin609 & ferpe211
 * since:  10/12/2024
 */
#include "costs.h"
#include "pqueue.h"
#include "trailblazer.h"
#include <queue>
#include <limits.h>

using namespace std;

/*
 * Method for reseting all data in a graph
 */
void reset(BasicGraph& graph){
    for(Vertex* vertex : graph.getNodeSet()){
        vertex->resetData();
    }
    for(Arc* arc : graph.getArcSet()){
        arc->resetData();
    }
}
/*
 * Method for backtracking a path based on the "previous" member in Vertex
 */
void backtrack(vector<Vertex*>& path, Vertex* current){
    Vertex* backtrack = current;

    while(backtrack != nullptr){
        path.push_back(backtrack);
        backtrack = backtrack->previous;
    }
}

/*
 * Recursive DFS algorithm
 */
bool depthFirstSearchRec(vector<Vertex*>& path,Vertex* current, Vertex* target ){
    current->setColor(GREEN);
    current->visited = true;
    if(current->name == target->name){
        backtrack(path, current);

        return true;
    }
    for(Arc* arc : current->arcs){
        Vertex* next = arc->finish;

        if(!next->visited){
           next->setColor(YELLOW);
           next->previous = current;
           bool pathFound = depthFirstSearchRec(path, next, target);
           if(pathFound)
               return pathFound;
        }

    }
    current->setColor(GRAY);
    return false;

}



/*
 * Calls depthFirstSearchRec to perform a DFS search
 */
vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    vector<Vertex*> path;
    depthFirstSearchRec( path,start, end);
    reset(graph);
    return path;
}

/*
 * BFS implementation
 */
vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    vector<Vertex*> path;
    std::queue<Vertex*> queue;
    Vertex* current = start;
    queue.push(current);
    while (!queue.empty()){
        current = queue.front();
        queue.pop();
        current->setColor(GREEN);
        current->visited = true;
        if(current->name == end->name){
            backtrack(path, current);

            break;
        }
        for(Arc* arc : current->arcs){
            Vertex* next = arc->finish;
            if(!next->visited){
                next->visited = true;
                next->previous = current;
                next->setColor(YELLOW);
                queue.push(next);
            }
        }

    }
    reset(graph);
    return path;
}


/*
 * An implementation of Dijkstras algorithm
 */
vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    vector<Vertex*> path;

    for(Vertex* vertex : graph.getNodeSet()){
        vertex->cost =INT_MAX;
    }

    Vertex* current = start;

    current->cost = 0;
    PriorityQueue<Vertex*> pqueue;

    pqueue.enqueue(current, 0);


    while(!pqueue.isEmpty()){
        current = pqueue.dequeue();
        current->setColor(GREEN);
        current->visited = true;
        if(current->name == end->name){
            backtrack(path, current);


            break;
        }
        for(Arc* arc : current->arcs){
            Vertex* next = arc->finish;
            int cost = current->cost + arc->cost;
            if(cost < next->cost){
                next->visited = true;
                next->setColor(YELLOW);

                next->cost = cost;
                next->previous = current;
                pqueue.enqueue(next, cost);
            }
        }
    }

    reset(graph);
    return path;
}

/*
 * Implementation of the A* algorithm
 * Makes use of the heurstic member in Vertex to predict which nodes to search to accomplish its goal more efficiently
 */
vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    vector<Vertex*> path;

    for(Vertex* vertex : graph.getNodeSet()){
        vertex->cost =INT_MAX;
    }

    Vertex* current = start;

    current->cost = 0;
    PriorityQueue<Vertex*> pqueue;

    pqueue.enqueue(current, current->heuristic(end));


    while(!pqueue.isEmpty()){
        current = pqueue.dequeue();
        current->setColor(GREEN);
        current->visited = true;
        if(current->name == end->name){
           backtrack(path, current);

            break;
        }
        for(Arc* arc : current->arcs){
            Vertex* next = arc->finish;
            int cost = current->cost + arc->cost;
            if(cost < next->cost){
                next->visited = true;
                next->setColor(YELLOW);

                next->cost = cost;
                next->previous = current;
                pqueue.enqueue(next, ( cost + next->heuristic(end)));
            }
        }
    }

    reset(graph);
    return path;
}

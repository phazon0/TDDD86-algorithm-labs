/*
 * TDDD86 TSP
 * This client program uses your Tour class and contains the 'main'
 * function to open the input file and set up the program's primitive GUI.
 */

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <chrono>
#include <thread>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "Point.h"
#include "Tour.h"
#include <queue>





int main(int argc, char *argv[]) {





    QApplication a(argc, argv);

    string filename = "tsp100.txt";
    ifstream input;
    input.open(filename);

    // get dimensions
    int width;
    int height;
    input >> width;
    input >> height;

    // setup graphical window
    QGraphicsView *view = new QGraphicsView();
    QGraphicsScene *scene = new QGraphicsScene();
    view->setScene(scene);
    view->scale(1, -1); //screen y-axis is inverted
    view->setSceneRect(0, 0, width, height);
    view->show();

    // run insertion heuristic
    Tour tour;
    double x;
    double y;
    while (input >> x >> y) {
        Point p(x, y);
        tour.insertSmallest(p);
        //uncomment the 4 lines below to animate
       // tour.draw(scene);

        //std::chrono::milliseconds dura(50);
        //std::this_thread::sleep_for(dura);
        //a.processEvents();
    }
    cout << tour.distance() << endl;
    input.close();
    int size = tour.size();
    double distance =tour.distance();
    // print tour to standard output
    cout << "Tour distance: " << std::fixed << std::setprecision(4)
         << std::showpoint << distance << endl;
    cout << "Number of points: " << size << endl;

    // draw tour
    tour.draw(scene);
    return a.exec(); // start Qt event loop
}


/*
 * File: main.cpp
 * ------------
 * This is a source file for processing points in a 2-dimensional space.
 * Algorithms are used to calclulate lines that can be created with four or more points
 * author: ludin609 & ferpe211
 * since:  6/12/2024
 */

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include "Point.h"

// constants
static const int SCENE_WIDTH = 512;
static const int SCENE_HEIGHT = 512;




void render_points(QGraphicsScene* scene, const vector<Point>& points) {
    for(const auto& point : points) {
        point.draw(scene);
    }
}

void render_line(QGraphicsScene* scene, const Point& p1, const Point& p2) {
    p1.lineTo(scene, p2);
}

/*
 * Implementation of the fast algorithm
 * Each point p is treated like origo and then calclulates the slope for the rest of the points q.
 * The slopes are then stored in a vector which is sorted by ascending order.
 * The sorted list is then processed and each line containing 4 or more points is rendered.
 */
void fast(const vector<Point>& points, QApplication& a, QGraphicsScene* scene){
    auto begin = chrono::high_resolution_clock::now();
    //Comparator, compares slope value
    auto comp = [](pair<double, int> a, pair
                 <double,int> b) {
        return a.first < b.first;
  };
    //Algorithm
    for (int i = 0 ; i < points.size() ; ++i) {
        //Sets point with index i as origo and then stores q points with pair of (slope, index)
        vector<pair<double, int>> qPoints;
        for (int j = 0 ; j < points.size() ; ++j) {
            if(i != j){
                double slope = points.at(i).slopeTo(points.at(j));
                qPoints.push_back(make_pair(slope, j));
            }
        }
        std::sort(qPoints.begin(), qPoints.end(), comp);

        double currentSlope = 0;
        vector<int> collinearPoints;
        for(int k = 0; k < qPoints.size(); ++k){
            if(qPoints[k].first == currentSlope && (k != qPoints.size()-1)){
                collinearPoints.push_back(qPoints[k].second);
            }else{
                currentSlope = qPoints[k].first;

                if(collinearPoints.size() >= 3){
                    for(int index : collinearPoints){
                        render_line(scene, points.at(i), points.at(index));
                        a.processEvents();
                    }
                }
                collinearPoints.clear();
                collinearPoints.push_back(qPoints[k].second);

            }
        }
    }
    //Prints time it took
    auto end = chrono::high_resolution_clock::now();
    cout << "Computing line segments took "
         << std::chrono::duration_cast<chrono::milliseconds>(end - begin).count()
         << " milliseconds." << endl;
}

void brute(const vector<Point>& points, QApplication& a, QGraphicsScene* scene){
    int N = points.size();
    // sort points by natural order
    // makes finding endpoints of line segments easy
    auto begin = chrono::high_resolution_clock::now();

    // iterate through all combinations of 4 points
    for (int i = 0 ; i < N-3 ; ++i) {
        for (int j = i+1 ; j < N-2 ; ++j) {
            for (int k = j+1 ; k < N-1 ; ++k) {
                //only consider fourth point if first three are collinear
                if (points.at(i).slopeTo(points.at(j)) == points.at(i).slopeTo(points.at(k))) {
                    for (int m{k+1} ; m < N ; ++m) {
                        if (points.at(i).slopeTo(points.at(j)) == points.at(i).slopeTo(points.at(m))) {
                            render_line(scene, points.at(i), points.at(m));
                            a.processEvents(); // show rendered line
                        }
                    }
                }
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    cout << "Computing line segments took "
         << std::chrono::duration_cast<chrono::milliseconds>(end - begin).count()
         << " milliseconds." << endl;

}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // open file
    string filename = "mystery10089.txt";
    ifstream input;
    input.open(filename);

    // the vector of points
    vector<Point> points;

    // read points from file
    int N;
    int x;
    int y;

    input >> N;

    for (int i = 0; i < N; ++i) {
        input >> x >> y;
        points.push_back(Point(x, y));
    }
    input.close();

    // setup graphical window
    QGraphicsView *view = new QGraphicsView();
    QGraphicsScene *scene = new QGraphicsScene(0, 0, SCENE_WIDTH, SCENE_HEIGHT);
    view->setScene(scene);
    // draw points to screen all at once
    render_points(scene, points);
    view->scale(1, -1); //screen y-axis is inverted
    view->resize(view->sizeHint());
    view->setWindowTitle("Brute Force Pattern Recognition");
    view->show();
    sort(points.begin(), points.end());

    //brute(points, a, scene);

    fast(points, a, scene);

    return a.exec(); // start Qt event loop
}

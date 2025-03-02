/*
 * File: MyPriorityQueue.h
 * ------------
 * This is a header file and a source file for the ADT priority queue based on a heap implementation.
 * The priority queue makes use of a min heap implemented as a tree. The tree is stored as a MyVector, @see MyVector.h
 * author: ludin609 & ferpe211
 * since:  6/12/2024
 */

#ifndef MY_PRIORITY_QUEUE_H
#define MY_PRIORITY_QUEUE_H

#include "MyVector.h"
#include "MyException.h"
#include "Event.h"



template <typename T, typename C>
class MyPriorityQueue
{
    MyVector<T> vector_array;
    C strictly_larger_operator;

public:
    MyPriorityQueue();

    ~MyPriorityQueue();

    void push(const T& t);

    T top()const;

    void pop();

    bool empty()const;

  unsigned size() const;


private:

};


/*
 * Constructor, creates a MyVector object with type T
 */
template <typename T, typename C>
MyPriorityQueue<T,C>::MyPriorityQueue(){
    vector_array = MyVector<T>();
}


/*
 * Destructor, clears the MyVector
 */
template <typename T, typename C>
MyPriorityQueue<T,C>::~MyPriorityQueue(){
    vector_array.clear();
}


/*
 * Adds an element to the end of the list and then heapifies the MyVector
 */
template <typename T, typename C>
void MyPriorityQueue<T,C>::push(const T& t){
    vector_array.push_back(t);
    //Heapifies the array
    int currentPos=vector_array.size()-1;
    int parentPos = (currentPos-1)/2;
    while (currentPos > 0 && strictly_larger_operator(vector_array[parentPos], t) && (parentPos >= 0)){
        T temp = vector_array[parentPos];
        vector_array[parentPos] = t;
        vector_array[currentPos] = temp;
        currentPos = parentPos;
        parentPos = (currentPos-1)/2;
    }
}


/*
 * Returns the object with highest priority (highest up in the heap)
 */
template <typename T, typename C>
T MyPriorityQueue<T,C>::top()const{
    return vector_array[0];
}


/*
 * Removes the object with highest priority then heapifies the MyVector
 * This is done by swapping first and last element and then "swapping down" the top element until it is in the right place
 */
template <typename T, typename C>
void MyPriorityQueue<T,C>::pop(){
    vector_array[0] = vector_array[vector_array.size()-1];
    T t = vector_array[0];
    vector_array.pop_back();
    //Heapifies the array
    int size = vector_array.size();
    int currentPos=0;

    while (!((currentPos >= size/2) && (currentPos < size))){
        int leftChild = 2*currentPos + 1;
        int rightChild = 2*currentPos + 2;


        if( strictly_larger_operator(vector_array[rightChild], vector_array[leftChild])){
            if (strictly_larger_operator(vector_array[currentPos], vector_array[leftChild])){
                //Swaps left with curent
                T temp = vector_array[leftChild];
                vector_array[leftChild] = vector_array[currentPos];
                vector_array[currentPos] = temp;
                currentPos = leftChild;
                continue;
            }
        }else{
            if (strictly_larger_operator(vector_array[currentPos], vector_array[rightChild])){
                 //Swaps right with curent
                T temp = vector_array[rightChild];
                vector_array[rightChild] = vector_array[currentPos];
                vector_array[currentPos] = temp;
                currentPos = rightChild;
                continue;
            }
        }
        //Did not swap
        break;
    }
}


/*
 * Return if the MyVector is empty
 */
template <typename T, typename C>
bool MyPriorityQueue<T,C>::empty()const{
    return vector_array.empty();
}


/*
 * Returns the size of the MyVector
 */
template <typename T, typename C>
unsigned MyPriorityQueue<T,C>::size()const{
    return vector_array.size();
}

#endif // MY_PRIORITY_QUEUE_H

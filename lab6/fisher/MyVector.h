/*
 * File: MyVector.h
 * ------------
 * This is a header file and a source file for the ADT Vector array.
 * This vector allocates memory dynamicly based on how much the vector contains.
 * author: ludin609 & ferpe211
 * since:  4/12/2024
 */

#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include "MyException.h"
template<typename T>
void myVectorDeepCopy(T* from, T*& to, unsigned size){
    for(int i = 0; i<size; ++i){
        to[i] = from[i];
    }
}

template <typename T>
class MyVector
{

public:
    MyVector();

    ~MyVector();

    MyVector(const MyVector& other);

    MyVector& operator =(const MyVector& other);


    void push_back(const T&);

    void pop_back();

    T& operator[](unsigned i);

    const T& operator[](unsigned i)const;

    bool empty()const;

    T* begin();

    T* end();

    void clear();

    unsigned size()const;

private:
    T* storage = nullptr; //Pointer to first element
    unsigned m_capacity = 0; //Capacity of the array
    int m_size = 0; //The number of elements currently in the array

};

/*
 * Constructor setting capacity, size and allocating memory
 */
template<typename T>
MyVector<T>::MyVector(){
    m_capacity = 1;
    m_size = 0;
    storage = new T[m_capacity];
}


/*
 * Destructor freeing all dynamicly allocated memory
 */
template<typename T>
MyVector<T>::~MyVector(){
    delete [] storage;
}


/*
 * Copy constructor
 */
template<typename T>
MyVector<T>::MyVector(const MyVector& other){
    m_capacity = other.m_capacity;
    storage = new T[m_capacity];
    m_size = other.m_size;
    myVectorDeepCopy(other.storage, storage, other.size());
}


/*
 * Copy assignment operator using copy constructor and then swapping fields
 */
template<typename T>
MyVector<T>& MyVector<T>::operator =(const MyVector& other){
    if(this == &other)
        return *this;
    MyVector temp(other);
    std::swap(storage, temp.storage);
    std::swap(m_capacity, temp.m_capacity);
    std::swap(m_size, temp.m_size);
    return *this;
}


/*
 * Adds a new element att the end of the array and updating fields. Also doubles capacity if array is full
 */
template<typename T>
void MyVector<T>::push_back(const T& e){

    if(m_size == m_capacity){
        m_capacity *= 2;
        T* newStorage = new T[m_capacity];
        myVectorDeepCopy(storage, newStorage, m_size);
        delete [] storage;
        storage = newStorage;

    }
    storage[m_size] = e;
    m_size++;

}


/*
 * Removes the last element is the arrray
 */
template<typename T>
void MyVector<T>::pop_back(){
    m_size--;
}


/*
 * Returns element at index i
 */
template<typename T>
T& MyVector<T>::operator[](unsigned i){
    return storage[i];
}


/*
 * Returns a const ref to element at index i
 */
template<typename T>
const T& MyVector<T>::operator[](unsigned i)const{
    return storage[i];
}


/*
 * returns if array is empty
 */
template<typename T>
bool MyVector<T>::empty()const{
    return m_size <= 0;
}


/*
 * Clears the MyVector
 */
template<typename T>
void MyVector<T>::clear(){
    delete [] storage;
    m_capacity = 1;
    m_size = 0;
    storage = new T[m_capacity];
}


/*
 * Returns the size
 */
template<typename T>
unsigned MyVector<T>::size()const{
    return m_size;
}


/*
 * Returns pointer to first element in array
 */
template<typename T>
T* MyVector<T>::begin(){
    return storage;
}

/*
 * Returns pointer to last element in array
 */
template<typename T>
T* MyVector<T>::end(){
   return storage + m_size;
}


#endif // MY_VECTOR_H

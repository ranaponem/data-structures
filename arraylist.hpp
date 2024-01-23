#ifndef ARRAYLIST_HPP
#define ARRAYLIST_HPP

#include <iostream>
#include "comparison.hpp"
#include "constants.hpp"

template <typename T> class ArrayList{
protected:
    int length;
    T* array;
public:
    ArrayList(){
        length = 0;
        array = nullptr;
    }

    ArrayList(T* oldArray, int size){
        length = size;
        array = new T[size];
        for(int i = 0 ; i < size ; i++)
            array[i] = oldArray[i];
    }

    ~ArrayList(){
        delete[] array;
    }

    /**
     * @brief Adds an element to array list
     * 
     * @param elem Element to add to array list
    */
    void add(T elem){
        //Copying current array to a temporary array
        T* temp = new T[length];
        for(int i = 0 ; i < length ; i++)
            temp[i] = array[i];
        
        length++;

        //Realocating current array
        delete[] array;
        array = new T[length];

        //Copying temp array to current array
        for(int i = 0 ; i < length - 1 ; i++)
            array[i] = temp[i];

        //Inserting new value
        array[length-1] = elem;

        //Freeing temp array
        delete[] temp;
    }

    /**
     * @brief Adds all elements from an array to array list
     * 
     * @param elems Array of elements to add
     * @param numElems Number of elements to add
    */
    void add(T* elems, int numElems){
        //Copying current array to a temporary array
        T* temp = new T[length];
        for(int i = 0 ; i < length ; i++)
            temp[i] = array[i];
        
        length += numElems;

        //Realocating current array
        delete[] array;
        array = new T[length];

        //Copying temp array to current array
        for(int i = 0 ; i < length - 1 ; i++)
            array[i] = temp[i];

        //Inserting new values
        for(int i = 0 ; i < numElems ; i++){
            array[length - (numElems - i)] = elems[i];
        }

        //Freeing temp array
        delete[] temp;
    }

    /**
     * @brief Removes element at an index from the array list
     * 
     * @param index Index of the element to remove
    */
    void remove(int index){
        if(index < 0 || index >= length){
            std::cerr << "Out of bounds\n";
            return;
        }

        //Copying current array to a temporary array
        T* temp = new T[--length];
        for(int i = 0 ; i < index ; i++)
            temp[i] = array[i];

        for(int i = index; i < length; i++)
            temp[i] = array[i+1];

        //Realocating current array
        delete[] array;
        array = new T[length];

        //Copying temp array to current array
        for(int i = 0 ; i < length ; i++)
            array[i] = temp[i];

        //Freeing temp array
        delete[] temp;
    }

    /**
     * @brief Removes all elements from an index to another
     * 
     * @param startIndex First index of group of elements to remove
     * @param endIndex Last index of group of elements to remove
    */
    void remove(int startIndex, int endIndex){
        if(startIndex < 0 || startIndex >= length ||
           endIndex < 0   || endIndex >= length   ||
           startIndex >= endIndex){
            std::cerr << "Out of bounds\n";
            return;
        }

        if(startIndex == 0 && endIndex == length - 1){
            clear();
            return;
        }

        //Copying current array to a temporary array
        int numRemoved = (endIndex - startIndex) + 1;
        length -= numRemoved;
        T* temp = new T[length];
        for(int i = 0 ; i < startIndex ; i++)
            temp[i] = array[i];

        for(int i = startIndex; i < length; i++)
            temp[i] = array[i+numRemoved];

        //Realocating current array
        delete[] array;
        array = new T[length];

        //Copying temp array to current array
        for(int i = 0 ; i < length ; i++)
            array[i] = temp[i];

        //Freeing temp array
        delete[] temp;
    }

    /**
     * @brief Gets element at an index of the array list
     * 
     * @param index Index to get element from
     * 
     * @return Element at index if index isn't out of bounds, generic element otherwise
    */
    T get(int index){
        if(index < 0 || index >= length){
            std::cerr << "Out of bounds\n";
            return T();
        }
        return array[index];
    }

    /**
     * @brief Gets size of array list
     * 
     * @return Length of the array list
    */
    int size(){
        return length;
    }

    /**
     * @brief Checks if array list is empty
     * 
     * @return true if array list is empty, false otherwise
    */
    bool isEmpty(){
        return length == 0;
    }

    /**
     * @brief Clears array list
    */
    void clear(){
        if(length > 0){
            length = 0;
            delete[] array; 
        }
    }

    /**
     * @brief Tries to find an element in the array list
     * 
     * @param elem Element to find
     * 
     * @return Index of element in the array list or NOT_FOUND if element isn't in the array list
    */
    int find(T elem){
        for(int i = 0 ; i < length ; i++){
            if(array[i] == elem)
                return i;
        }
        return NOT_FOUND;
    }
};

template <typename T> class OrderedArrayList : public ArrayList<T>{
private:
    using ArrayList<T>::length;
    using ArrayList<T>::array;
    Comparison<T> comparison;   //Criteria for ordering
public:
    OrderedArrayList(Comparison<T> c){
        length = 0;
        array = nullptr;
        comparison = c;
    }

    OrderedArrayList(Comparison<T> c, T* elems, int numElems){
        length = 0;
        comparison = c;
        add(elems, numElems);
    }
    /**
     * @brief Adds element to ordered array list
     * 
     * @param elem Element to add
    */
    void add(T elem){
        //Finding index for new element
        int index = 0;
        while(index < length && comparison.compare(elem, array[index]) == 1)
            index++;

        //Copying old and new element to a temporary array
        T* temp = new T[++length];
        for(int i = 0 ; i < length ; i++){
            if(i < index)
                temp[i] = array[i];
            
            else if(i == index)
                temp[i] = elem;

            else
                temp[i] = array[i-1];
        }

        //Copying temporary array to current array
        delete[] array;
        array = new T[length];

        for(int i = 0 ; i < length ; i++)
            array[i] = temp[i];

        //Freeing temp
        delete[] temp;
    }

    /**
     * @brief Adds array of elements to ordered array list
     * 
     * @param elems Elements to add
     * @param numElems Number of new elements
    */
    void add(T* elems, int numElems){
        for(int i = 0 ; i < numElems ; i++)
            add(elems[i]);
    }

    /**
     * @brief Tries to find an element in the ordered array list
     * 
     * @param elem Element to find
     * 
     * @return Index of element in the array list or NOT_FOUND if element isn't in the array list
    */
    int find(T elem){
        int lp = 0, rp = length, mp;
        while(lp <= rp){
            mp = (rp + lp) / 2;
            switch(comparison.compare(elem, array[mp])){
                case -1:
                    rp = mp;
                    break;
                case 0:
                    return mp;
                case 1:
                    lp = mp;
            }
        }
        return NOT_FOUND;
    }
};

#endif
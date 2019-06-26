//
//  Pool.cpp
//  Pool
//
//  Created by Mariana on 1/25/19.
//  Copyright © 2019 Mariana. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cstddef>
#include <new>
#include "Pool.hpp"

//constructor
Pool::Pool(size_t elemSize, size_t blockSize){
    //initializes the element size and the block size of that element
    elemSize_ = elemSize;
    blockSize_ = blockSize;
    std::cout << "Initializing a pool with element size " << elemSize_ << " and block size "<< blockSize_ << std::endl;
}

//destructor
Pool::~Pool(){
    int i;
    int counter = 0;
    for( i = 0; i<numBlocks; i++){
        counter++;
        delete[] pool[i];
    }
    std::cout << "Deleting "  << counter << " blocks" << std::endl;
    delete[] pool;
    
    
}


void* Pool::allocate(){
    //allocate memory on the pool and on the block
    //check if there is space, if there is not then grow
    //if freelist += nulptr
    //grow
    //decrement freecells
    //increment livecells
    //go to addrress that it points to, set freelist to it.
    if (free == nullptr) {
        grow();
    }
    //std::cout << &free  <<" &free before" << std::endl;
    char* temp;
    temp = free;
    
    free= *reinterpret_cast<char**>(free);
    //std::cout << &free  <<"  &free after" << std::endl;
    freecells--;
    std::cout << "Cell allocated at " << reinterpret_cast<char**>(temp) << std::endl;
    livecells++;
    
    //return reinterpret_cast<void*>(temp);
    return temp;
}


void Pool::grow(){
    //check if there is space, if there is not then grow
    //if freelist += nulptr
    //grow
    if(pool==nullptr){
        std::cout << "Expanding pool..." << std::endl;
        pool = new char*[1];
        pool[0] = new char[elemSize_*blockSize_];
        char* temp = pool[0];
        free = temp;
        link(free); //link(temp)
        numBlocks++;
        freecells+=blockSize_;
    }
    else {
        std::cout << "Expanding pool..." << std::endl;
        char* temp = new char[elemSize_*blockSize_];
        char** tempPool = new char* [numBlocks+1];
        
        for (int i=0; i<numBlocks+1; i++){
            tempPool[i] = pool[i];
        }
        
        tempPool[numBlocks+1] = temp;
        free = temp;
        link(tempPool[numBlocks+1]);
        delete[] pool;
        pool = tempPool;
        
        numBlocks++;
        freecells+=blockSize_;
    }
}

void Pool::link(char* n){
    //connects all the elements allocated in the pool
    char* p = n;
    std::cout  << "Linking cells at starting at " << static_cast<void*>(free) << std::endl;
    for (int i=0; i<blockSize_-1; i++){
        new (p) char*(p+elemSize_);
        p+=elemSize_;
    }
    new (p) char*(nullptr);
    
    
}

void Pool::deallocate(void* pointer){
    //take a temporary freelist
    //and freelists point before and now freelist is what it was
    //increase freecells
    //decrement livecells
    char* temp;
    temp=free;
    
    free = reinterpret_cast<char*>(pointer);
    new (free) char*(temp);
    freecells++;
    std::cout << "Cell deallocated at " << pointer << std::endl;
    livecells--;
}


void Pool::profile(){
    //print out live and free cells and keep track of the used and free cells
    //output live and free cells
    //while temp is not  null
    //output
    std::cout << "\nLive cell: " << livecells << " Free cell: " << freecells << std::endl;
    std::cout << "Free list: " << reinterpret_cast<void*>(free)<< "\n" << std::endl;
    
    char* temp=free;
    while(temp != nullptr){
        std::cout << reinterpret_cast<void*>(temp) << std::endl;
        temp=*(reinterpret_cast<char**>(temp));
    }
    
    std::cout << "\n";
}



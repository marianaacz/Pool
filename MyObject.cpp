//  MyObject.cpp
//  Pool
//  Created by Mariana on 1/25/19.
//  Copyright © 2019 Mariana. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cstddef>
#include <new>
#include "MyObject.hpp"
#include "Pool.hpp"

//constructor, used to initialize the list
MyObject* MyObject::create(int id, const std::string& name) {
    return new MyObject(id, name);
}

//Initialized a pool object of type pool
Pool MyObject::pool(sizeof(MyObject));

//function used to overwrite the operator new using the pool class
void* MyObject::operator new(size_t){
    return pool.allocate();
}

//function used to overwrite the operator delete using the pool class
void MyObject::operator delete(void *pointer){
    pool.deallocate(pointer);
}

//function to keep track of the used and free cells
void MyObject::profile(){
    pool.profile();
}

std::ostream& operator<<(std::ostream& out, const MyObject& obj){
    out<<obj.id;
    return out;
}



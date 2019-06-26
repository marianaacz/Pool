//
//  MyObject.hpp
//  Pool
//
//  Created by Mariana on 1/25/19.
//  Copyright © 2019 Mariana. All rights reserved.
//

#include "Pool.hpp"
#include <string>
#ifndef MyObject_h
#define Myobject_h
class MyObject {
    
    
public:
    //function used to return a pointer to the object created
    static MyObject* create(int id, const std::string& name);
    
    //function used to overwrite the operator new using the pool class
    static void* operator new(size_t elemsize);
    
    //function used to overwrite the operator delete using the pool class
    static void operator delete(void* pointer);
    
    //function to keep track of the used and free cells
    static void profile();
    
    friend std::ostream& operator<<(std::ostream& out, const  MyObject& obj);
private:
    static Pool pool;
    std::string name;
    int id;
    
private:
    
    //constructor, used to initialize the list
    MyObject(int i, const std::string& nm): name(nm) {
        id = i;
    }
    
};


#endif


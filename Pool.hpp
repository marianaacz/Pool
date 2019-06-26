//
//  Pool.hpp
//  Pool
//
//  Created by Mariana on 1/25/19.
//  Copyright © 2019 Mariana. All rights reserved.
//

#ifndef Pool_h
#define Pool_h


class Pool {
public:
    //constructor, used to initialize all the objects in the class
    Pool(size_t elemSize, size_t blockSize=5);
    
    //destructor, used to delete all the objects before initialized
    ~Pool();
    
    //used to get a pointer inside a pre-allocated block for a new object
    void* allocate();
    
    //used to remove an object from that pool block
    void deallocate(void*);
    
    //used to keep track of the free and used cells
    void profile();
    
private:
    char** pool;
    char* free;
    int numBlocks=0;
    void grow();
    void link(char*);
    int freecells = 0;
    int livecells = 0;
    size_t elemSize_;
    size_t blockSize_;
    
};

#endif

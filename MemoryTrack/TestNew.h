//
//  TestNew.h
//  MemoryTrack
//
//  Created by FreeBlank on 17/8/13.
//  Copyright © 2017年 pClass. All rights reserved.
//

#ifndef TestNew_h
#define TestNew_h

#include <stdio.h>

class TestNew {
public:
    TestNew();
    ~TestNew();
    void* operator new(size_t size);
    
private:
    int *test2;
    int test;
};

#endif /* TestNew_h */

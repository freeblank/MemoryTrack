//
//  main.cpp
//  MemoryTrack
//
//  Created by FreeBlank on 17/8/6.
//  Copyright © 2017年 pClass. All rights reserved.
//

#include <iostream>
#include "TestNew.h"


class ObjectTest {
public:
    int i_test1;
    char i_test2;
    char i_test3;
};

class ObjectTest2 {
public:
    char i_test2;
    int i_test1;
    char i_test3;
};

#include "DefineHack.h"
int main(int argc, const char * argv[]) {
    int* i_objectTest1 = new int[20];
    i_objectTest1[1] = 20;
    MemoryTrack::getInstance()->dump();
    
    delete[] i_objectTest1;
    MemoryTrack::getInstance()->dump();
    
    ObjectTest *i_objectTest2 = new ObjectTest();
    ObjectTest2 *i_objectTest3 = new ObjectTest2();
    MemoryTrack::getInstance()->dump();
    
    ObjectTest2 *i_objectTest4 = new(i_objectTest3) ObjectTest2();
    i_objectTest4->i_test1 = 1;
    MemoryTrack::getInstance()->dump();
    
    delete i_objectTest2;
    delete i_objectTest3;
    MemoryTrack::getInstance()->dump();
    
    TestNew *i_testNew = new TestNew();
    MemoryTrack::getInstance()->dump();
    delete i_testNew;
    MemoryTrack::getInstance()->dump();
    
    return 0;
}
#include "UndefineHack.h"

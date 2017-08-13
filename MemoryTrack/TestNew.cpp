//
//  TestNew.cpp
//  MemoryTrack
//
//  Created by FreeBlank on 17/8/13.
//  Copyright © 2017年 pClass. All rights reserved.
//

#include "TestNew.h"
#include <stdlib.h>

#include "DefineHack.h"
TestNew::TestNew() {
    test2 = new int[20];
}
#include "UndefineHack.h"

void* TestNew::operator new(size_t size) {
    return malloc(size);
}

#include "DefineHack.h"
TestNew::~TestNew() {
    delete test2;
}
#include "UndefineHack.h"

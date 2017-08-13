//
//  AllocHack.cpp
//  MemoryTrack
//
//  Created by FreeBlank on 17/8/7.
//  Copyright © 2017年 pClass. All rights reserved.
//

#include "AllocHack.h"

#undef malloc
#undef realloc
#undef free
#undef new

#include <stdio.h>
#include <stdlib.h>



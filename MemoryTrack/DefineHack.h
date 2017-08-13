//
//  MemoryHack.h
//  MemoryTrack
//
//  Created by FreeBlank on 17/8/8.
//  Copyright © 2017年 pClass. All rights reserved.
//

#ifndef DefineHack_h
#define DefineHack_h

#ifdef ENABLE_MEMORY_TRACK
    #include "MemoryTrack.h"

    #define malloc(size) (malloc_custom(size, __FILE__, __LINE__))
    #define realloc(ptr, size) (realloc_custom(ptr, size, __FILE__, __LINE__))
    #define free(ptr) (free_custom(ptr))

    #define new TraceInfo(__FILE__, __LINE__) & new
#endif

#endif /* DefineHack_h */

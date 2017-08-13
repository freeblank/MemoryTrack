//
//  UndefineHack.h
//  MemoryTrack
//
//  Created by FreeBlank on 17/8/13.
//  Copyright © 2017年 pClass. All rights reserved.
//

#ifndef UndefineHack_h
#define UndefineHack_h

#ifdef ENABLE_MEMORY_TRACK
    #undef malloc
    #undef realloc
    #undef free
    #undef new
#endif

#endif /* UndefineHack_h */

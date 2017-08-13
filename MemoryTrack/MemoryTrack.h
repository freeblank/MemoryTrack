//
//  MemoryTrack.h
//  MemoryTrack
//
//  Created by FreeBlank on 17/8/6.
//  Copyright © 2017年 pClass. All rights reserved.
//

#ifndef MemoryTrack_h
#define MemoryTrack_h

#ifdef ENABLE_MEMORY_TRACK

#include <stdio.h>
#include <string>
#include <map>


class TraceInfo {
public:
    TraceInfo(const char *i_filename, int i_line) : filename(i_filename) , line(i_line) {}
    
public:
    std::string filename;
    int line;
};


typedef struct _PointerInfo {
    std::string key;
    size_t size;
} PointerInfo;

class MemoryTrack {
public:
    static MemoryTrack* getInstance();
    
    MemoryTrack();
    ~MemoryTrack();
    
    void recordMemory(void *ptr, size_t size);
    void recordMemoryMore(void *ptr, const char* filename, int line);
    void removeMemory(void *ptr);
    
    void dump();
    
private:
    std::map<void*, PointerInfo> _mapPointers;
    std::map<std::string, size_t> _mapSize;
};

template<class T> inline T* operator&(const TraceInfo& trace_info, T* ptr) {
    MemoryTrack::getInstance()->recordMemoryMore(ptr, trace_info.filename.c_str(), trace_info.line);
    return ptr;
}

void* malloc_custom(size_t size, const char* filename, int line);
void* realloc_custom(void* ptr, size_t size, const char* filename, int line);
void free_custom(void *ptr);


void* operator new(size_t size);
void* operator new[](size_t size);

void operator delete(void* ptr) throw();
void operator delete[](void* ptr) throw();
#endif

#endif /* MemoryTrack_h */

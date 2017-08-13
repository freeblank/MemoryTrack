//
//  MemoryTrack.cpp
//  MemoryTrack
//
//  Created by FreeBlank on 17/8/6.
//  Copyright © 2017年 pClass. All rights reserved.
//

#include "MemoryTrack.h"
#ifdef ENABLE_MEMORY_TRACK

#include <sstream>
#include <iostream>

static MemoryTrack g_memoryTrack;
static bool g_bTrack = true;

MemoryTrack* MemoryTrack::getInstance() {
    return &g_memoryTrack;
}

MemoryTrack::MemoryTrack() {
    _mapPointers.clear();
    _mapSize.clear();
    
    g_bTrack = true;
}

MemoryTrack::~MemoryTrack() {
    g_bTrack = false;
    
    _mapPointers.clear();
    _mapSize.clear();
}

void MemoryTrack::recordMemory(void *ptr, size_t size) {
    PointerInfo i_info;
    i_info.size = size;
    _mapPointers[ptr] = i_info;
    
}
void MemoryTrack::recordMemoryMore(void *ptr, const char* filename, int line) {
    PointerInfo &i_info = _mapPointers[ptr];
    if (i_info.key.empty()) {   //placement new will not allocate new memory
        std::stringstream ss_key;
        ss_key<<filename<<":"<<line;
        i_info.key = ss_key.str();
        _mapSize[i_info.key] = i_info.size;
    }
}

void MemoryTrack::removeMemory(void *ptr) {
    std::map<void*, PointerInfo>::iterator it_pointer = _mapPointers.find(ptr);
    if (it_pointer == _mapPointers.end()) {
        return;
    }
    
    std::map<std::string, size_t>::iterator it_size = _mapSize.find(it_pointer->second.key);
    if (it_size == _mapSize.end()) {
        return;
    }
    it_size->second -= it_pointer->second.size;
    
    if (it_size->second == 0) {
        _mapSize.erase(it_size);
        _mapPointers.erase(it_pointer);
    }
    
}

void MemoryTrack::dump() {
    std::cout << "dump memory info:" << std::endl;
    for (std::map<std::string, size_t>::iterator it=_mapSize.begin(); it!=_mapSize.end(); ++it) {
        std::cout << it->first.c_str() << "\t\t" << it->second << std::endl;
    }
    if (_mapSize.size() == 0) {
        std::cout << "all memory is free" << std::endl;
    }
    std::cout << std::endl;
}


void* malloc_custom(size_t size, const char* filename, int line) {
    void *ptr = malloc(size);
    MemoryTrack::getInstance()->recordMemory(ptr, size);
    MemoryTrack::getInstance()->recordMemoryMore(ptr, filename, line);
    
    return ptr;
}

void* realloc_custom(void* ptr, size_t size, const char* filename, int line) {
    MemoryTrack::getInstance()->removeMemory(ptr);
    
    ptr = realloc(ptr, size);
    MemoryTrack::getInstance()->recordMemory(ptr, size);
    MemoryTrack::getInstance()->recordMemoryMore(ptr, filename, line);
    
    return ptr;
}

void free_custom(void *ptr) {
    MemoryTrack::getInstance()->removeMemory(ptr);
    
    free(ptr);
}

void* operator new(size_t size) {
    void* ptr = malloc(size);
    if (g_bTrack) {
        g_bTrack = false;
        MemoryTrack::getInstance()->recordMemory(ptr, size);
        g_bTrack = true;
    }
    
    return ptr;
}


void* operator new[](size_t size) {
    void* ptr = malloc(size);
    
    if (g_bTrack) {
        g_bTrack = false;
        MemoryTrack::getInstance()->recordMemory(ptr, size);
        g_bTrack = true;
    }
    
    
    return ptr;
}

void operator delete(void* ptr) throw() {
    if (g_bTrack) {
        g_bTrack = false;
        MemoryTrack::getInstance()->removeMemory(ptr);
        g_bTrack = true;
    }
    
    free(ptr);
}
void operator delete[](void* ptr) throw() {
    if (g_bTrack) {
        g_bTrack = false;
        MemoryTrack::getInstance()->removeMemory(ptr);
        g_bTrack = true;
    }
    
    free(ptr);
}

#endif

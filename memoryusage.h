#ifndef MEMORYUSAGE_H
#define MEMORYUSAGE_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <memory>
#include <numeric>

struct memoryusage
{
    int mem_total = 0;
    int mem_avail = 0;
    int mem_free = 0;
};

class MemoryUsage
{
private:
    memoryusage _mem_use;

public:
    MemoryUsage();
    ~MemoryUsage();

    memoryusage get_memory_usage();
    void update_memory_values();
};

#endif // MEMORYUSAGE_H

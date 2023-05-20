#include "memoryusage.h"

MemoryUsage::MemoryUsage() { update_memory_values(); }
MemoryUsage::~MemoryUsage() {}

void MemoryUsage::update_memory_values()
{
    // update values from /proc/meminfo
    std::ifstream input_data("/proc/meminfo");
    if (!input_data)
    {
        std::cerr << "File can not be opened << std::endl";
    }
    std::string line;
    while (input_data >> line)
    {
        if (line == "MemTotal:")
        {
            input_data >> _mem_use.mem_total;
        }
        if (line == "MemAvailable:")
        {
            input_data >> _mem_use.mem_avail;
        }
        if (line == "MemFree:")
        {
            input_data >> _mem_use.mem_free;
        }
    }
}

memoryusage MemoryUsage::get_memory_usage()
{
    update_memory_values();
    return _mem_use;
}

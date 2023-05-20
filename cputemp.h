#ifndef CPUTEMP_H
#define CPUTEMP_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <memory>
#include <numeric>

struct cputemp
{
    std::vector<int> thermal_zone = std::vector<int>(8,0);
};

class CPUTemp
{
private:
    cputemp _cpu_temperature;

public:
    CPUTemp();
    ~CPUTemp();

    cputemp get_cpu_temp();
    void update_cpu_temp_values();
};

#endif // CPUTEMP_H

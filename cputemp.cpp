#include "cputemp.h"

CPUTemp::CPUTemp() { update_cpu_temp_values(); }
CPUTemp::~CPUTemp() {}

void CPUTemp::update_cpu_temp_values()
{
    // update values from /sys/class/thermal/thermal_zone*/temp
    for (size_t i = 0; i < 8; i++)
    {
        std::string file_path = "/sys/class/thermal/thermal_zone" + std::to_string(i) + std::string("/temp");
        std::ifstream input_data(file_path);
        if (!input_data)
        {
            std::cerr << "File can not be opened << std::endl";
        }
        input_data >> _cpu_temperature.thermal_zone[i];
        _cpu_temperature.thermal_zone[i] /= 1000;       // values obtained are *1000 deg C
    }
}

cputemp CPUTemp::get_cpu_temp()
{
    update_cpu_temp_values();
    return _cpu_temperature;
}

#ifndef NETWORKSTATS_H
#define NETWORKSTATS_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <memory>
#include <numeric>

struct networkstats
{
    int transmit_data_lo = 0;
    int receive_data_lo = 0;
    int transmit_data_eth = 0;
    int receive_data_eth = 0;
    int transmit_data_wl = 0;
    int receive_data_wl = 0;
};

class NetworkStats
{
private:
    networkstats _net_stat;

public:
    NetworkStats();
    ~NetworkStats();

    networkstats get_network_stats();
    void update_network_values();
};

#endif // NETWORKSTATS_H

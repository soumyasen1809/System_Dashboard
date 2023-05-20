#include "networkstats.h"

NetworkStats::NetworkStats() { update_network_values(); }
NetworkStats::~NetworkStats() {}

// void NetworkStats::update_network_values()
// {
//     // update values from /proc/net/dev
//     std::ifstream input_data("/proc/net/dev");
//     if (!input_data)
//     {
//         std::cerr << "File can not be opened << std::endl";
//     }
//     std::string line;
//     while (std::getline(input_data, line))
//     {
//         if (line.find("lo") != std::string::npos) // loopback
//         {
//             std::istringstream ss(line);
//             std::string token;
//             std::getline(ss, token, ':');
//             for (size_t i = 0; i < 2; i++)
//             {
//                 std::getline(ss, token, ' ');
//             }
//             _net_stat.receive_data_lo = std::stoi(token);

//             for (size_t i = 0; i < 41; i++)
//             {
//                 std::getline(ss, token, ' ');
//             }
//             _net_stat.transmit_data_lo = std::stoi(token);
//         }

//         if (line.find("en") != std::string::npos) // ethernet
//         {
//             std::istringstream ss(line);
//             std::string token;
//             std::getline(ss, token, ':');
//             for (size_t i = 0; i < 3; i++) // this get the receive bytes (for en: i < 2, for lo: i < 3)
//             {
//                 std::getline(ss, token, ' ');
//             }
//             _net_stat.receive_data_eth = std::stoi(token);

//             for (size_t i = 0; i < 35; i++) // this get the transmit bytes (for en: i < 37, for lo: i < 43)
//             {
//                 std::getline(ss, token, ' ');
//             }
//             _net_stat.transmit_data_eth = std::stoi(token);
//         }
//     }
// }

// updated code using /sys/class/net/...
void NetworkStats::update_network_values()
{
    // Get exact names of the supported devices
    // update values from /proc/net/dev
    std::string lo_name = "", eth_name = "", wl_name = "";
    {
        std::ifstream input_data("/proc/net/dev");
        if (!input_data)
        {
            std::cerr << "File can not be opened << std::endl";
        }
        std::string line;
        while (std::getline(input_data, line))
        {
            if (line.find("lo") != std::string::npos) // loopback
            {
                std::istringstream ss(line);
                std::string token;
                std::getline(ss, token, ':');
                token.erase(remove(token.begin(), token.end(), ' '), token.end());
                lo_name = token;
            }
            if (line.find("en") != std::string::npos) // Ethernet
            {
                std::istringstream ss(line);
                std::string token;
                std::getline(ss, token, ':');
                token.erase(remove(token.begin(), token.end(), ' '), token.end());
                eth_name = token;
            }
            if (line.find("wl") != std::string::npos) // Wireless
            {
                std::istringstream ss(line);
                std::string token;
                std::getline(ss, token, ':');
                token.erase(remove(token.begin(), token.end(), ' '), token.end());
                wl_name = token;
            }
        }
    }

    // For loopback:
    // update values from /sys/class/net/lo/statistics/{rx_bytes, tx_bytes}
    {
        std::string file_path = "/sys/class/net/" + lo_name + std::string("/statistics/tx_bytes"); // transmit, lo
        std::ifstream input_data(file_path);
        if (!input_data)
        {
            std::cerr << "File can not be opened << std::endl";
        }
        input_data >> _net_stat.transmit_data_lo;
    }

    {
        std::string file_path = "/sys/class/net/" + lo_name + std::string("/statistics/rx_bytes"); // receive, lo
        std::ifstream input_data(file_path);
        if (!input_data)
        {
            std::cerr << "File can not be opened << std::endl";
        }
        input_data >> _net_stat.receive_data_lo;
    }

    // For ethernet (en)
    // update values from /sys/class/net/enp7s0/statistics/{rx_bytes, tx_bytes}
    {
        std::string file_path = "/sys/class/net/" + eth_name + std::string("/statistics/tx_bytes"); // transmit, en
        std::ifstream input_data(file_path);
        if (!input_data)
        {
            std::cerr << "File can not be opened << std::endl";
        }
        input_data >> _net_stat.transmit_data_eth;
    }

    {
        std::string file_path = "/sys/class/net/" + eth_name + std::string("/statistics/rx_bytes"); // receive, en
        std::ifstream input_data(file_path);
        if (!input_data)
        {
            std::cerr << "File can not be opened << std::endl";
        }
        input_data >> _net_stat.receive_data_eth;
    }

    // For wireless (wl)
    // update values from /sys/class/net/wlp0s20f3/statistics/{rx_bytes, tx_bytes}
    {
        std::string file_path = "/sys/class/net/" + wl_name + std::string("/statistics/tx_bytes"); // transmit, wl
        std::ifstream input_data(file_path);
        if (!input_data)
        {
            std::cerr << "File can not be opened << std::endl";
        }
        input_data >> _net_stat.transmit_data_wl;
    }

    {
        std::string file_path = "/sys/class/net/" + wl_name + std::string("/statistics/rx_bytes"); // receive, wl
        std::ifstream input_data(file_path);
        if (!input_data)
        {
            std::cerr << "File can not be opened << std::endl";
        }
        input_data >> _net_stat.receive_data_wl;
    }
}

networkstats NetworkStats::get_network_stats()
{
    update_network_values();
    return _net_stat;
}

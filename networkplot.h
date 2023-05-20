#ifndef NETWORKPLOT_H
#define NETWORKPLOT_H

#include <QDialog>
#include <QMessageBox>
#include <QDebug>
#include <QThread>
#include <QTimer>
#include <unistd.h>
#include "networkstats.h"

namespace Ui
{
    class NetworkPlot;
}

class NetworkPlot : public QDialog
{
    Q_OBJECT

public:
    explicit NetworkPlot(QWidget *parent = nullptr);
    ~NetworkPlot();

private slots:
    void show_net_stats_plot_lo();
    void network_stats_realtimeDataSlot_lo();

    void show_net_stats_plot_eth();
    void network_stats_realtimeDataSlot_eth();

    void show_net_stats_plot_wl();
    void network_stats_realtimeDataSlot_wl();

private:
    Ui::NetworkPlot *ui;

    static std::vector<int> data_lo;
    static std::vector<int> data_eth;
    static std::vector<int> data_wl;
    NetworkStats net_stats = NetworkStats();
};

#endif // NETWORKPLOT_H

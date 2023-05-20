#include <utility>
#include <functional>
#include "networkplot.h"
#include "ui_networkplot.h"

NetworkPlot::NetworkPlot(QWidget *parent) : QDialog(parent),
                                            ui(new Ui::NetworkPlot)
{
    ui->setupUi(this);
    this->setWindowTitle("Network Plot");
    this->setStyleSheet("background-color: white;");

    show_net_stats_plot_lo();
    show_net_stats_plot_eth();
    show_net_stats_plot_wl();
}

NetworkPlot::~NetworkPlot()
{
    this->deleteLater();
    delete ui;
}

std::vector<int> NetworkPlot::data_lo;
std::vector<int> NetworkPlot::data_eth;
std::vector<int> NetworkPlot::data_wl;

/// @brief find number of digits of the min and max elements
/// @param num the number
/// @return the number of digits of the number
int compute_number_digits(int num)
{
    int count = 0;
    while (std::abs(num) > 0)
    {
        count++;
        num /= 10;
    }

    return count;
}

/// @brief find the lower and upper limits for the plot
/// @param data a vector containing the most recent points
/// @return the lower and upper limits for the plot (Y-axis)
std::pair<int, int> compute_plot_limits(std::vector<int> data)
{
    int min = *std::min_element(data.begin(), data.end());
    int max = *std::max_element(data.begin(), data.end());

    int min_digits = compute_number_digits(min);
    int max_digits = compute_number_digits(max);

    int min_limit = 0;
    int max_limit = 0;

    /**
     * Say the number is 123, then the limit should be 100 and 1000
     * i.e. the limits are 10^{2} and 10^{3}
     * or, 10^{num of digits -1} and 10^{num of digits}
     */
    if (min_digits > 1)
    {
        min_limit = pow(10, (min_digits - 1));
    }
    if (max_digits > 1)
    {
        max_limit = pow(10, max_digits);
    }

    return std::make_pair(min_limit, max_limit);
}

void NetworkPlot::network_stats_realtimeDataSlot_lo()
{
    static QElapsedTimer time;            // https://stackoverflow.com/questions/69153879/replace-qtimeelapsed
    double key = time.elapsed() / 1000.0; // time elapsed since start of demo (in seconds)
    ui->widget_plotnetuse_lo->graph(0)->addData(key, net_stats.get_network_stats().receive_data_lo);
    ui->widget_plotnetuse_lo->graph(0)->setName("Receive data");
    ui->widget_plotnetuse_lo->graph(1)->addData(key, net_stats.get_network_stats().transmit_data_lo);
    ui->widget_plotnetuse_lo->graph(1)->setName("Transmit data");

    data_lo.push_back(net_stats.get_network_stats().receive_data_lo);
    data_lo.push_back(net_stats.get_network_stats().transmit_data_lo);
    while (data_lo.size() > 10)
    {
        data_lo.erase(data_lo.begin());
    }
    auto [min_limit, max_limit] = compute_plot_limits(data_lo);
    ui->widget_plotnetuse_lo->yAxis->setRange(min_limit, max_limit); // use a dynamic limit of the plot

    // make key axis range scroll with the data (at a constant range size of 10):
    ui->widget_plotnetuse_lo->xAxis->setRange(key, 10, Qt::AlignRight);
    ui->widget_plotnetuse_lo->replot();
}

void NetworkPlot::show_net_stats_plot_lo()
{
    // customPlot setup
    // https://www.qcustomplot.com/index.php/demos/realtimedatademo
    ui->widget_plotnetuse_lo->addGraph(); // blue line
    ui->widget_plotnetuse_lo->graph(0)->setPen(QPen(QColor::fromRgb(40, 110, 255)));
    ui->widget_plotnetuse_lo->addGraph(); // red line
    ui->widget_plotnetuse_lo->graph(1)->setPen(QPen(QColor::fromRgb(255, 110, 40)));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%s");
    ui->widget_plotnetuse_lo->xAxis->setTicker(timeTicker);
    ui->widget_plotnetuse_lo->xAxis->setTickLabels(false);
    ui->widget_plotnetuse_lo->xAxis->setLabel("time");
    ui->widget_plotnetuse_lo->axisRect()->setupFullAxesBox();
    // ui->widget_plotnetuse_lo->yAxis->setRange(100000, 10000000);
    ui->widget_plotnetuse_lo->yAxis->setLabel("bytes");
    ui->widget_plotnetuse_lo->legend->setVisible(true);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->widget_plotnetuse_lo->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget_plotnetuse_lo->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->widget_plotnetuse_lo->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget_plotnetuse_lo->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls MemoryPlot::memory_use_realtimeDataSlot:
    QTimer *net_dataTimer = new QTimer(this);
    connect(net_dataTimer, SIGNAL(timeout()), this, SLOT(network_stats_realtimeDataSlot_lo()));
    net_dataTimer->start(2000); // updating every 2 seconds
}

void NetworkPlot::network_stats_realtimeDataSlot_eth()
{
    static QElapsedTimer time;            // https://stackoverflow.com/questions/69153879/replace-qtimeelapsed
    double key = time.elapsed() / 1000.0; // time elapsed since start of demo (in seconds)
    ui->widget_plotnetuse_eth->graph(0)->addData(key, net_stats.get_network_stats().receive_data_eth);
    ui->widget_plotnetuse_eth->graph(0)->setName("Receive data");
    ui->widget_plotnetuse_eth->graph(1)->addData(key, net_stats.get_network_stats().transmit_data_eth);
    ui->widget_plotnetuse_eth->graph(1)->setName("Transmit data");

    data_eth.push_back(net_stats.get_network_stats().receive_data_eth);
    data_eth.push_back(net_stats.get_network_stats().transmit_data_eth);
    while (data_eth.size() > 10)
    {
        data_eth.erase(data_eth.begin());
    }
    auto [min_limit, max_limit] = compute_plot_limits(data_eth);
    ui->widget_plotnetuse_eth->yAxis->setRange(min_limit, max_limit); // use a dynamic limit of the plot

    // make key axis range scroll with the data (at a constant range size of 10):
    ui->widget_plotnetuse_eth->xAxis->setRange(key, 10, Qt::AlignRight);
    ui->widget_plotnetuse_eth->replot();
}

void NetworkPlot::show_net_stats_plot_eth()
{
    // customPlot setup
    // https://www.qcustomplot.com/index.php/demos/realtimedatademo
    ui->widget_plotnetuse_eth->addGraph(); // blue line
    ui->widget_plotnetuse_eth->graph(0)->setPen(QPen(QColor::fromRgb(40, 110, 255)));
    ui->widget_plotnetuse_eth->addGraph(); // red line
    ui->widget_plotnetuse_eth->graph(1)->setPen(QPen(QColor::fromRgb(255, 110, 40)));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%s");
    ui->widget_plotnetuse_eth->xAxis->setTicker(timeTicker);
    ui->widget_plotnetuse_eth->xAxis->setTickLabels(false);
    ui->widget_plotnetuse_eth->xAxis->setLabel("time");
    ui->widget_plotnetuse_eth->axisRect()->setupFullAxesBox();
    // ui->widget_plotnetuse_eth->yAxis->setRange(10000000, 5000000000);
    ui->widget_plotnetuse_eth->yAxis->setLabel("bytes");
    ui->widget_plotnetuse_eth->legend->setVisible(true);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->widget_plotnetuse_eth->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget_plotnetuse_eth->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->widget_plotnetuse_eth->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget_plotnetuse_eth->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls MemoryPlot::memory_use_realtimeDataSlot:
    QTimer *net_dataTimer = new QTimer(this);
    connect(net_dataTimer, SIGNAL(timeout()), this, SLOT(network_stats_realtimeDataSlot_eth()));
    net_dataTimer->start(2000); // updating every 2 seconds
}

void NetworkPlot::network_stats_realtimeDataSlot_wl()
{
    static QElapsedTimer time;            // https://stackoverflow.com/questions/69153879/replace-qtimeelapsed
    double key = time.elapsed() / 1000.0; // time elapsed since start of demo (in seconds)
    ui->widget_plotnetuse_wl->graph(0)->addData(key, net_stats.get_network_stats().receive_data_wl);
    ui->widget_plotnetuse_wl->graph(0)->setName("Receive data");
    ui->widget_plotnetuse_wl->graph(1)->addData(key, net_stats.get_network_stats().transmit_data_wl);
    ui->widget_plotnetuse_wl->graph(1)->setName("Transmit data");

    data_wl.push_back(net_stats.get_network_stats().receive_data_wl);
    data_wl.push_back(net_stats.get_network_stats().transmit_data_wl);
    while (data_wl.size() > 10)
    {
        data_wl.erase(data_wl.begin());
    }
    auto [min_limit, max_limit] = compute_plot_limits(data_wl);
    ui->widget_plotnetuse_wl->yAxis->setRange(min_limit, max_limit); // use a dynamic limit of the plot

    // make key axis range scroll with the data (at a constant range size of 10):
    ui->widget_plotnetuse_wl->xAxis->setRange(key, 10, Qt::AlignRight);
    ui->widget_plotnetuse_wl->replot();
}

void NetworkPlot::show_net_stats_plot_wl()
{
    // customPlot setup
    // https://www.qcustomplot.com/index.php/demos/realtimedatademo
    ui->widget_plotnetuse_wl->addGraph(); // blue line
    ui->widget_plotnetuse_wl->graph(0)->setPen(QPen(QColor::fromRgb(40, 110, 255)));
    ui->widget_plotnetuse_wl->addGraph(); // red line
    ui->widget_plotnetuse_wl->graph(1)->setPen(QPen(QColor::fromRgb(255, 110, 40)));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%s");
    ui->widget_plotnetuse_wl->xAxis->setTicker(timeTicker);
    ui->widget_plotnetuse_wl->xAxis->setTickLabels(false);
    ui->widget_plotnetuse_wl->xAxis->setLabel("time");
    ui->widget_plotnetuse_wl->axisRect()->setupFullAxesBox();
    // ui->widget_plotnetuse_wl->yAxis->setRange(1000, 10000000);
    ui->widget_plotnetuse_wl->yAxis->setLabel("bytes");
    ui->widget_plotnetuse_wl->legend->setVisible(true);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->widget_plotnetuse_wl->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget_plotnetuse_wl->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->widget_plotnetuse_wl->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget_plotnetuse_wl->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls MemoryPlot::memory_use_realtimeDataSlot:
    QTimer *net_dataTimer = new QTimer(this);
    connect(net_dataTimer, SIGNAL(timeout()), this, SLOT(network_stats_realtimeDataSlot_wl()));
    net_dataTimer->start(2000); // updating every 2 seconds
}
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include <QThread>
#include <QTimer>
#include <unistd.h>
#include "memoryplot.h"
#include "networkplot.h"
#include "cputempplot.h"
#include "memoryusage.h"
#include "networkstats.h"
#include "cputemp.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_checkBox_mem_usage_stateChanged(int arg1);

    void on_checkBox_net_stats_stateChanged(int arg1);

    void on_checkBox_cpu_temp_stateChanged(int arg1);

    void on_pushButton_refresh_all_clicked();

    void update_use_values();

    void on_pushButton_mem_plot_clicked();

    void on_pushButton_net_plot_clicked();

    void on_pushButton_cpu_temp_plot_clicked();

    void on_actionInfo_triggered();

private:
    Ui::MainWindow *ui;

    QTimer* timer;
    MemoryPlot mem_plot;
    NetworkPlot net_plot;
    CPUTempPlot cpu_temp_plot;

    MemoryUsage mem_use = MemoryUsage();
    NetworkStats net_stat = NetworkStats();
    CPUTemp cpu_temp = CPUTemp();

    
};
#endif // MAINWINDOW_H

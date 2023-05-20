#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("System Dashboard");
    this->setStyleSheet("background-color: white;");

    // Update a value continuously using the timer (multi-threaded)
    // https://stackoverflow.com/questions/40726814/update-a-value-continuously-in-qt-c
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_use_values()));
    // https://stackoverflow.com/questions/18958436/how-to-run-a-timer-inside-a-qthread
    timer->start(2000); // update the timer thread in background every 2 sec (doesn't block the GUI). Note: Interval 0 means to refresh as fast as possible
}

MainWindow::~MainWindow()
{
    this->deleteLater();
    delete ui;
}

void MainWindow::update_use_values()
{
    on_pushButton_refresh_all_clicked();
}

void MainWindow::on_checkBox_mem_usage_stateChanged(int arg1)
{
    if (arg1)
    {
        ui->lcdNumber_mem_avail->display(QString::number(mem_use.get_memory_usage().mem_avail));
        ui->lcdNumber_mem_free->display(QString::number(mem_use.get_memory_usage().mem_free));
        ui->lcdNumber_mem_total->display(QString::number(mem_use.get_memory_usage().mem_total));
    }
    else
    {
        ui->lcdNumber_mem_avail->display(0);
        ui->lcdNumber_mem_free->display(0);
        ui->lcdNumber_mem_total->display(0);
    }
}

void MainWindow::on_checkBox_net_stats_stateChanged(int arg1)
{
    if (arg1)
    {
        ui->lcdNumber_net_receive_lo->display(QString::number(net_stat.get_network_stats().receive_data_lo));
        ui->lcdNumber_net_transmit_lo->display(QString::number(net_stat.get_network_stats().transmit_data_lo));
        ui->lcdNumber_net_receive_eth->display(QString::number(net_stat.get_network_stats().receive_data_eth));
        ui->lcdNumber_net_transmit_eth->display(QString::number(net_stat.get_network_stats().transmit_data_eth));
        ui->lcdNumber_net_receive_wl->display(QString::number(net_stat.get_network_stats().receive_data_wl));
        ui->lcdNumber_net_transmit_wl->display(QString::number(net_stat.get_network_stats().transmit_data_wl));
    }
    else
    {
        ui->lcdNumber_net_receive_lo->display(0);
        ui->lcdNumber_net_transmit_lo->display(0);
        ui->lcdNumber_net_receive_eth->display(0);
        ui->lcdNumber_net_transmit_eth->display(0);
        ui->lcdNumber_net_receive_wl->display(0);
        ui->lcdNumber_net_transmit_wl->display(0);
    }
}

void MainWindow::on_checkBox_cpu_temp_stateChanged(int arg1)
{
    // add the lcdNumbers to a vector
    std::vector<QLCDNumber *> cpu_lcd_vec{ui->lcdNumber_cpu_temp_zone0, ui->lcdNumber_cpu_temp_zone1, ui->lcdNumber_cpu_temp_zone2, ui->lcdNumber_cpu_temp_zone3, ui->lcdNumber_cpu_temp_zone4, ui->lcdNumber_cpu_temp_zone5, ui->lcdNumber_cpu_temp_zone6, ui->lcdNumber_cpu_temp_zone7};

    if (arg1)
    {
        for (size_t i = 0; i < cpu_lcd_vec.size(); i++)
        {
            cpu_lcd_vec[i]->display(QString::number(cpu_temp.get_cpu_temp().thermal_zone[i]));
        }
    }
    else
    {
        for (size_t i = 0; i < cpu_lcd_vec.size(); i++)
        {
            cpu_lcd_vec[i]->display(0);
        }
    }
}

void MainWindow::on_pushButton_refresh_all_clicked()
{
    // Update all the values:
    // For memory use
    Qt::CheckState mem_use_current_state = ui->checkBox_mem_usage->checkState();
    qDebug() << QString("Qt Checkstate for memory use: ") << mem_use_current_state;

    if (mem_use_current_state == Qt::CheckState::Checked)
    {
        on_checkBox_mem_usage_stateChanged(1);
    }

    // For network stats
    Qt::CheckState net_stat_current_state = ui->checkBox_net_stats->checkState();
    qDebug() << QString("Qt Checkstate for network stat: ") << net_stat_current_state;

    if (net_stat_current_state == Qt::CheckState::Checked)
    {
        on_checkBox_net_stats_stateChanged(1);
    }

    // For CPU Temperature
    Qt::CheckState cpu_temp_current_state = ui->checkBox_cpu_temp->checkState();
    qDebug() << QString("Qt Checkstate for cpu temp: ") << cpu_temp_current_state;

    if (cpu_temp_current_state == Qt::CheckState::Checked)
    {
        on_checkBox_cpu_temp_stateChanged(1);
    }
}

void MainWindow::on_pushButton_mem_plot_clicked() { mem_plot.show(); }

void MainWindow::on_pushButton_net_plot_clicked() { net_plot.show(); }

void MainWindow::on_pushButton_cpu_temp_plot_clicked() { cpu_temp_plot.show(); }

void MainWindow::on_actionInfo_triggered()
{
    QString info_text;
    info_text = "Name:  System Dashboard \n";
    info_text += "Author:   Sen \n";
    info_text += "QT Version:   5.15.3 \n";
    info_text += "QMake Version:    3.1 \n";
    info_text += "Copyright:    2023 \n";
    QMessageBox::about(this, "About", info_text);
}

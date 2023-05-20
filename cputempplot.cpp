#include "cputempplot.h"
#include "ui_cputempplot.h"

CPUTempPlot::CPUTempPlot(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CPUTempPlot)
{
    ui->setupUi(this);
    this->setWindowTitle("CPU Temperature Plot");
    this->setStyleSheet("background-color: white;");

    show_cpu_temp_plot();
}

CPUTempPlot::~CPUTempPlot()
{
    this->deleteLater();
    delete ui;
}

void CPUTempPlot::cpu_temp_realtimeDataSlot()
{
    static QElapsedTimer time;            // https://stackoverflow.com/questions/69153879/replace-qtimeelapsed
    double key = time.elapsed() / 1000.0; // time elapsed since start of demo (in seconds)
    for (size_t i = 0; i < 8; i++)
    {
        ui->widget_plotcputemp->graph(i)->addData(key, cpu_temp.get_cpu_temp().thermal_zone[i]);
        ui->widget_plotcputemp->graph(i)->setName(QString("Thermal zone: ") + QString::number(i));
    }
    

    // make key axis range scroll with the data (at a constant range size of 10):
    ui->widget_plotcputemp->xAxis->setRange(key, 10, Qt::AlignRight);
    ui->widget_plotcputemp->replot();
}

void CPUTempPlot::show_cpu_temp_plot()
{
    // customPlot setup
    // https://www.qcustomplot.com/index.php/demos/realtimedatademo
    for (size_t i = 0; i < 8; i++)
    {
        ui->widget_plotcputemp->addGraph();
        ui->widget_plotcputemp->graph(i)->setPen(QPen(QColor::fromRgb( 255-(i*30), 100+(i*10), 0+(i*30) )));
    }
    

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%s");
    ui->widget_plotcputemp->xAxis->setTicker(timeTicker);
    ui->widget_plotcputemp->xAxis->setTickLabels(false);
    ui->widget_plotcputemp->xAxis->setLabel("time");
    ui->widget_plotcputemp->axisRect()->setupFullAxesBox();
    ui->widget_plotcputemp->yAxis->setRange(0, 100);
    ui->widget_plotcputemp->yAxis->setLabel("deg C");
    ui->widget_plotcputemp->legend->setVisible(true);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->widget_plotcputemp->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget_plotcputemp->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->widget_plotcputemp->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget_plotcputemp->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls MemoryPlot::memory_use_realtimeDataSlot:
    QTimer *cpuTemp_dataTimer = new QTimer(this);
    connect(cpuTemp_dataTimer, SIGNAL(timeout()), this, SLOT(cpu_temp_realtimeDataSlot()));
    cpuTemp_dataTimer->start(2000); // updating every 2 seconds
}
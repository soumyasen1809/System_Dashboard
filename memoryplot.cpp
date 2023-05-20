#include "memoryplot.h"
#include "ui_memoryplot.h"

MemoryPlot::MemoryPlot(QWidget *parent) : QDialog(parent),
                                          ui(new Ui::MemoryPlot)
{
    ui->setupUi(this);
    this->setWindowTitle("Memory Plot");
    this->setStyleSheet("background-color: white;");

    show_mem_use_plot();
}

MemoryPlot::~MemoryPlot()
{
    this->deleteLater();
    delete ui;
}

void MemoryPlot::memory_use_realtimeDataSlot()
{
    static QElapsedTimer time;            // https://stackoverflow.com/questions/69153879/replace-qtimeelapsed
    double key = time.elapsed() / 1000.0; // time elapsed since start of demo (in seconds)
    ui->widget_plotmem->graph(0)->addData(key, mem_use.get_memory_usage().mem_avail);
    ui->widget_plotmem->graph(0)->setName("Memory available");
    ui->widget_plotmem->graph(1)->addData(key, mem_use.get_memory_usage().mem_free);
    ui->widget_plotmem->graph(1)->setName("Memory free");
    ui->widget_plotmem->graph(2)->addData(key, mem_use.get_memory_usage().mem_total);
    ui->widget_plotmem->graph(2)->setName("Memory total");

    // make key axis range scroll with the data (at a constant range size of 10):
    ui->widget_plotmem->xAxis->setRange(key, 10, Qt::AlignRight);
    ui->widget_plotmem->replot();
}

void MemoryPlot::show_mem_use_plot()
{
    // customPlot setup
    // https://www.qcustomplot.com/index.php/demos/realtimedatademo
    ui->widget_plotmem->addGraph(); // blue line
    ui->widget_plotmem->graph(0)->setPen(QPen(QColor::fromRgb(40, 110, 255)));
    ui->widget_plotmem->addGraph(); // red line
    ui->widget_plotmem->graph(1)->setPen(QPen(QColor::fromRgb(255, 110, 40)));
    ui->widget_plotmem->addGraph(); // green line
    ui->widget_plotmem->graph(2)->setPen(QPen(QColor::fromRgb(110, 255, 40)));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%s");
    ui->widget_plotmem->xAxis->setTicker(timeTicker);
    ui->widget_plotmem->xAxis->setTickLabels(false);
    ui->widget_plotmem->xAxis->setLabel("time");
    ui->widget_plotmem->axisRect()->setupFullAxesBox();
    ui->widget_plotmem->yAxis->setRange(100000, 9000000);
    ui->widget_plotmem->yAxis->setLabel("kBytes");
    ui->widget_plotmem->legend->setVisible(true);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->widget_plotmem->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget_plotmem->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->widget_plotmem->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget_plotmem->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls MemoryPlot::memory_use_realtimeDataSlot:
    QTimer *mem_dataTimer = new QTimer(this);
    connect(mem_dataTimer, SIGNAL(timeout()), this, SLOT(memory_use_realtimeDataSlot()));
    mem_dataTimer->start(2000); // updating every 2 seconds
}

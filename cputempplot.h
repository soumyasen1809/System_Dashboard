#ifndef CPUTEMPPLOT_H
#define CPUTEMPPLOT_H

#include <QDialog>
#include <QMessageBox>
#include <QDebug>
#include <QThread>
#include <QTimer>
#include <unistd.h>
#include "cputemp.h"

namespace Ui {
class CPUTempPlot;
}

class CPUTempPlot : public QDialog
{
    Q_OBJECT

public:
    explicit CPUTempPlot(QWidget *parent = nullptr);
    ~CPUTempPlot();

private slots:
    void show_cpu_temp_plot();
    void cpu_temp_realtimeDataSlot();

private:
    Ui::CPUTempPlot *ui;

    CPUTemp cpu_temp = CPUTemp();
};

#endif // CPUTEMPPLOT_H

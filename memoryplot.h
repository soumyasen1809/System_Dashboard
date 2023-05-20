#ifndef MEMORYPLOT_H
#define MEMORYPLOT_H

#include <QDialog>
#include <QMessageBox>
#include <QDebug>
#include <QThread>
#include <QTimer>
#include <unistd.h>
#include "memoryusage.h"

namespace Ui
{
    class MemoryPlot;
}

class MemoryPlot : public QDialog
{
    Q_OBJECT

public:
    explicit MemoryPlot(QWidget *parent = nullptr);
    ~MemoryPlot();

private slots:
    void show_mem_use_plot();
    void memory_use_realtimeDataSlot();

private:
    Ui::MemoryPlot *ui;

    MemoryUsage mem_use = MemoryUsage();
};

#endif // MEMORYPLOT_H

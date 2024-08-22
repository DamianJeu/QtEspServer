#ifndef CHARTWINDOW_H
#define CHARTWINDOW_H

#include <QObject>
#include <QtCharts>
#include <QChartView>
#include <QMainWindow>

class ChartWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChartWindow(QWidget *parent = nullptr);
    ~ChartWindow();

private:
    QChartView *chartView;
    QChart *chart;
    QLineSeries *series;
    QValueAxis *axisX;
    QValueAxis *axisY;


};

#endif // CHARTWINDOW_H

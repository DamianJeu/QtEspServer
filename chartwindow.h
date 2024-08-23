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

public slots:

    void clearChart();
    void addNewSample(double point);
    void setNewMaxY(double maxY);
    void setNewMinY(double minY);
    void setXValue(quint16 newXValue);

private:
    QChartView *chartView;
    QChart *chart;
    QLineSeries *series;
    QValueAxis *axisX;
    QValueAxis *axisY;

    quint16 m_xValue;
    double m_maxY;

};

#endif // CHARTWINDOW_H

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

signals:

    void closeWindow();

private:
    QChartView *chartView;
    QChart *chart;
    QLineSeries *series;
    QValueAxis *axisX;
    QValueAxis *axisY;
    QPushButton *pushButton;

    quint16 m_xValue;
    double m_maxY;


    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // CHARTWINDOW_H

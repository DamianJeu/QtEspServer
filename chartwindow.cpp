#include "chartwindow.h"

ChartWindow::ChartWindow(QWidget *parent)
    : QMainWindow(nullptr),
    chart{new QChart()},
    series{new QLineSeries(chart)},
    axisX{new QValueAxis(chart)},
    axisY{new QValueAxis(chart)},
    chartView{new QChartView(this)}
{
    // Dodanie danych do serii

    series->append(0, 6);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 4);
    series->append(10, 5);

    chart->createDefaultAxes();

    axisY->setTickCount(10);
    axisY->setMax(10);
    axisY->setMin(0);
    axisY->applyNiceNumbers();
    axisY->setTickType(QValueAxis::TicksFixed);

    axisX->setMax(100);
    axisX->setMin(0);
    axisX->setLabelFormat("%d");
    axisX->setTickCount(10);
    axisX->applyNiceNumbers();
    axisX->setTickType(QValueAxis::TicksFixed);
    axisX->setTitleText("Odczyt");

    chart->legend()->hide();
    chart->setTitle("Data");
    chart->setTheme(QChart::ChartThemeBlueCerulean);
    chart->addSeries(series);
    chart->addAxis(axisY, Qt::AlignLeft);
    chart->addAxis(axisX, Qt::AlignBottom);

    series->attachAxis(axisY);
    series->setColor(Qt::red);
    series->attachAxis(axisX);

    chartView->setRenderHint(QPainter::Antialiasing);

    setCentralWidget(chartView);

    resize(400, 300);
}

ChartWindow::~ChartWindow()
{
    // Automatyczne zwolnienie zasobów przez Qt dzięki QObject
}

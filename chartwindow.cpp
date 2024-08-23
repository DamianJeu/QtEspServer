#include "chartwindow.h"

ChartWindow::ChartWindow(QWidget *parent)
    : QMainWindow(nullptr),
    chart{new QChart(nullptr)},
    series{new QLineSeries(chart)},
    axisX{new QValueAxis(chart)},
    axisY{new QValueAxis(chart)},
    chartView{new QChartView(this)}
{



    axisY->setRange(0, 10);
    axisY->setTickCount(10);
   // axisY->applyNiceNumbers();
  //  axisY->setTickType(QValueAxis::TicksFixed);

    axisX->setRange(0, 100);
    axisX->setLabelFormat("%d");
    axisX->setTickCount(10);
   // axisX->applyNiceNumbers();
    //axisX->setTickType(QValueAxis::TicksFixed);
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

    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    setCentralWidget(chartView);

    resize(600, 400);
    chart->scroll(0,0);
}

ChartWindow::~ChartWindow()
{
    qDebug() << "ChartWindow destructor";

    delete chart;

}

void ChartWindow::clearChart()
{
    series->clear();

    chart->scroll(0,0);

    axisX->setRange(0, 100);
    axisY->setRange(0, 10);

}

void ChartWindow::addNewSample(double point)
{

    if(++m_xValue >= axisX->max())
    {
        axisX->setMax(axisX->max()+10);
    }

    if(point >= axisY->max())
    {

        axisY->setMax(point+10);
    }

    series->append(m_xValue, point);
}

void ChartWindow::setNewMaxY(double maxY)
{
    Q_UNUSED(maxY);
}

void ChartWindow::setNewMinY(double minY)
{
    Q_UNUSED(minY);
}

void ChartWindow::setXValue(quint16 newXValue)
{
    Q_UNUSED(newXValue);
}

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
    axisX->setRange(0, 100);
    axisX->setLabelFormat("%d");
    axisX->setTickCount(10);
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

    this->clearChart();

    // Tworzymy główny widżet, który będzie zawierał layout
    QWidget *mainWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(mainWidget);

    // Dodajemy chartView do layoutu
    mainLayout->addWidget(chartView);

    // Tworzymy przycisk i dodajemy go do layoutu
    pushButton = new QPushButton("Clear", this);
    mainLayout->addWidget(pushButton);

    // Ustawiamy mainWidget jako główny widżet okna
    setCentralWidget(mainWidget);

    connect(pushButton, &QPushButton::clicked, this, &ChartWindow::clearChart, Qt::QueuedConnection);

    resize(600, 400);
}

ChartWindow::~ChartWindow()
{
    qDebug() << "ChartWindow destructor";



    delete chart;

}

void ChartWindow::clearChart()
{
    series->clear();



    axisX->setRange(0, 100);
    axisY->setRange(0, 10);
    m_xValue =0;
    chart->scroll(0,0);

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

void ChartWindow::closeEvent(QCloseEvent *event)
{
    qDebug()<< "ChartWindow closeEvent";
    emit closeWindow();
}

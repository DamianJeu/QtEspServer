#include "espserver.h"
#include <QDebug>
#include "clienthandler.h"
#include <QThread>


EspServer::EspServer(QObject *parent) : QTcpServer(parent)
{

    QThread::currentThread()->setObjectName("ServerThread");

}

EspServer::~EspServer()
{
    qDebug()<<"Server deleted";
}

void EspServer::startServer()
{
    if( !this->listen(QHostAddress::Any, 1234))
    {
        qCritical()<<"Could not start server";
    }
    else
    {
        qDebug()<<"Server started on thread: "<<QThread::currentThread();
    }
}

void EspServer::serverStop()
{
    emit serverStopped();
    this->close();

    qInfo()<<"Server stopped";
}

void EspServer::on_clientDisconnected()
{
    Q_UNUSED(this);
}

void EspServer::incomingConnection(qintptr handle)
{
    qInfo()<<"New client connected";

    Client *client = new Client(nullptr, handle);
    QThread *thread = new QThread();

    ChartWindow *chart = new ChartWindow(nullptr);
    chart->show();

    client->moveToThread(thread);

    connect(thread, &QThread::started, client, &Client::startClient);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);

    connect(chart, &ChartWindow::closeWindow, client, &Client::stopClient, Qt::QueuedConnection);

    connect(this, &EspServer::serverStopped, client, &Client::stopClient, Qt::QueuedConnection);
    connect(client, &Client::clientDisconnected, thread, &QThread::quit, Qt::QueuedConnection);
    connect(client, &Client::newSample, chart, &ChartWindow::addNewSample, Qt::QueuedConnection);
    connect(client, &Client::rename_chart_window, this, [=](QString name)
            {
                chart->setWindowTitle(name);
                emit newClientIp(name);

            }, Qt::QueuedConnection);

    connect(client, &Client::clientDisconnected, this,[=]()
            {
                chart->close();
                chart->deleteLater();
                emit clientDisconnected(chart->windowTitle());

            }, Qt::QueuedConnection);

    thread->start();

}




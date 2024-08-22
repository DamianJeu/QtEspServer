#include "clienthandler.h"
#include <QDebug>
#include <QThread>
#include <QEventLoop>
#include <QTcpSocket>
#include <QString>

quint64 Client::numClients;

Client::Client(QObject *parent, qintptr handle)
{
    this->handle = handle;
}

Client::~Client()
{
    qDebug()<<"Client deleted";
    if(numClients)numClients--;
}

void Client::run()
{

    clientSocket = new QTcpSocket();

    if( !clientSocket->setSocketDescriptor(this->handle))
    {
        qCritical()<<"Could not set socket descriptor";
        delete clientSocket;
        clientSocket = nullptr;  // Zapobieganie podwójnemu usunięciu
        return;
    }
    else
    {
        numClients++;
        QEventLoop loop;

        QString threadName = "ClientHandlerThread_" + QString::number(numClients);
        QThread::currentThread()->setObjectName(threadName);

        qDebug()<<"Client connected on thread: "<<QThread::currentThread();

        connect(clientSocket, &QTcpSocket::readyRead, this, [&]()
                {
                    qDebug()<<"Data received from: "<<QThread::currentThread()<<clientSocket->readAll();
                }, Qt::QueuedConnection);

        connect(clientSocket, &QTcpSocket::disconnected, this, [&]()
                {
                    qDebug()<<"Client disconnected on thread: "<<QThread::currentThread();
                    clientSocket->deleteLater();
                    clientSocket = nullptr;
                    loop.quit();

                }, Qt::QueuedConnection);

        connect(this, &Client::disconnect, clientSocket, &QTcpSocket::disconnectFromHost, Qt::QueuedConnection);


        loop.exec();

        qDebug() << "Event loop closed";
        //deleteLater();
    }
}

void Client::serverStoped()
{
    if(clientSocket!=nullptr)
    {
        emit disconnect();
        qDebug()<<"Server stopped" << QThread::currentThread();
    }
}

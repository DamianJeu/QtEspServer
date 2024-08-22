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
    this->close();
    emit serverStopped();
    qDebug()<<"Server stopped";
}

void EspServer::incomingConnection(qintptr handle)
{
    qInfo()<<"New client connected";


    Client *client = new Client(nullptr, handle);
    connect(this, &EspServer::serverStopped, client, &Client::serverStoped, Qt::QueuedConnection);
    client->setAutoDelete(true);
    pool.start(client);
}




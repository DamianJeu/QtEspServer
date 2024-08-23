#include "clienthandler.h"
#include <QDebug>
#include <QThread>
#include <QEventLoop>
#include <QTcpSocket>
#include <QString>


#include <QRegularExpression>

quint64 Client::numClients;

Client::Client(QObject *parent, qintptr handle)
{
    this->handle = handle;
}

Client::~Client()
{
    qDebug() << "Client deleted";
    if (numClients) numClients--;
}

void Client::startClient()
{


    clientSocket = new QTcpSocket();

    if(!clientSocket->setSocketDescriptor(handle))
    {

        qCritical() << "Could not set socket descriptor";
        return;

    }

    loop = new QEventLoop();

    numClients++;

    QThread::currentThread()->setObjectName("ClientThread" + QString::number(numClients));

    connect(clientSocket,&QTcpSocket::disconnected, this, [this]()
            {
                this->stopClient();

            });

    connect(clientSocket, &QTcpSocket::readyRead, this, [this]()
            {
                QByteArray data = clientSocket->readAll();
                QString str(data);
                qDebug() << "Data received: " << str << "on Thread: " << QThread::currentThread();


                QRegularExpression regex("y=(\\d+)");
                QRegularExpressionMatch match = regex.match(str);


                emit newSample(match.captured(1).toDouble());
            });


    loop->exec();
}

void Client::stopClient()
{
    clientSocket->disconnect();
    clientSocket->close();
    clientSocket->deleteLater();

    loop->exit();
    loop->deleteLater();

    this->deleteLater();

    qDebug() << "Client disconnected";

    emit clientDisconnected();
}







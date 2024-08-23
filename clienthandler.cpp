#include "clienthandler.h"
#include <QDebug>
#include <QThread>
#include <QEventLoop>
#include <QTcpSocket>
#include <QString>


#include <QRegularExpression>

quint64 Client::numClients;

Client::Client(QObject *parent, qintptr handle):
    chartWindow{nullptr}
{
    this->handle = handle;
}

Client::~Client()
{
    qDebug() << "Client deleted";
    if (numClients) numClients--;
}

void Client::run()
{
    clientSocket = new QTcpSocket();

    if (!clientSocket->setSocketDescriptor(this->handle))
    {
        qCritical() << "Could not set socket descriptor";
        delete clientSocket;
        clientSocket = nullptr;
        return;
    }
    else
    {
        numClients++;
        QEventLoop loop;

        QString threadName = "ClientHandlerThread_" + QString::number(numClients);
        QThread::currentThread()->setObjectName(threadName);

        qDebug() << "Client connected on thread: " << QThread::currentThread();

        emit newClientIp(clientSocket->peerAddress().toString());

        // Creating window ChartWindow in main thread
        QMetaObject::invokeMethod(QApplication::instance(), [this]() {
            chartWindow = new ChartWindow();
            chartWindow->setWindowTitle("Client: " + QString::number(numClients));
            chartWindow->show();
        }, Qt::QueuedConnection);

        connect(clientSocket, &QTcpSocket::readyRead, this, &Client::addNewSample, Qt::AutoConnection);

        connect(clientSocket, &QTcpSocket::disconnected, this, [&]()
                {
                    qDebug() << "Client disconnected on thread: " << QThread::currentThread();
                    clientSocket->deleteLater();

                    // Closing chart window in main thread
                    QMetaObject::invokeMethod(QApplication::instance(), [this]() {
                        if (chartWindow) {
                            chartWindow->close();
                            chartWindow->deleteLater();
                        }
                    }, Qt::QueuedConnection);

                    clientSocket = nullptr;
                    loop.quit();
                }, Qt::AutoConnection);

        connect(this, &Client::disconnect, clientSocket, &QTcpSocket::disconnectFromHost, Qt::QueuedConnection);

        loop.exec();

        qDebug() << "Event loop closed";

        this->deleteLater();
    }
}

void Client::addNewSample()
{
    if(chartWindow == nullptr)
    {
        return;
    }

    QString data = clientSocket->readAll();

    QRegularExpression regex("y=(\\d+)");
    QRegularExpressionMatch match = regex.match(data);

    // Send data to main thread
    QMetaObject::invokeMethod(chartWindow, [this, captured = match.captured(1).toDouble()]() {
        chartWindow->addNewSample(captured);
    }, Qt::QueuedConnection);

    qDebug() << "Data received from: " << QThread::currentThread();
}


void Client::serverStoped()
{
    if (clientSocket != nullptr)
    {
        emit disconnect();
        qDebug() << "Server stopped" << QThread::currentThread();
    }
}


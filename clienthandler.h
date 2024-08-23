#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <QTcpSocket>
#include <QRunnable>
#include <QEventLoop>
#include "chartwindow.h"

class Client : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr, qintptr handle = 0);
    ~Client();

    void run() override;

signals:

    void disconnect();
    void newClientIp(QString ip);

public slots:

    void serverStoped();

private slots:

    void addNewSample();

private:
    qintptr handle;
    static quint64 numClients;
    QTcpSocket *clientSocket;
    ChartWindow *chartWindow;

};

#endif // CLIENTHANDLER_H

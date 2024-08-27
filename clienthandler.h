#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <QTcpSocket>
#include <QRunnable>
#include <QEventLoop>
#include "chartwindow.h"

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr, qintptr handle = 0);
    ~Client();



signals:
    void clientDisconnected();
    void newSample(double sample);
    void rename_chart_window(QString name);

public slots:

    void startClient();
    void stopClient();

private:

    qintptr handle;
    static quint64 numClients;
    QTcpSocket *clientSocket;
    QEventLoop *loop;


};

#endif // CLIENTHANDLER_H

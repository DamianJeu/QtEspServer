#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <QTcpSocket>
#include <QRunnable>
#include <QEventLoop>

class Client : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr, qintptr handle = 0);
    ~Client();

    void run() override;

signals:

    void disconnect();

public slots:

    void serverStoped();

private:
    qintptr handle;
    static quint64 numClients;
    QTcpSocket *clientSocket;

};

#endif // CLIENTHANDLER_H

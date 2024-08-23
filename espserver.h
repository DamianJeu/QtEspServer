#ifndef ESPSERVER_H
#define ESPSERVER_H

#include <QMainWindow>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QThreadPool>

class EspServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit EspServer(QObject *parent = nullptr);
    ~EspServer();

public slots:
    void startServer();
    void serverStop();
  //  void newIp(QString ip);

signals:

    void serverStopped();
    void newClientIp(QString ip);

protected:
    void incomingConnection(qintptr handle) override;

private:
    QThreadPool pool;
};

#endif // ESPSERVER_H

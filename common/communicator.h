#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>

struct CommParams
{
    QHostAddress rHost;
    quint16      rPort;
    QHostAddress sHost;
    quint16      sPort;
};

class Communicator : public QUdpSocket
{
    Q_OBJECT

    bool         ready;
    CommParams  params;

public:
    Communicator(CommParams&,QObject *parent = nullptr);
    bool isReady();

signals:
    void recieved(QByteArray);

public slots:
    void send(QByteArray);

private slots:
    void recieve();

};

#endif // COMMUNICATOR_H

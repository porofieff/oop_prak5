#include "communicator.h"

Communicator::Communicator(CommParams& pars, QObject *parent) : QUdpSocket(parent)
{
    params = pars;
    ready = bind(params.rHost, params.rPort,
                 QAbstractSocket::ShareAddress | QAbstractSocket::ReuseAddressHint);
    if (ready) connect(this,SIGNAL(readyRead()),this,SLOT(recieve()));
}

bool Communicator::isReady()
{
    return ready;
}

void Communicator::send(QByteArray msg)
{
    if (ready)
    {
        writeDatagram(msg, params.sHost, params.sPort);
        //qDebug()<<"sended"<<msg;
    }
}

void Communicator::recieve()
{
    if (hasPendingDatagrams())
    {
        quint64 size = pendingDatagramSize();
        QByteArray msg(size,'\0');
        readDatagram(msg.data(), size);
        //qDebug()<<"recieved"<<msg;
        emit recieved(msg);
    }
}

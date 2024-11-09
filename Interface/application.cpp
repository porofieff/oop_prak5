#include "application.h"

Application::Application(int& argc, char *argv[])
    : QApplication(argc,argv)
{
    CommParams pars = { QHostAddress("127.0.0.1"), 10001,
                        QHostAddress("127.0.0.1"), 10000};
    comm = new Communicator(pars, this);

    interface = new Interface();
    interface->show();

    connect(comm,SIGNAL(recieved(QByteArray)),this,
            SLOT(fromCommunicator(QByteArray)));
    connect(interface,SIGNAL(request(QString)),
            this,SLOT(toCommunicator(QString)));

}

void Application::fromCommunicator(QByteArray msg)
{
    interface->answer(QString(msg));
}

void Application::toCommunicator(QString msg)
{
    comm->send(QByteArray().append(msg));
}

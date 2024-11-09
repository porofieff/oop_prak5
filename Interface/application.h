#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QApplication>

#include "interface.h"
#include "communicator.h"

class Application : public QApplication
{
    Q_OBJECT

    Communicator *comm;
    Interface    *interface;

public:
    Application(int&, char**);

public slots:
    void fromCommunicator(QByteArray);
    void toCommunicator(QString);

};

#endif // APPLICATION_H

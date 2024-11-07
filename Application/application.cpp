#include "application.h"
#include "common.h"

Application::Application(int argc, char *argv[])
    : QCoreApplication(argc,argv)
{
    CommParams pars = { QHostAddress("127.0.0.1"), 10000,
                        QHostAddress("127.0.0.1"), 10001};
    comm = new Communicator(pars, this);

    connect(comm,SIGNAL(recieved(QByteArray)),this,SLOT(recieve(QByteArray)));

    p.change_size(2);
    p.change_an(2);
    p.change_roots(1, 0);
    p.change_roots(3, 1);
}

void Application::recieve(QByteArray msg)
{
    QString answer, s;
    complex an, x, v, root;
    int size, root_pos;
    int pos = msg.indexOf(separator);
    int t = msg.left(pos).toInt();
    switch (t)
    {
    case VALUE_REQUEST:
        msg = msg.right(msg.length()-pos-1);
        msg >> x;
        v = p.count_val(x);
        s << (QString)x << (QString)v;
        answer<<QString().setNum(VALUE_ANSWER);
        answer += s;
        break;
    case PRINT_CLASSIC_REQUEST:
        p.change_print_mode(PrintModeClassic);
        s<<p;
        answer<<QString().setNum(PRINT_ANSWER)<<s;
        break;
    case PRINT_CANONIC_REQUEST:
        p.change_print_mode(PrintModeCanonic);
        s << p;
        answer<<QString().setNum(PRINT_ANSWER)<<s;
        break;
    case CHANGE_AN_REQUEST:
        msg = msg.right(msg.length()-pos-1);
        msg >> an;
        p.change_an(an);
        answer << QString().setNum(CHANGE_LAST_ANSWER);
        break;
    case CHANGE_POL_AN_REQUEST:
        msg = msg.right(msg.length()-pos-1);
        msg >> an;
        p.change_an(an);
        answer << QString().setNum(CHANGE_POL_ANSWER);
        break;
    case CHANGE_SIZE_REQUEST:
        msg = msg.right(msg.length()-pos-1);
        pos = msg.indexOf(separator);
        size = msg.left(pos).toInt();
        p.change_size(size);
        answer << QString().setNum(CHANGE_LAST_ANSWER);
        break;
    case CHANGE_ROOT_REQUEST:
        msg = msg.right(msg.length()-pos-1);
        msg >> root;
        pos = msg.indexOf(separator);
        root_pos = msg.left(pos).toInt();
        p.change_roots(root, root_pos);
        answer << QString().setNum(CHANGE_LAST_ANSWER);
        break;
    case CHANGE_POL_ROOTS_REQUEST:
        msg = msg.right(msg.length()-pos-1);
        msg >> root;
        pos = msg.indexOf(separator);
        root_pos = msg.left(pos).toInt();
        p.change_roots(root, root_pos);
        if (root_pos == p.get_size() - 1)
            answer << QString().setNum(CHANGE_LAST_ANSWER);
        else
            answer << QString().setNum(CHANGE_POL_ANSWER);
        break;
    default: return;
    }
    comm->send(QByteArray().append(answer));
}

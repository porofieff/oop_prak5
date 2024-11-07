#ifndef COMMON_H
#define COMMON_H

#include <QString>

enum messages
{
    VALUE_REQUEST = 1,
    VALUE_ANSWER,
    PRINT_CLASSIC_REQUEST,
    PRINT_CANONIC_REQUEST,
    PRINT_ANSWER,
    CHANGE_AN_REQUEST,
    CHANGE_POL_AN_REQUEST,
    CHANGE_ROOT_REQUEST,
    CHANGE_POL_ROOTS_REQUEST,
    CHANGE_SIZE_REQUEST,
    CHANGE_POL_ANSWER,
    CHANGE_LAST_ANSWER,
};

extern const QChar separator;
QString& operator<< (QString&,const QString&);

#endif // COMMON_H

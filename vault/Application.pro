QT = core
QT += network


CONFIG += c++17 cmdline

INCLUDEPATH += ../common
INCLUDEPATH += ../Interface

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        application.cpp \
        array.cpp \
        complex.cpp \
        main.cpp \
        polinome.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    application.h \
    array.h \
    complex.h \
    number.h \
    polinome.h

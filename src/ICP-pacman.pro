QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Model/FileLoader.cpp \
    Model/GameModel.cpp \
    Model/ReplayModel.cpp \
    View/gamepage.cpp \
    Controller/gamecontroller.cpp \
    main.cpp \
    View/mainwindow.cpp \
    View/replaypage.cpp

HEADERS += \
    Model/FileLoader.h \
    Model/GameModel.h \
    Model/ReplayModel.h \
    View/gamepage.h \
    View/mainwindow.h \
    View/replaypage.h \
    Controller/gamecontroller.h

FORMS += \
    View/gamepage.ui \
    View/mainwindow.ui \
    View/replaypage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

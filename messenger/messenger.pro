QT       += core gui statemachine
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DEPENDPATH += . $$PWD/Logger/
INCLUDEPATH += $$PWD/Logger/
LIBS += -L$$PWD/Logger -lLogger

CONFIG += c++11
TEMPLATE = app



# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chatinfo.cpp \
    createchat.cpp \
    cache.cpp \
    currentchat.cpp \
    currentuser.cpp \
    emoji.cpp \
    imagemanager.cpp \
    jsondeserializer.cpp \
    jsonserializer.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    message.cpp \
    profilewindow.cpp \
    requestmanager.cpp \
    signupwindow.cpp \
    threadworker.cpp \
    windowmanager.cpp


HEADERS += \
    chatinfo.h \
    createchat.h \
    cache.h \
    currentchat.h \
    currentuser.h \
    emoji.h \
    imagemanager.h \
    jsondeserializer.h \
    jsonserializer.h \
    loginwindow.h \
    mainwindow.h \
    message.h \
    profilewindow.h \
    requestmanager.h \
    signupwindow.h \
    threadworker.h \
    windowmanager.h

FORMS += \
    chatinfo.ui \
    createchat.ui \
    emoji.ui \
    loginwindow.ui \
    mainwindow.ui \
    profilewindow.ui \
    signupwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QT += core gui network
І
QMAKE_EXTRA_TARGETS += copyfiles
POST_TARGETDEPS += copyfiles

RESOURCES += \
    resources.qrc

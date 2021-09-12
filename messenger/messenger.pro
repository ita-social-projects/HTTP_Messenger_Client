QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    jsonparser.cpp \
    logininfo.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    signupinfo.cpp \
    signupwindow.cpp \
    userinterface.cpp

HEADERS += \
    jsonparser.h \
    logininfo.h \
    loginwindow.h \
    mainwindow.h \
    signupinfo.h \
    signupwindow.h \
    userinterface.h

FORMS += \
    loginwindow.ui \
    mainwindow.ui \
    signupwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    JsonSerializer.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    replymsgkeeper.cpp \
    requestmanager.cpp \
    signupwindow.cpp \
    user.cpp \
    userinforeply.cpp \
    windowmanager.cpp

HEADERS += \
    JsonDeserializer.h \
    JsonSerializer.h \
    loginwindow.h \
    mainwindow.h \
    replymsgkeeper.h \
    requestmanager.h \
    signupwindow.h \
    user.h \
    userinforeply.h \
    windowmanager.h

FORMS += \
    loginwindow.ui \
    mainwindow.ui \
    signupwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QT += core gui network

QMAKE_EXTRA_TARGETS += copyfiles
POST_TARGETDEPS += copyfiles

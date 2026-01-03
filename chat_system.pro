QT       += core gui
QT       += sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chat_client.cpp \
    chat_login.cpp \
    main.cpp \
    registeruser.cpp \
    stusql.cpp \
    widget.cpp

HEADERS += \
    chat_client.h \
    chat_login.h \
    registeruser.h \
    stusql.h \
    widget.h

FORMS += \
    chat_client.ui \
    chat_login.ui \
    registeruser.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

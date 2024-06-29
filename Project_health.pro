QT       += core gui
QT       += charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chooseuserwindow.cpp \
    createuserwindow.cpp \
    datainwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    datamanager.cpp \
    agl.cpp \
    setgoalwindow.cpp

HEADERS += \
    chooseuserwindow.h \
    createuserwindow.h \
    datainwindow.h \
    mainwindow.h \
    datamanager.h \
    setgoalwindow.h

FORMS += \
    chooseuserwindow.ui \
    createuserwindow.ui \
    datainwindow.ui \
    mainwindow.ui \
    setgoalwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

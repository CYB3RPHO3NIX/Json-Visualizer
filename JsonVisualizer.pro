QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    JsonSummary.cpp \
    JsonWorker.cpp \
    jsonsummarydialog.cpp \
    main.cpp \
    MainWindow.cpp \
    qjsonmodel.cpp \
    simdjson.cpp

HEADERS += \
    JsonSummary.h \
    JsonWorker.h \
    MainWindow.h \
    jsonsummarydialog.h \
    qjsonmodel.h \
    simdjson.h

FORMS += \
    MainWindow.ui \
    jsonsummarydialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    MainWindow.qrc

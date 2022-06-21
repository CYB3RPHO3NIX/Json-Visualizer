QT       += core gui
Qt       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    File.cpp \
    JsonSummary.cpp \
    JsonWorker.cpp \
    JsonSummaryDialog.cpp \
    Summary.cpp \
    main.cpp \
    MainWindow.cpp \
    qjsonmodel.cpp \
    simdjson.cpp

HEADERS += \
    File.h \
    JsonSummary.h \
    JsonWorker.h \
    MainWindow.h \
    Summary.h \
    jsoncons/json.hpp \
    jsoncons_ext/jsonpath/expression.hpp \
    jsoncons_ext/jsonpath/flatten.hpp \
    jsoncons_ext/jsonpath/json_location.hpp \
    jsoncons_ext/jsonpath/json_query.hpp \
    jsoncons_ext/jsonpath/jsonpath.hpp \
    jsoncons_ext/jsonpath/jsonpath_error.hpp \
    jsoncons_ext/jsonpath/jsonpath_expression.hpp \
    jsoncons_ext/jsonpath/jsonpath_selector.hpp \
    JsonSummaryDialog.h \
    qjsonmodel.h \
    simdjson.h

FORMS += \
    MainWindow.ui \
    JsonSummaryDialog.ui \
    Summary.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    MainWindow.qrc

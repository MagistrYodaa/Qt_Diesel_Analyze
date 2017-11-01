#-------------------------------------------------
#
# Project created by QtCreator 2017-02-17T14:06:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Garant_v_02
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS +=          $$PWD/libusb/MinGW32/libusb-1.0.a
unix: LIBS += -lusb-1.0
INCLUDEPATH +=  $$PWD/libusb/include/
                $$PWD/HEADERS
DEPENDPATH +=    $$PWD/libusb/include/

PRE_TARGETDEPS += $$PWD/libusb/MinGW32/libusb-1.0.a


SOURCES += main.cpp \
    MainWindow/mainwindow.cpp \
    QCustomPlot/qcustomplot.cpp \
    WidgetVMTSetup/widgetvmtsetup.cpp \
    WidgetSettings/widgetsettings.cpp \
    WidgetTest/widgettest.cpp \
    WidgetSelectDiesel/widgetselectdiesel.cpp \
    WidgetMetering/widgetmetering.cpp \
    WidgetDieselType/widgetdieseltype.cpp \
    WidgetArchive/widgetarchive.cpp \
    Settings/settings.cpp \
    dataio/dataio.cpp \
    ModBus/include/ModBusUSB.cpp \
    DieselType/dieseltype.cpp




HEADERS  += WidgetArchive/widgetarchive.h \
    WidgetDieselType/widgetdieseltype.h \
    WidgetSelectDiesel/widgetselectdiesel.h \
    WidgetMetering/widgetmetering.h \
    WidgetTest/widgettest.h \
    WidgetSettings/widgetsettings.h \
    WidgetVMTSetup/widgetvmtsetup.h \
    MainWindow/mainwindow.h \
    Settings/settings.h \
    QCustomPlot/qcustomplot.h \
    dataio/dataio.h \
    DieselType/dieseltype.h \
    libusb/include/libusb-1.0/libusb.h \
    Spline/spline.h \
    ModBus/include/ModBusUSB.h

FORMS    += WidgetVMTSetup/widgetvmtsetup.ui \
    WidgetTest/widgettest.ui \
    WidgetSettings/widgetsettings.ui \
    WidgetSelectDiesel/widgetselectdiesel.ui \
    WidgetMetering/widgetmetering.ui \
    WidgetDieselType/widgetdieseltype.ui \
    WidgetArchive/widgetarchive.ui \
    MainWindow/mainwindow.ui

CONFIG += mobility

RC_FILE = release/appico.rc

#win32: RC_ICONS = $$PWD/release/appico.rc
#RC_ICONS = $$PWD/appico.rc

MOBILITY = 

RESOURCES +=

DISTFILES += \
    release/appico.ico \
    release/appico.rc \
    release/icon.png



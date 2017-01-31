TEMPLATE = app
TARGET = GrblController

DEFINES = QT_NO_DEBUG

QT   += core gui printsupport widgets

# QGlViewer
QT += xml opengl
INCLUDEPATH += QGLViewer QGLWidget
# srichy  November 17, 2014
unix {
    !macx {
        LIBS += -lGLU
        LIBS += -lQGLViewer-qt5
    }
    else
    {
        LIBS += -lQGLViewer-qt5
    }
}
else {
    LIBS += -lQGlViewer2
}



# Translations
	TRANSLATIONS += trlocale/GrblController_xx.ts
	TRANSLATIONS += trlocale/GrblController_fr.ts

include(QextSerialPort/qextserialport.pri)
include(log4qt/log4qt.pri)

SOURCES += main.cpp\
    mainwindow.cpp \
    rs232.cpp \
    options.cpp \
    grbldialog.cpp \
    about.cpp \
    gcode.cpp \
    timer.cpp \
    atomicintbool.cpp \
    coord3d.cpp \
    renderarea.cpp \
    positem.cpp \
    renderitemlist.cpp \
    lineitem.cpp \
    itemtobase.cpp \
    arcitem.cpp \
    pointitem.cpp \
    controlparams.cpp \
    visu3D/viewer3D.cpp \
    visu3D/Point3D.cpp \
    visu3D/Line3D.cpp \
    visu3D/Arc3D.cpp \
    visu3D/Tools3D.cpp \
    visu3D/Box3D.cpp

HEADERS  += mainwindow.h \
    rs232.h \
    options.h \
    grbldialog.h \
    definitions.h \
    about.h \
    images.rcc \
    gcode.h \
    timer.h \
    atomicintbool.h \
    coord3d.h \
    log4qtdef.h \
    renderarea.h \
    positem.h \
    renderitemlist.h \
    lineitem.h \
    itemtobase.h \
    arcitem.h \
    pointitem.h \
    termiosext.h \
    controlparams.h \
    version.h \
    visu3D/viewer3D.h \
    visu3D/Point3D.h \
    visu3D/Line3D.h \
    visu3D/Arc3D.h \
    visu3D/Tools3D.h  \
    visu3D/Box3D.h

FORMS    += forms/mainwindow.ui \
    forms/options.ui \
    forms/grbldialog.ui \
    forms/about.ui

RESOURCES += GrblController.qrc

RC_FILE = grbl.rc



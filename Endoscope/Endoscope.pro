QT       += core gui
QT    += charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bwcamera.cpp \
    colorcamera.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    CamApi.h \
    CamShare.h \
    ExplosureFusion.h \
    TUCamApi.h \
    TUDefine.h \
    bwcamera.h \
    colorcamera.h \
    cuda_dll.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS+=$$PWD/CamCore.lib
LIBS+=$$PWD/TUCam.lib


INCLUDEPATH += $$PWD/opencv2 \

LIBS +=$$PWD/opencv_world455.lib
LIBS +=$$PWD/opencv_world455d.lib

LIBS +=$$PWD/cuda_dll.lib
LIBS +=$$PWD/ExplosureFusion.lib



#-------------------------------------------------
#
# Project created by QtCreator 2019-06-11T10:58:25
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UniversalUI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11 debug_and_release

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    factory.cpp \
    product.cpp \
    log.cpp \
    exception.cpp \
    language.cpp \
    label.cpp \
    widget.cpp \
    pushbutton.cpp \
    frame.cpp \
    signalsrelay.cpp \
    database.cpp \
    connection.cpp \
    view.cpp \
    model.cpp \
    combobox.cpp \
    progressbar.cpp \
    scene.cpp \
    item.cpp \
    qttoopencv.cpp \
    worker.cpp \
    controller.cpp

HEADERS += \
        mainwindow.h \
    factory.h \
    product.h \
    protocol.h \
    log.h \
    exception.h \
    common.h \
    signalsrelay.h \
    qttoopencv.h

FORMS += \
        mainwindow.ui

TRANSLATIONS += translation_cn.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ui.xml \
    xml/config.xml \
    xml/ui.xml \
    readme.txt \
    translation_cn.ts

INCLUDEPATH += D:\opencv4.1.0\opencv\build\include\opencv2 \
               D:\opencv4.1.0\opencv\build\include

CONFIG(debug, debug|release) {
  LIBS += -LD:/NYQProject/UniversalUI/libs -llibmysql \
        -LD:\opencv4.1.0\opencv\build\x64\vc15\lib -lopencv_world410d
} else {
  LIBS += -LD:/NYQProject/UniversalUI/libs -llibmysql \
        -LD:\opencv4.1.0\opencv\build\x64\vc15\lib -lopencv_world410
}

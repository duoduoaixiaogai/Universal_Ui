#-------------------------------------------------
#
# Project created by QtCreator 2019-06-11T10:58:25
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = lib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS BUILD_LIB

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11 debug_and_release dll

SOURCES += \
        #main.cpp \
        #mainwindow.cpp \
    #factory.cpp \
    #product.cpp \
    #log.cpp \
    #exception.cpp \
    #language.cpp \
    #label.cpp \
    #widget.cpp \
    #pushbutton.cpp \
    #frame.cpp \
    #signalsrelay.cpp \
    #database.cpp \
    #connection.cpp \
    #view.cpp \
    #model.cpp \
    #combobox.cpp \
    #progressbar.cpp \
    #scene.cpp \
    #item.cpp \
    #qttoopencv.cpp \
    #worker.cpp \
    #controller.cpp \
    #source/combobox.cpp \
    #source/common.cpp \
    #source/connection.cpp \
    #source/controller.cpp \
    #source/database.cpp \
    #source/exception.cpp \
    #source/factory.cpp \
    #source/frame.cpp \
    #source/graphicsscene_copy.cpp \
    #source/gtxlqxmainwindow.cpp \
    #source/item.cpp \
    #source/label.cpp \
    #source/language.cpp \
    #source/log.cpp \
    #source/main.cpp \
    #source/mainwindow.cpp \
    #source/model.cpp \
    #source/product.cpp \
    #source/progressbar.cpp \
    #source/pushbutton.cpp \
    #source/qttoopencv.cpp \
    #source/scene.cpp \
    #source/signalsrelay.cpp \
    #source/view.cpp \
    #source/widget.cpp \
    #source/worker.cpp \
    sources/combobox.cpp \
    #sources/common.cpp \
    sources/connection.cpp \
    sources/controller.cpp \
    sources/database.cpp \
    sources/exception.cpp \
    #sources/factory.cpp \
    sources/frame.cpp \
    #sources/graphicsscene_copy.cpp \
    #sources/gtxlqxmainwindow.cpp \
    sources/item.cpp \
    sources/label.cpp \
    sources/language.cpp \
    sources/log.cpp \
    #sources/main.cpp \
    sources/mainwindow.cpp \
    sources/model.cpp \
    sources/product.cpp \
    sources/progressbar.cpp \
    sources/pushbutton.cpp \
    sources/qttoopencv.cpp \
    sources/scene.cpp \
    sources/signalsrelay.cpp \
    sources/view.cpp \
    sources/widget.cpp \
    sources/worker.cpp \
    sources/file.cpp \
    sources/lineedit.cpp \
    sources/checkbox.cpp \
    sources/radiobutton.cpp \
    sources/doublespinbox.cpp

HEADERS += \
        #mainwindow.h \
    #factory.h \
    #product.h \
    #protocol.h \
    #log.h \
    #exception.h \
    #common.h \
    #signalsrelay.h \
    #qttoopencv.h \
    #global.h \
    include/common.h \
    include/exception.h \
    include/factory.h \
    include/global.h \
    include/language.h \
    include/log.h \
    include/mainwindow.h \
    include/product.h \
    include/progressbar.h \
    include/protocol.h \
    include/qttoopencv.h \
    include/recordtype.h \
    include/signalsrelay.h

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
    translation_cn.ts \
    qss/IVMS4200.qss

INCLUDEPATH += D:\opencv4.1.0\opencv\build\include\opencv2 \
               D:\opencv4.1.0\opencv\build\include

CONFIG(debug, debug|release) {
  LIBS += -LD:/NYQProject/UniversalUI/libs -llibmysql \
        -LD:\opencv4.1.0\opencv\build\x64\vc15\lib -lopencv_world410d
  TARGET = UniversalUI_d
} else {
  LIBS += -LD:/NYQProject/UniversalUI/libs -llibmysql \
        -LD:\opencv4.1.0\opencv\build\x64\vc15\lib -lopencv_world410
  TARGET = UniversalUI
}

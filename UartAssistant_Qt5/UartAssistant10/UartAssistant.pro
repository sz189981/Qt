#-------------------------------------------------
#
# Project created by QtCreator 2018-07-12T18:36:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UartAssistant
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


SOURCES += \
    Forms/AboutDialog.cpp \
    Forms/ComDialog.cpp \
    Qextserial/qextserialport.cpp \
    Qextserial/qextserialport_win.cpp \
    User/Combase.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Forms/AboutDialog.h \
    Forms/ComDialog.h \
    Qextserial/qextserialport.h \
    Qextserial/qextserialport_global.h \
    Qextserial/qextserialport_p.h \
    User/Combase.h \
    mainwindow.h

FORMS += \
    Forms/AboutDialog.ui \
    Forms/ComDialog.ui \
    mainwindow.ui


RESOURCES += \
    resource.qrc

#7.2、添加窗口图标：
#(1)制作一个.ico的图标，跟图片资源放在一起，如：Creator.ico。
#(2)新建一个文本文件，在文本文件中输入如下内容，关闭文本，重命名文本文件，改成.rc的文件，如：Creator.rc。
#(3)打开UartAssistant.pro工程文件，在下面添加如下语句，进行调用Creator.rc文件。
RC_FILE += Creator.rc









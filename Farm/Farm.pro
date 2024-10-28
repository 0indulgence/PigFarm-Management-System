QT       += core gui
QT       += multimedia
QT       += sql
QT       += charts
QT       += multimedia
QT       += multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    farmdialog.cpp \
    mainfarm.cpp \
    pig.cpp \
    pigfarm.cpp \
    pigsty.cpp

HEADERS += \
    farmdialog.h \
    mainfarm.h \
    pig.h \
    pigfarm.h \
    pigsty.h

FORMS += \
    farmdialog.ui \
    mainfarm.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Begin.qrc \
    FarmPicture.qrc

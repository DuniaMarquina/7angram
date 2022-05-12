QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    instructions.cpp \
    main.cpp \
    mainwindow.cpp \
    tablero.cpp

HEADERS += \
    instructions.h \
    mainwindow.h \
    tablero.h

FORMS += \
    instructions.ui \
    mainwindow.ui \
    tablero.ui

TRANSLATIONS += \
    7angram_es_VE.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    imagenes.qrc

DISTFILES += \
    imagenes/FigurasGris/1.png \
    imagenes/FigurasGris/10.png \
    imagenes/FigurasGris/11.png \
    imagenes/FigurasGris/2.png \
    imagenes/FigurasGris/3.png \
    imagenes/FigurasGris/4.png \
    imagenes/FigurasGris/5.png \
    imagenes/FigurasGris/6.png \
    imagenes/FigurasGris/7.png \
    imagenes/FigurasGris/8.png \
    imagenes/FigurasGris/9.png \
    imagenes/Reloj.jpg \
    imagenes/Soluciones/1.jpg \
    imagenes/Soluciones/7.jpg \
    imagenes/Soluciones/8.jpg

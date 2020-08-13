QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS


# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

RESOURCES+= \
     primo.mp3 \
     River.mp3 \
     love.mp3 \
     dusk.mp3 \
     pames.mp3 \
     agr.mp3 \
     til.mp4 \
     music.gif \
     river.gif \
     music2.gif \
     pl.gif \
     light.gif  \
     play.png \
     pause2.png \
     Caliente.mp3 \
     caliente.png \
     music.png \
     music1.png \
     music2.png \
     music3.png \
     mt.png \
     p.png \
     ps2.png \
     nm.png \
     laodsong.png \
     playlist.png \
     quit.png \
     ran2.png \
     n2.png \
     musicdefault.gif \
     shuffle.png \
     next.png
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

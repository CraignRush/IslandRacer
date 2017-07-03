QT += core gui
QT += multimedia

CONFIG += c++11 \
       += resources_big

QMAKE_CFLAGS += /RTC1 /GC
QMAKE_CXXFLAGS += /RTC1 /GC
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = src
TEMPLATE = app

SOURCES += main.cpp \
    game.cpp \
    world.cpp \
    car.cpp \
    track.cpp \
    player.cpp \
    checkpoint.cpp \
    mainmenu.cpp \
    sound.cpp \
    viewport.cpp \
    worldposition.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/../Box2D
#LIBS += -L$$PWD/../Box2D -lBox2D
LIBS += -L$$PWD/../Box2D
CONFIG( debug, debug|release ) {
    # debug
    LIBS += -lBox2D
} else {
    # release
    LIBS += -lBox2D
}
#INCLUDEPATH += $$PWD/libs
#LIBS += -L$$PWD/libs -lBox2D

HEADERS += \
    game.h \
    world.h \
    car.h \
    track.h \
    player.h \
    checkpoint.h \
    mainmenu.h \
    sound.h \
    viewport.h \
    worldposition.h

RESOURCES += \
    res.qrc

FORMS += \
    mainmenu.ui

# set icon for mac and windows
ICON = Icon.icns
RC_ICONS = Icon.ico


DESTDIR = $$PWD

DISTFILES += \
    highscores/Hockenheimring.score \
    highscores/Monza.score \
    highscores/YasMarina.score


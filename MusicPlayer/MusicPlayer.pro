TEMPLATE = app
TARGET = musicplayer

QT += widgets multimedia winextras

RESOURCES += \
    myimages.qrc

HEADERS += \
    musicplayer.h \
    volumebutton.h \
    mylrc.h \
    myplaylist.h

SOURCES += \
    main.cpp \
    musicplayer.cpp \
    volumebutton.cpp \
    mylrc.cpp \
    myplaylist.cpp

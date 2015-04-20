
TARGET = hang-me

QT += dbus

CONFIG += sailfishapp

INCLUDEPATH += src

SOURCES += \
    src/Hangish.cpp \
    src/authenticator.cpp \
    src/client.cpp \
    src/channel.cpp \
    src/conversationmodel.cpp \
    src/rostermodel.cpp \
    src/utils.cpp \
    src/contactsmodel.cpp \
    src/filemodel.cpp

HEADERS += \
    src/authenticator.h \
    src/client.h \
    src/channel.h \
    src/qtimports.h \
    src/conversationmodel.h \
    src/rostermodel.h \
    src/utils.h \
    src/structs.h \
    src/contactsmodel.h \
    src/filemodel.h

OTHER_FILES += \
    rpm/hang-me.yaml \
    rpm/hang-me.changes.in \
    rpm/hang-me.spec \
    hang-me.desktop

RESOURCES += \
    hang-me.qrc

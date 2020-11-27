QT       += core gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

LIBS += -lssl -lcrypto -lpthread -lpistache

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    add_plant.cpp \
    add_requirement.cpp \
    api_server.cpp \
    main.cpp \
    plantapp.cpp

HEADERS += \
    add_plant.h \
    add_requirement.h \
    api_server.h \
    plantapp.h

FORMS += \
    add_plant.ui \
    add_requirement.ui \
    api_server.ui \
    plantapp.ui


TRANSLATIONS += \
    client_local_en_GB.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

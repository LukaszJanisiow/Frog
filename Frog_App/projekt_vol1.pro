QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    drzewo.cpp \
    kloda.cpp \
    main.cpp \
    obiekt.cpp \
    obiektmobilny.cpp \
    przyciskstartugry.cpp \
    rozgrywka.cpp \
    samochod.cpp \
    scene.cpp \
    teren.cpp \
    terendroga.cpp \
    terengrafika.cpp \
    terenwoda.cpp \
    terenzielony.cpp \
    widget.cpp \
    zaba.cpp \
    zarzadzanieterenami.cpp

HEADERS += \
    drzewo.h \
    kloda.h \
    obiekt.h \
    obiektmobilny.h \
    przyciskstartugry.h \
    rozgrywka.h \
    samochod.h \
    scene.h \
    teren.h \
    terendroga.h \
    terengrafika.h \
    terenwoda.h \
    terenzielony.h \
    widget.h \
    zaba.h \
    zarzadzanieterenami.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    logic_handler.cpp \
    main.cpp \
    main_screen.cpp \
    trm_widget.cpp

HEADERS += \
    logic_handler.h \
    main_screen.h \
    trm_widget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


FORMS += \
    main_screen.ui \
    trm_widget.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lowen_io
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lowen_iod
else:unix: LIBS += -L$$PWD/lib/ -lowen_io

INCLUDEPATH += $$PWD/lib
DEPENDPATH += $$PWD/lib

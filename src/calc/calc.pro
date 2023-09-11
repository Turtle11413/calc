QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cred.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    ../github/calc/src/backend/calc.c \
    ../github/calc/src/backend/stack.c \
    ../github/calc/src/backend/validate.c \
    ../github/calc/src/backend/priority.c \
    ../github/calc/src/backend/credit.c

HEADERS += \
    cred.h \
    mainwindow.h \
    qcustomplot.h \
    ../github/calc/src/backend/calc.h \
    ../github/calc/src/backend/credit.h

FORMS += \
    cred.ui \
    mainwindow.ui

CONFIG += lrelease
CONFIG += embed_translation

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

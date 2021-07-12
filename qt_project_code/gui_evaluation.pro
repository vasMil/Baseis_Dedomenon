QT       += core gui sql

include( ./manager/manager.pri )
include( ./administrator/administrator.pri )
include( ./evaluator/evaluator.pri )
include( ./employee/employee.pri )

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DBConnect.cpp \
    Login.cpp \
    main.cpp \
    myQt_Functions.cpp

HEADERS += \
    DBConnect.h \
    Login.h \
    myQt_Functions.h

FORMS += \
    DBConnect.ui \
    Login.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES +=

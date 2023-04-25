QT = core

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        blasteffects.cpp \
        bomb.cpp \
        location.cpp \
        main.cpp \
        weatherconditions.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
QT += network

HEADERS += \
    CasualtiesEstimator.h \
    Server.h \
    ShelterEstimator.h \
    blasteffects.h \
    bomb.h \
    location.h \
    weatherconditions.h

LIBS += -LC:/curl/lib -lcurl
INCLUDEPATH += C:/curl/include
INCLUDEPATH += C:/json/json-develop/include

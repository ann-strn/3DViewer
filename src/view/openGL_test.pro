QT       += core gui opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 C

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    simpleobject3d.cpp \
    widget.cpp \
    ../back/parser.c \
    ../back/affine_transformations.c \
    ./gif/gifanim.cpp

HEADERS += \
    mainwindow.h \
    simpleobject3d.h \
    widget.h \
    ../back/parser.h \
    ../back/affine_transformations.h \
    ./gif/gifanim.h
#    gif.h



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RESOURCES += \
    shaders.qrc 

FORMS += \
    mainwindow.ui

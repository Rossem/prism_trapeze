#-------------------------------------------------
#
# Project created by QtCreator 2012-03-12T14:01:19
#
#-------------------------------------------------
CONFIG += qt
QT += gui
QT       += core gui
QT           += opengl
TARGET = CG_OGL
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    Camera.cpp \
    box.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    Camera.h \
    box.h \
    coord_axis.h \
    prism.h \
    L.h \
    rotations_array.h \
    sphere.h

FORMS    += mainwindow.ui

RESOURCES += \
    textures.qrc

OTHER_FILES += \
    images/side1.png \
    images/side6.png \
    images/side5.png \
    images/side4.png \
    images/side3.png \
    images/side2.png \
    images/11_earth.jpg \
    fragment_shader.frag \
    vertex_shader.vert


















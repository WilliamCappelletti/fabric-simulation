QT += core gui opengl widgets
CONFIG += c++11

win32:LIBS += -lopengl32


TARGET = exerciceP14_gl

LIBS += -L../general -lgeneral
PRE_TARGETDEPS += ../general/libgeneral.a

INCLUDEPATH = ../general

SOURCES += \
    main_qt_gl.cc \
    glwidget.cc \
    glsphere.cc \
    vue_opengl.cc

HEADERS += \
    glwidget.h \
    vertex_shader.h \
    vue_opengl.h \
    glsphere.h \
    ../general/Dessinable.h \
    ../general/SupportADessin.h \
    ../general/Systeme.h

RESOURCES += \
    resource.qrc

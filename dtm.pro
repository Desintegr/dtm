TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .

QT += opengl

HEADERS += src/camera.h \
           src/dtm.h \
           src/light.h \
           src/opengl_scene.h \
           src/point3d.h \
           src/water.h

SOURCES += src/camera.cpp \
           src/dtm.cpp \
           src/light.cpp \
           src/main.cpp \
           src/opengl_scene.cpp \
           src/point3d.cpp \
           src/water.cpp

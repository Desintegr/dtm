TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .

QT += opengl

HEADERS += src/camera.h \
           src/dtm.h \
           src/dtm_widget.h \
           src/point3d.h

SOURCES += src/camera.cpp \
           src/dtm.cpp \
           src/dtm_widget.cpp \
           src/main.cpp \
           src/point3d.cpp

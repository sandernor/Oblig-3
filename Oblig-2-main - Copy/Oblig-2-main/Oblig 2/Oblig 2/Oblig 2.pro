QT          += core gui widgets opengl

TEMPLATE    = app
CONFIG      += c++17

TARGET      = 3D-programmering

SOURCES += main.cpp \
    boat.cpp \
    camera.cpp \
    cube.cpp \
    cube2.cpp \
    cube3.cpp \
    door.cpp \
    fx.cpp \
    fxy.cpp \
    graph.cpp \
    heightmapread.cpp \
    house.cpp \
    interobj.cpp \
    light.cpp \
    lineobject.cpp \
    logger.cpp \
    mainwindow.cpp \
    oarpu.cpp \
    octahedronball.cpp \
    parabel.cpp \
    pickup.cpp \
    plane.cpp \
    renderwindow.cpp \
    shader.cpp \
    tetra.cpp \
    tetra2.cpp \
    texturedcube.cpp \
    trianglesurface.cpp \
    vertex2.cpp \
    visualobject.cpp \
    x3curve.cpp \
    xyz.cpp \
    xyz2.cpp

HEADERS += \
    boat.h \
    camera.h \
    cube.h \
    cube2.h \
    cube3.h \
    door.h \
    fx.h \
    fxy.h \
    graph.h \
    heightmapread.h \
    house.h \
    interobj.h \
    light.h \
    lineobject.h \
    logger.h \
    mainwindow.h \
    oarpu.h \
    octahedronball.h \
    parabel.h \
    pickup.h \
    plane.h \
    renderwindow.h \
    shader.h \
    tetra.h \
    tetra2.h \
    texturedcube.h \
    trianglesurface.h \
    vertex2.h \
    visualobject.h \
    x3curve.h \
    xyz.h \
    xyz2.h

FORMS += \
    mainwindow.ui

DISTFILES += \
    plainshader.frag \
    plainshader.vert \
    textureShader.frag \
    textureShader.vert

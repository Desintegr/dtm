INCLUDE_DIRECTORIES(../include ${FLOWVR_INCLUDE_DIR})

SET(QT_USE_QTOPENGL TRUE)
INCLUDE(${QT_USE_FILE})

SET(EXEC viewer)
SET(SRC camera.cpp dtm.cpp flowvr.cpp flowvr_thread.cpp light.cpp main.cpp opengl_scene.cpp point3d.cpp water.cpp)

SET(MOC_HDR flowvr_thread.h opengl_scene.h water.h)
QT4_WRAP_CPP(MOC_SRC ${MOC_HDR})

ADD_EXECUTABLE(${EXEC} ${SRC} ${MOC_SRC})
TARGET_LINK_LIBRARIES(${EXEC} ${FLOWVR_base_LIBRARY} ${FLOWVR_mod_LIBRARY} ${FLOWVR_utils_LIBRARY} ${QT_LIBRARIES})
INSTALL(TARGETS ${EXEC} DESTINATION ${MODULE_DIR})

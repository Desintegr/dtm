PROJECT(simulation)

SET(app simulation)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

# répertoires d'installation

SET(INCLUDE_DIR ${CMAKE_INSTALL_PREFIX}/include)
SET(LIB_DIR ${CMAKE_INSTALL_PREFIX}/lib)
SET(BIN_DIR ${CMAKE_INSTALL_PREFIX}/bin)
SET(MODULE_DIR ${CMAKE_INSTALL_PREFIX}/bin)
SET(CMAKE_DIR ${CMAKE_INSTALL_PREFIX}/cmake)

# vérifie si FlowVR est bien installé

FIND_PACKAGE(FlowVR REQUIRED)
IF(FLOWVR_FOUND)
  MESSAGE(STATUS "FlowVR found")
ELSE(FLOWVR_FOUND)
  MESSAGE(FATAL_ERROR "Error: FlowVR not found")
ENDIF (FLOWVR_FOUND)

# vérifie si OpenGL est bien installé

FIND_PACKAGE(OpenGL REQUIRED)
IF(OPENGL_FOUND) 
  MESSAGE(STATUS "OpenGL found")
ELSE(OPENGL_FOUND) 
  MESSAGE(FATAL_ERROR "Error: OpenGL not found")
  SET(BUILD_MODULE FALSE)
ENDIF(OPENGL_FOUND) 

# vérifie si Qt4 est bien installé

FIND_PACKAGE(Qt4 REQUIRED)
IF(QT4_FOUND)
  MESSAGE(STATUS "Qt4 found")
ELSE(QT4_FOUND)
  MESSAGE(FATAL_ERROR "Qt4 not found")
  SET(BUILD_MODULE FALSE)
ENDIF(QT4_FOUND)

# fichiers de configuration

CONFIGURE_FILE(app-config.sh.in ${app}-config.sh @ONLY)
INSTALL(PROGRAMS ${CMAKE_BINARY_DIR}/${app}-config.sh DESTINATION ${BIN_DIR})

CONFIGURE_FILE(appConfig.cmake.in ${app}Config.cmake @ONLY)
INSTALL(FILES ${CMAKE_BINARY_DIR}/${app}Config.cmake DESTINATION ${CMAKE_DIR})

# compilation des sources

ADD_DEFINITIONS(-O2 -pipe -march=native -W -Wall -Wno-deprecated)
ADD_SUBDIRECTORY(src)

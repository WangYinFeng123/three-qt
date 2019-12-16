# Install script for directory: /home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthDrivers/engine_mp

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/osgdb_osgearth_engine_mp.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/osgdb_osgearth_engine_mp.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/osgdb_osgearth_engine_mp.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE MODULE FILES "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/lib/osgdb_osgearth_engine_mp.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/osgdb_osgearth_engine_mp.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/osgdb_osgearth_engine_mp.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/osgdb_osgearth_engine_mp.so"
         OLD_RPATH "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/lib:/usr/local/lib64:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/osgdb_osgearth_engine_mp.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/osgEarthDrivers/engine_mp" TYPE FILE FILES
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthDrivers/engine_mp/Common"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthDrivers/engine_mp/DynamicLODScaleCallback"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthDrivers/engine_mp/HeightFieldCache"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthDrivers/engine_mp/FileLocationCallback"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthDrivers/engine_mp/KeyNodeFactory"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthDrivers/engine_mp/MPGeometry"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthDrivers/engine_mp/MPShaders"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthDrivers/engine_mp/MPTerrainEngineNode"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthDrivers/engine_mp/MPTerrainEngineOptions"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthDrivers/engine_mp/QuickReleaseGLObjects"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthDrivers/engine_mp/SingleKeyNodeFactory"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthDrivers/engine_mp/TerrainNode"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthDrivers/engine_mp/TileGroup"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthDrivers/engine_mp/TileModel"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthDrivers/engine_mp/TileModelCompiler"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthDrivers/engine_mp/TileNode"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthDrivers/engine_mp/TileNodeRegistry"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthDrivers/engine_mp/TileModelFactory"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthDrivers/engine_mp/TilePagedLOD"
    )
endif()


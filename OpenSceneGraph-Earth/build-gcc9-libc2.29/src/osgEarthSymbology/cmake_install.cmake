# Install script for directory: /home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthSymbology

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
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthSymbology.so.2.6.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthSymbology.so.0"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY FILES
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/lib/libosgEarthSymbology.so.2.6.0"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/lib/libosgEarthSymbology.so.0"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthSymbology.so.2.6.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthSymbology.so.0"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHANGE
           FILE "${file}"
           OLD_RPATH "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/lib:/usr/local/lib64:"
           NEW_RPATH "")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthSymbology.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthSymbology.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthSymbology.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY FILES "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/lib/libosgEarthSymbology.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthSymbology.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthSymbology.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthSymbology.so"
         OLD_RPATH "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/lib:/usr/local/lib64:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthSymbology.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/osgEarthSymbology" TYPE FILE FILES
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthSymbology/AGG.h"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthSymbology/AltitudeSymbol"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthSymbology/Common"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthSymbology/Color"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthSymbology/CoverageSymbol"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthSymbology/CssUtils"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthSymbology/Expression"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthSymbology/ExtrusionSymbol"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthSymbology/Fill"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthSymbology/Geometry"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthSymbology/GeometryFactory"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthSymbology/GEOS"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthSymbology/GeometryRasterizer"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthSymbology/IconResource"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthSymbology/IconSymbol"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthSymbology/InstanceResource"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthSymbology/InstanceSymbol"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthSymbology/LineSymbol"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthSymbology/MarkerResource"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthSymbology/MarkerSymbol"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthSymbology/MeshConsolidator"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthSymbology/MeshFlattener"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthSymbology/MeshSubdivider"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthSymbology/ModelResource"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthSymbology/ModelSymbol"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthSymbology/PointSymbol"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthSymbology/PolygonSymbol"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthSymbology/Query"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthSymbology/RenderSymbol"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthSymbology/Resource"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthSymbology/ResourceCache"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthSymbology/ResourceLibrary"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthSymbology/Skins"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthSymbology/StencilVolumeNode"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthSymbology/Stroke"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthSymbology/Style"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthSymbology/StyleSelector"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthSymbology/StyleSheet"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthSymbology/Symbol"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthSymbology/Tags"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthSymbology/TextSymbol"
    )
endif()


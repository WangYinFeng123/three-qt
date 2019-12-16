# Install script for directory: /home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthQt

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
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthQt.so.2.6.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthQt.so.0"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY FILES
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/lib/libosgEarthQt.so.2.6.0"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/lib/libosgEarthQt.so.0"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthQt.so.2.6.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthQt.so.0"
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
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthQt.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthQt.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthQt.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY FILES "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/lib/libosgEarthQt.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthQt.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthQt.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthQt.so"
         OLD_RPATH "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/lib:/usr/local/lib64:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthQt.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/osgEarthQt" TYPE FILE FILES
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthQt/Actions"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthQt/AnnotationDialogs"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthQt/AnnotationListWidget"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthQt/AnnotationToolbar"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthQt/CollapsiblePairWidget"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthQt/Common"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthQt/DataManager"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthQt/GuiActions"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthQt/LayerManagerWidget"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthQt/LOSControlWidget"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthQt/LOSCreationDialog"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthQt/MapCatalogWidget"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthQt/TerrainProfileGraph"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthQt/TerrainProfileWidget"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthQt/ViewWidget"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthQt/ViewerWidget"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/osgEarthQt/ui_LOSCreationDialog.h"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthQt/ui/LOSCreationDialog.ui"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthQt/images.qrc"
    )
endif()


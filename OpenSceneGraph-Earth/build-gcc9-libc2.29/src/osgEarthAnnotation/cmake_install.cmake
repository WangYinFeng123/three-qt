# Install script for directory: /home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthAnnotation

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
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthAnnotation.so.2.6.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthAnnotation.so.0"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY FILES
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/lib/libosgEarthAnnotation.so.2.6.0"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/lib/libosgEarthAnnotation.so.0"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthAnnotation.so.2.6.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthAnnotation.so.0"
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
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthAnnotation.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthAnnotation.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthAnnotation.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY FILES "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/lib/libosgEarthAnnotation.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthAnnotation.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthAnnotation.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthAnnotation.so"
         OLD_RPATH "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/lib:/usr/local/lib64:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthAnnotation.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/osgEarthAnnotation" TYPE FILE FILES
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthAnnotation/AnnotationSettings"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthAnnotation/AnnotationEditing"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthAnnotation/AnnotationData"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthAnnotation/AnnotationNode"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthAnnotation/AnnotationRegistry"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthAnnotation/AnnotationUtils"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthAnnotation/CircleNode"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthAnnotation/Common"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthAnnotation/Decoration"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthAnnotation/Draggers"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthAnnotation/EllipseNode"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthAnnotation/Export"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthAnnotation/FeatureNode"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthAnnotation/FeatureEditing"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthAnnotation/LocalGeometryNode"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthAnnotation/HighlightDecoration"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthAnnotation/ImageOverlay"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthAnnotation/ImageOverlayEditor"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthAnnotation/LabelNode"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthAnnotation/LocalizedNode"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthAnnotation/ModelNode"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthAnnotation/OrthoNode"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthAnnotation/PlaceNode"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthAnnotation/RectangleNode"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthAnnotation/ScaleDecoration"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthAnnotation/TrackNode"
    )
endif()


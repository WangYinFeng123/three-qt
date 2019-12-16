# Install script for directory: /home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthFeatures

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
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthFeatures.so.2.6.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthFeatures.so.0"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY FILES
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/lib/libosgEarthFeatures.so.2.6.0"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/lib/libosgEarthFeatures.so.0"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthFeatures.so.2.6.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthFeatures.so.0"
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
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthFeatures.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthFeatures.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthFeatures.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY FILES "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/lib/libosgEarthFeatures.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthFeatures.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthFeatures.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthFeatures.so"
         OLD_RPATH "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/lib:/usr/local/lib64:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthFeatures.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/osgEarthFeatures" TYPE FILE FILES
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthFeatures/AltitudeFilter"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthFeatures/BufferFilter"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthFeatures/BuildGeometryFilter"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthFeatures/BuildTextFilter"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthFeatures/BuildTextOperator"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthFeatures/CentroidFilter"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthFeatures/Common"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthFeatures/ConvertTypeFilter"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthFeatures/CropFilter"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthFeatures/ExtrudeGeometryFilter"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthFeatures/Feature"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthFeatures/FeatureCursor"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthFeatures/FeatureDisplayLayout"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthFeatures/FeatureDrawSet"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthFeatures/FeatureIndex"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthFeatures/FeatureListSource"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthFeatures/FeatureModelGraph"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthFeatures/FeatureModelSource"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthFeatures/FeatureSource"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthFeatures/FeatureSourceIndexNode"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthFeatures/FeatureTileSource"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthFeatures/Filter"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthFeatures/FilterContext"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthFeatures/GeometryCompiler"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthFeatures/GeometryUtils"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthFeatures/LabelSource"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthFeatures/MeshClamper"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthFeatures/OgrUtils"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthFeatures/OptimizerHints"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthFeatures/PolygonizeLines"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthFeatures/ResampleFilter"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthFeatures/ScaleFilter"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthFeatures/Session"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthFeatures/ScatterFilter"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthFeatures/Script"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthFeatures/ScriptEngine"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthFeatures/SubstituteModelFilter"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthFeatures/TessellateOperator"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthFeatures/TextSymbolizer"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthFeatures/TransformFilter"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthFeatures/VirtualFeatureSource"
    )
endif()


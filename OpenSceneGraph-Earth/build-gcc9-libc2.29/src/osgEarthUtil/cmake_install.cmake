# Install script for directory: /home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil

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
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthUtil.so.2.6.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthUtil.so.0"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY FILES
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/lib/libosgEarthUtil.so.2.6.0"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/lib/libosgEarthUtil.so.0"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthUtil.so.2.6.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthUtil.so.0"
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
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthUtil.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthUtil.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthUtil.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY FILES "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/lib/libosgEarthUtil.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthUtil.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthUtil.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthUtil.so"
         OLD_RPATH "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/lib:/usr/local/lib64:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarthUtil.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/osgEarthUtil" TYPE FILE FILES
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/ActivityMonitorTool"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/AnnotationEvents"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/AutoClipPlaneHandler"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/ArcGIS"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/AtlasBuilder"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/Common"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/Controls"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/ContourMap"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/ClampCallback"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/DataScanner"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/EarthManipulator"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/Ephemeris"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/ExampleResources"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/Export"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/FeatureQueryTool"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/Fog"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/Formatter"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/GeodeticGraticule"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/GraticuleExtension"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/GraticuleNode"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/GraticuleOptions"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/GraticuleTerrainEffect"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/HTM"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/LatLongFormatter"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/LineOfSight"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/LinearLineOfSight"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/LODBlending"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/LogarithmicDepthBuffer"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/MeasureTool"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/MGRSFormatter"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/MGRSGraticule"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/MouseCoordsTool"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/ObjectLocator"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/Ocean"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/PolyhedralLineOfSight"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/RadialLineOfSight"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/RTTPicker"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/Shaders"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/Shadowing"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/SimplexNoise"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/Sky"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/SpatialData"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/StarData"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/TerrainProfile"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/TileIndex"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/TileIndexBuilder"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/TFS"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/TFSPackager"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/TMS"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/TMSBackFiller"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/TMSPackager"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/UTMGraticule"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/VerticalScale"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/WFS"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/WMS"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/BrightnessContrastColorFilter"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/CMYKColorFilter"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/GammaColorFilter"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/GLSLColorFilter"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/HSLColorFilter"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/RGBColorFilter"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/ChromaKeyColorFilter"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarthUtil/NightColorFilter"
    )
endif()


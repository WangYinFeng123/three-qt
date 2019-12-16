# Install script for directory: /home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth

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
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarth.so.2.6.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarth.so.0"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY FILES
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/lib/libosgEarth.so.2.6.0"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/lib/libosgEarth.so.0"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarth.so.2.6.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarth.so.0"
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
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarth.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarth.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarth.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY FILES "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/lib/libosgEarth.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarth.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarth.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarth.so"
         OLD_RPATH "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/lib:/usr/local/lib64:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libosgEarth.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/osgEarth" TYPE FILE FILES
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/AlphaEffect"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/AutoScale"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/Bounds"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/Cache"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/CacheEstimator"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/CacheBin"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/CachePolicy"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/CacheSeed"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/Capabilities"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/Clamping"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/ClampableNode"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/ClampingTechnique"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/ColorFilter"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/Common"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/CompositeTileSource"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/Config"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/Containers"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/Cube"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/CullingUtils"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/DateTime"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/Decluttering"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/DepthOffset"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/DPLineSegmentIntersector"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/DrapeableNode"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/DrapingTechnique"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/DrawInstanced"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/ECEF"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/ElevationField"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/ElevationLayer"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/ElevationLOD"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/ElevationQuery"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/Export"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/Extension"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/FadeEffect"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/FileUtils"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/GeoCommon"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/GeoData"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/Geoid"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/GeoMath"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/GeoTransform"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/HeightFieldUtils"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/Horizon"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/HTTPClient"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/ImageLayer"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/ImageMosaic"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/ImageToHeightFieldConverter"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/ImageUtils"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/IOTypes"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/JsonUtils"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/Layer"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/LineFunctor"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/Locators"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/LocalTangentPlane"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/Map"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/MapCallback"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/MapFrame"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/MapInfo"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/MapModelChange"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/MapNode"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/MapNodeObserver"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/MapNodeOptions"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/MapOptions"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/MaskLayer"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/MaskNode"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/MaskSource"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/MemCache"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/ModelLayer"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/ModelSource"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/NativeProgramAdapter"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/NodeUtils"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/Notify"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/optional"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/ObjectIndex"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/OverlayDecorator"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/OverlayNode"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/PhongLightingEffect"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/Picker"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/IntersectionPicker"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/PrimitiveIntersector"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/Profile"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/Profiler"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/Progress"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/Random"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/Registry"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/Revisioning"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/Shaders"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/ShaderFactory"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/ShaderGenerator"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/ShaderLoader"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/ShaderUtils"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/SharedSARepo"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/SpatialReference"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/StateSetCache"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/StateSetLOD"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/StringUtils"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/TaskService"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/Terrain"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/TerrainEffect"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/TerrainLayer"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/TerrainOptions"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/TerrainEngineNode"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/TerrainTileNode"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/Tessellator"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/TextureCompositor"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/TileKey"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/TileHandler"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/TileSource"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/TileVisitor"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/TimeControl"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/TraversalData"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/ThreadingUtils"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/Units"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/URI"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/Utils"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/Version"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/VerticalDatum"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/Viewpoint"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/VirtualProgram"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/XmlUtils"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/tinystr.h"
    "/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/osgEarth/tinyxml.h"
    )
endif()


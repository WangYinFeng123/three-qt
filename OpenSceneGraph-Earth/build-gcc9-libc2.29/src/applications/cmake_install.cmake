# Install script for directory: /home/truman/Desktop/three-widget/OpenSceneGraph-Earth/src/applications

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

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_viewer/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_seed/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_package/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_tfs/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_boundarygen/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_backfill/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_overlayviewer/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_version/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_tileindex/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_package_qt/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_clamp/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_manip/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_toc/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_createtile/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_elevation/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_features/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_featureinfo/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_featurefilter/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_los/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_terrainprofile/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_map/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_annotation/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_tracks/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_transform/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_measure/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_controls/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_shadercomp/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_tilesource/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_imageoverlay/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_city/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_graticule/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_featurequery/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_occlusionculling/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_colorfilter/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_sequencecontrol/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_minimap/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_sharedlayer/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_mrt/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_fog/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_shadergen/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_atlas/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_conv/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_clipplane/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_cache_test/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_pick/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_qt/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_qt_simple/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_qt_windows/cmake_install.cmake")
  include("/home/truman/Desktop/three-widget/OpenSceneGraph-Earth/build-gcc9-libc2.29/src/applications/osgearth_demo/cmake_install.cmake")

endif()

# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/hanur/CLionProjects/MagLevControl/cmake-build-debug-mingw/_deps/qcustomplot-src"
  "C:/Users/hanur/CLionProjects/MagLevControl/cmake-build-debug-mingw/_deps/qcustomplot-build"
  "C:/Users/hanur/CLionProjects/MagLevControl/cmake-build-debug-mingw/_deps/qcustomplot-subbuild/qcustomplot-populate-prefix"
  "C:/Users/hanur/CLionProjects/MagLevControl/cmake-build-debug-mingw/_deps/qcustomplot-subbuild/qcustomplot-populate-prefix/tmp"
  "C:/Users/hanur/CLionProjects/MagLevControl/cmake-build-debug-mingw/_deps/qcustomplot-subbuild/qcustomplot-populate-prefix/src/qcustomplot-populate-stamp"
  "C:/Users/hanur/CLionProjects/MagLevControl/cmake-build-debug-mingw/_deps/qcustomplot-subbuild/qcustomplot-populate-prefix/src"
  "C:/Users/hanur/CLionProjects/MagLevControl/cmake-build-debug-mingw/_deps/qcustomplot-subbuild/qcustomplot-populate-prefix/src/qcustomplot-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/hanur/CLionProjects/MagLevControl/cmake-build-debug-mingw/_deps/qcustomplot-subbuild/qcustomplot-populate-prefix/src/qcustomplot-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/hanur/CLionProjects/MagLevControl/cmake-build-debug-mingw/_deps/qcustomplot-subbuild/qcustomplot-populate-prefix/src/qcustomplot-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()

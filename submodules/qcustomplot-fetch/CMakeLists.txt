cmake_minimum_required(VERSION 3.11)

project(qcustomplot LANGUAGES CXX VERSION 2.1.1)


set(QCUSTOMPLOT_URL "https://www.qcustomplot.com/release/${QCUSTOMPLOT_VERSION}/QCustomPlot-source.tar.gz" CACHE STRING "")
set(QT_VERSION 6 CACHE STRING "Qt version to use")

set(CMAKE_PREFIX_PATH "C:/qt6/6.5.3/lib/cmake")

set(CMAKE_BUILD_TYPE "Release" CACHE STRING "")

set(Qt6Libs Core Widgets PrintSupport)

find_package(Qt6 COMPONENTS ${Qt6Libs} REQUIRED)

include(FetchContent)
FetchContent_Declare(qcustomplot
        URL "${QCUSTOMPLOT_URL}"
)
FetchContent_MakeAvailable(qcustomplot)

# Add QCustomPlot library
add_library(qcustomplot
        "${qcustomplot_SOURCE_DIR}/qcustomplot.cpp"
        "${qcustomplot_SOURCE_DIR}/qcustomplot.h"
)

# Add include directories
target_include_directories(qcustomplot PUBLIC
        "${qcustomplot_SOURCE_DIR}"
)

# Link Qt6 libraries to QCustomPlot
foreach(lib IN LISTS Qt6Libs)
  target_link_libraries(qcustomplot PRIVATE Qt${QT_VERSION}::${lib})
endforeach()

# Enable AUTOMOC for Qt6
set_target_properties(qcustomplot PROPERTIES
        AUTOMOC ON
)

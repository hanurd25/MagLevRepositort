cmake_minimum_required(VERSION 3.29)
project(MagLevControl)

if (MSVC)
    add_compile_options(/Zc:__cplusplus)
endif ()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "C:/qt6/6.5.3/lib/cmake")
set(QCUSTOMPLOT_VERSION "2.1.1")


find_package(Eigen3 CONFIG REQUIRED)
find_package(OpenCV CONFIG REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets PrintSupport)

add_subdirectory(submodules/qcustomplot-fetch)

add_executable(QtLivePlot
        noiseAnalyzer.cpp
 #       externals/qt/qcustomplot.cpp
)


target_link_libraries(QtLivePlot
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::PrintSupport
        ${OpenCV_LIBRARIES}
        #qtCustmPlotLib  # Correctly link the library target
        qcustomplot
        #${CMAKE_BINARY_DIR}/externals/qt
)

add_custom_command(TARGET QtLivePlot POST_BUILD
        COMMAND C:/qt6/6.5.3/bin/windeployqt.exe $<TARGET_FILE:QtLivePlot>
        COMMENT "Running windeployqt for QtLivePlot"
)



add_executable(MagLevControl main.cpp src/MagnetObserver.cpp)
target_link_libraries(MagLevControl
        Eigen3::Eigen
        ${OpenCV_LIBRARIES}
)

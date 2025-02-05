cmake_minimum_required(VERSION 3.29)
project(MagLevControl)

if (MSVC)
    add_compile_options(/Zc:__cplusplus)
endif ()


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CMAKE_PREFIX_PATH "C:/qt6/6.5.3/lib/cmake")
set(QCUSTOMPLOT_VERSION "2.1.1")

set(CMAKE_PREFIX_PATH "C:/qt6/6.5.3;${CMAKE_PREFIX_PATH}")



find_package(Eigen3 CONFIG REQUIRED)
find_package(OpenCV CONFIG REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets PrintSupport) #SerialPort)

find_path(RAPIDCSV_INCLUDE_DIRS "rapidcsv.h")


add_subdirectory(submodules/qcustomplot-fetch)


include(FetchContent)
set(SERIAL_BUILD_EXAMPLES OFF)
FetchContent_Declare(
        serial
        GIT_REPOSITORY https://github.com/markaren/serial.git
        GIT_TAG fd4ef255f693679f0d589df2145176b7c6eccb1c
)
FetchContent_MakeAvailable(serial)



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
        qcustomplot
        serial
)

add_executable(PlotAndWrite
        plotAndWriteToCSV.cpp
)

target_link_libraries(PlotAndWrite
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::PrintSupport
        ${OpenCV_LIBRARIES}
        qcustomplot
        serial
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

target_include_directories(PlotAndWrite PRIVATE ${RAPIDCSV_INCLUDE_DIRS})
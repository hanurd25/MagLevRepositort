
Downloading qt by this way shown in the link here: 
"https://wiki.qt.io/Building_Qt_6_from_Git"

//Use this command:
C:\qt6\6.5.3\bin\windeployqt.exe QtLivePlot.exe

The code uses QCustomPlot fetch with cmake with the turtorial found under:
https://github.com/conelov/qcustomplot-fetch







HKU cmake:
wsa
"
-DCMAKE_TOOLCHAIN_FILE=C:/PATH_TO_VCPKG_FROM_ROOOT/vcpkg/scripts/buildsystems/vcpkg.cmake
-DCMAKE_PREFIX_PATH=C:/qt6/6.5.3/lib/cmake
-DEigen3_DIR=PATH_TO_VCPKG_FROM_ROOOT/vcpkg/installed/x64-windows/share/eigen3
-DQt6_DIR=C:/qt6/6.5.3/lib/cmake/Qt6
-DOpenCV_DIR=C:/PATH_TO_VCPKG_FROM_ROOOT/opencv/build
-DVCPKG_MANIFEST_FEATURES=assimp;imgui
"

cmake ../qtserialport -G "Ninja" `
    -DCMAKE_TOOLCHAIN_FILE="C:/vcpkgpackage/vcpkg/scripts/buildsystems/vcpkg.cmake" `
-DCMAKE_INSTALL_PREFIX="C:/qt6" `
    -DCMAKE_PREFIX_PATH="C:/qt6/6.5.3" `
-DQT_NO_PACKAGE_VERSION_CHECK=TRUE `
-DCMAKE_BUILD_TYPE=Release



cmake ../qtserialport -G "Ninja" ^
-DCMAKE_PREFIX_PATH="C:/qt6/6.5.3" ^
-DCMAKE_INSTALL_PREFIX="C:/qt6/6.5.3/lib/cmake" ^
-DQT_NO_PACKAGE_VERSION_CHECK=TRUE ^
-DCMAKE_BUILD_TYPE=Release

Downloading Qtserial from source:
"git clone https://github.com/qt/qtserialport.git
cd qtserialport
mkdir build
cd build
cmake -G "Ninja" -DCMAKE_PREFIX_PATH=C:/qt6/6.5.3/lib/cmake ..
cmake --build .
cmake --install .
"
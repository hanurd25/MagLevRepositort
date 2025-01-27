have installed Qt6 via vcpkg using:

vcpkg install qt6-base:x64-windows


git pull
.\bootstrap-vcpkg.bat



cd C:PathToVCPKG
git pull
.\bootstrap-vcpkg.bat


C:\PathToVCPKG\vcpkg.exe install --triplet x64-windows


vcpkg> .\vcpkg.exe x-add-version --all


%downloading qt by this way: "https://wiki.qt.io/Building_Qt_6_from_Git"

//Use this command:
C:\qt6\6.5.3\bin\windeployqt.exe QtLivePlot.exe

HKU cmake:
"
-DCMAKE_TOOLCHAIN_FILE=C:/pathToVCPKG/vcpkg/scripts/buildsystems/vcpkg.cmake
-DEigen3_DIR=C:/pathToVCPKG/vcpkg/installed/x64-windows/share/eigen3
-DQt6_DIR=C:/qt6/6.5.3/lib/cmake/Qt6
-DOpenCV_DIR=C:/pathToVCPKG/opencv/build
-DVCPKG_MANIFEST_FEATURES=assimp;imgui
"

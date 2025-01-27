set(publicHeaders
        ${PROJECT_SOURCE_DIR}/include
)


set(SOURCES
        MPC.cpp
        MagnetObserver.cpp
)

add_library(MegLevLib ${SOURCES})
target_include_directories(MegLevLib PUBLIC ${publicHeaders})
target_link_libraries(MegLevLib PUBLIC Eigen3::Eigen)#threepp::threepp simple_socket imgui::imgui ${PCL_LIBRARIES} sfml-system sfml-window sfml-graphics ${OpenCV_LIBRARIES} nlohmann_json::nlohmann_json)
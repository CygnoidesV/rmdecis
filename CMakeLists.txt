cmake_minimum_required(VERSION 3.9)
project(rmdecis VERSION 2023.12 DESCRIPTION "Robomaster auto-aim prediction lib")

set(CMAKE_CXX_STANDARD 17)

option(RMDECIS_DEPLOYMENT "Build rmdecis with manually installed kissfft" OFF)

### Link libraries

if (RMDECIS_DEPLOYMENT)
    message("-- RMDECIS_DEPLOYMENT: Build rmdecis with manually installed kissfft")
    find_package(OpenCV REQUIRED)
    find_package(Ceres REQUIRED)
    find_package(Eigen3 REQUIRED)
    find_package(fmt REQUIRED)
    find_package(yaml-cpp REQUIRED)
    find_package(kissfft CONFIG REQUIRED COMPONENTS STATIC)
    link_libraries(${OpenCV_LIBS} ${CERES_LIBRARIES} Eigen3::Eigen fmt::fmt yaml-cpp kissfft::kissfft-float)
    include_directories(PRIVATE ${OpenCV_INCLUDE_DIRS} ${CERES_INCLUDE_DIRS})
else ()
    find_package(OpenCV REQUIRED)
    find_package(Ceres REQUIRED)
    find_package(Eigen3 REQUIRED)
    find_package(KissFFT REQUIRED)
    find_package(fmt REQUIRED)
    find_package(yaml-cpp REQUIRED)
    link_libraries(${OpenCV_LIBS} ${CERES_LIBRARIES} Eigen3::Eigen fmt::fmt kissfft-float yaml-cpp)
    include_directories(PRIVATE ${OpenCV_INCLUDE_DIRS} ${CERES_INCLUDE_DIRS})
endif ()

### Set directories & Get targets

include_directories(PRIVATE ${PROJECT_SOURCE_DIR}/3rdparty)
include_directories(PRIVATE ${PROJECT_SOURCE_DIR}/src)
include_directories(PUBLIC ${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE rmdecis_LIBS CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB_RECURSE rmdecis_HEADERS CONFIGURE_DEPENDS "include/*.h")
file(GLOB_RECURSE rmdecis_UTILS CONFIGURE_DEPENDS "utils_contrib/*.cpp")

message("-- ProjectSourceDir: ${PROJECT_SOURCE_DIR}")
message("-- GLOB: \${rmdecis_LIBS}: ${rmdecis_LIBS}")
message("-- GLOB: \${rmdecis_HEADERS}: ${rmdecis_HEADERS}")
message("-- GLOB: \${rmdecis_UTILS}: ${rmdecis_UTILS}")


### Build Library

add_library(rmdecis SHARED ${rmdecis_LIBS})
target_link_libraries(rmdecis PUBLIC ${OpenCV_LIBS})
set_target_properties(rmdecis PROPERTIES
        VERSION ${PROJECT_VERSION}
        PUBLIC_HEADER "${rmdecis_HEADERS}")

### Install library

include(GNUInstallDirs)
configure_file(rmdecis.pc.in rmdecis.pc @ONLY)
install(TARGETS rmdecis
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/rmdecis)
install(FILES ${CMAKE_BINARY_DIR}/rmdecis.pc
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)


### Tests

add_executable(util_calibrate_camera tests/calibrate_camera.cpp)

add_executable(test_video_playback ${rmdecis_UTILS} ${rmdecis_LIBS} tests/test_video_playback.cpp)

add_executable(test_reconstructor ${rmdecis_UTILS} ${rmdecis_LIBS} tests/test_reconstructor.cpp)

#add_executable(test_armor_track ${rmdecis_LIBS} ${rmdecis_UTILS} tests/test_armor_track.cpp)

add_executable(test_tracker ${rmdecis_LIBS} ${rmdecis_UTILS} tests/test_tracker.cpp)

add_executable(test_tracker_association ${rmdecis_LIBS} ${rmdecis_UTILS} tests/test_tracker_association.cpp)

#add_executable(test_detection ${rmdecis_LIBS} ${rmdecis_UTILS} tests/test_detection.cpp)

add_executable(test_basic_aiming ${rmdecis_LIBS} ${rmdecis_UTILS} tests/test_basic_aiming.cpp)

add_executable(test_config ${rmdecis_LIBS} ${rmdecis_UTILS} tests/test_config.cpp)

add_executable(test_kissfft ${rmdecis_LIBS} ${rmdecis_UTILS} tests/test_kissfft.cpp)

add_executable(test_trig_fitting ${rmdecis_LIBS} ${rmdecis_UTILS} tests/test_trig_fitting.cpp)

add_executable(test_rotated_rect ${rmdecis_LIBS} ${rmdecis_UTILS} tests/test_rotated_rect.cpp)

add_executable(test_large_rune_aiming ${rmdecis_LIBS} ${rmdecis_UTILS} tests/test_large_rune_aiming.cpp)

add_executable(test_transformer ${rmdecis_LIBS} ${rmdecis_UTILS} tests/test_transformer.cpp)

add_executable(test_avg_queue ${rmdecis_LIBS} ${rmdecis_UTILS} tests/test_avg_queue.cpp)

add_executable(test_ballistic_compensator ${rmdecis_LIBS} ${rmdecis_UTILS} tests/test_ballistic_compensator.cpp)

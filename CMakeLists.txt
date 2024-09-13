cmake_minimum_required(VERSION 3.29)
project(MusicPlayer)

set(CMAKE_CXX_STANDARD 20)

find_package(ALSA REQUIRED)
if(NOT ALSA_FOUND)
    message(FATAL_ERROR "ALSA lib not found")
endif()

#create sound basis lib
add_library(SoundBasis
        SoundBasis/Types.h
        SoundBasis/Exceptions.h
        SoundBasis/Buffer.cpp
        SoundBasis/Buffer.h
        SoundBasis/Adapter.cpp
        SoundBasis/Adapter.h
)

#create SoundDevice lib
add_library(SoundDevice
        SoundDevice/ALSA_PlayDevice.cpp
        SoundDevice/ALSA_PlayDevice.h
        SoundDevice/BasePlayDevice.cpp
        SoundDevice/BasePlayDevice.h
        SoundDevice/PlaybackDevice.h
)
target_link_libraries(SoundDevice SoundBasis)

#create SoundFiles lib
add_library(SoundFiles
        SoundFiles/WaveFile.cpp
        SoundFiles/WaveFile.h
)
target_link_libraries(SoundFiles SoundBasis)

#create exec target
add_executable(${PROJECT_NAME} main.cpp
        MusicPlayer/MusicPlayer.cpp
        MusicPlayer/MusicPlayer.h
        MusicPlayer/CLI_Interface.cpp
        MusicPlayer/CLI_Interface.h
)

target_link_libraries(${PROJECT_NAME} ${ALSA_LIBRARIES})
target_link_libraries(${PROJECT_NAME} SoundBasis SoundDevice SoundFiles)

#preprocessor definitions
add_compile_definitions(__LINUX__)
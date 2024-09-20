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
        SoundBasis/FourrierTransform.cpp
        SoundBasis/FourrierTransform.h
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

#create CLI_UI_INSTANCE library
add_library(CLI_UI
        CLI_UI/CLI_UI.cpp
        CLI_UI/CLI_UI.h
        CLI_UI/BarGraph.h
        CLI_UI/Types.h
        CLI_UI/Button.h
        CLI_UI/ValueField.h
        CLI_UI/Types.cpp
        CLI_UI/TextField.h
)

#preprocessor definitions
add_compile_definitions(__LINUX__)

#debug and test target
add_executable(UnitTests unitTestMain.cpp)
target_link_libraries(UnitTests SoundBasis SoundDevice ${ALSA_LIBRARIES} SoundFiles)

#create a test executable to debug CLI_UI_INSTANCE lib
add_executable(CLI_UI_TEST CLI_UI/libTestMain.cpp)
target_link_libraries(CLI_UI_TEST CLI_UI)

#create exec target
add_executable(${PROJECT_NAME} main.cpp
        MusicPlayer/MusicPlayer.cpp
        MusicPlayer/MusicPlayer.h
)

target_link_libraries(${PROJECT_NAME} ${ALSA_LIBRARIES})
target_link_libraries(${PROJECT_NAME} SoundBasis SoundDevice SoundFiles CLI_UI)